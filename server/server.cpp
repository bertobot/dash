#include "../core/Dash.h"
#include "ProxyWorker.h"
#include "ProxyCommand.h"

#include <MySocket/Select.h>
#include <ControlPort/ControlPort.h>

#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <getopt.h>
/////////////////////////////////////////////////
void signal_cleanup(int);
void signal_pipe(int);

std::vector<Worker*> *workerPtr = NULL;
ServerSocket *server = NULL;

enum OP_MODE {
    OP_NODE,
    OP_PROXY,
};

/////////////////////////////////////////////////
int main(int argc, char **argv) {
    int opt_port = 33000;
    int opt_controlport = opt_port + 1;
    int opt_connections = 256;
    std::string opt_name = "metro";
    std::string opt_logfile = "log.out";
    std::string opt_mode = "node";
    int opt_daemon = 0;
    int opt_flushtime = 10;
    int opt_threads = 10;

    OP_MODE operationMode = OP_NODE;
    std::map<std::string, ClientSocket> proxyConnections;

    int c;

    std::vector<Worker*> workerThreads;
    ThreadWriter threadWriter;

    Dash dash;
    
    // getopt
    // TODO: specify log file, port to run on, mode {proxy, node}, cap how much resources to use.
    while (1) {
        static struct option long_options[] = {
            /* These options set a flag. */

            /*
            {"verbose", no_argument,       &verbose_flag, 1},
            {"brief",   no_argument,       &verbose_flag, 0},
            */

            /* These options don't set a flag.  We distinguish them by their indices. */

            /*
            {"add",     no_argument,       0, 'a'},
            {"append",  no_argument,       0, 'b'},
            {"delete",  required_argument, 0, 'd'},
            {"create",  required_argument, 0, 'c'},
            {"file",    required_argument, 0, 'f'},
            */

            // max connections
            {"connections", required_argument, 0,  'c'},

            // daemon mode
            {"daemon",      no_argument,        0,  'd'},

            // flush time
            {"flushtime",   required_argument,   0,  'f'},

            // logfile
            {"log",         required_argument,  0,  'l'},

            // mode
            {"mode",        required_argument,  0,  'm'},

            // instance name
            {"name",        required_argument,  0,  'n'},

            // port
            {"port",        required_argument,  0,  'p'},

            {0, 0, 0, 0}
        };

        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "c:df:l:m:n:p:", long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c) {
            case 0:
                /* If this option set a flag, do nothing else now. */
                if (long_options[option_index].flag != 0)
                    break;
                printf ("option %s", long_options[option_index].name);
                if (optarg)
                    printf (" with arg %s", optarg);
                printf ("\n");
                break;

			case 'c':
				opt_connections = atoi(optarg);
				break;

            case 'f':
                opt_flushtime = atoi(optarg);
                break;

            case 'd':
                opt_daemon = 1;
                break;

            case 'l':
                opt_logfile = optarg;
                break;

            case 'm':
                opt_mode = optarg;

                if (opt_mode == "proxy") {
                    printf("running in proxy mode\n");
                    operationMode = OP_PROXY;
                }
                break;

            case 'n':
                opt_name = optarg;
                break;

            case 'p':
                opt_port = atoi(optarg);
                opt_controlport = opt_port + 1;
                break;

            default:
                //abort ();
                break;
        }
    }

    // end getopt

	// TODO: move this logic down after setting up of worker threads.
    // deamonize here, if optioned
    if (opt_daemon) {
        unsigned int child = fork();
        if (child < 0) {
            printf("couldn't place in background.\n");
            exit(1);
        }
        if (child > 0)
            exit(0);

        // else, child
        printf("child pid: %d\n", child);
    }

    if (opt_logfile.length() ) {
        threadWriter.load(opt_logfile);
    }

    // signal catcher first!
    (void) signal(SIGINT,signal_cleanup);
    (void) signal(SIGPIPE,signal_pipe);

    // start the control port
    
    CommandManager cm;
    ProxyCommand proxyCommand;
    ControlPort cp(opt_controlport);

    proxyCommand.associateMap(&proxyConnections);
    
    cp.setThreadCount(10);
    cp.associateCommandManager(&cm);

    if (operationMode == OP_PROXY)
        cm.add(&proxyCommand);
    
    cp.start();

	server = new ServerSocket(opt_port);

	if (! server->isValid() ) {
		printf("problem creating socket: %d\n", errno);
		return 1;
	}

	if (! server->isBound() ) {
		printf("binding error: %s\n", strerror(errno) );
		exit(5);
	}

	server->listen(opt_connections);

    for (int i = 0; i < opt_threads; i++) {
        Worker *newWorker;

        if (operationMode == OP_NODE)
            newWorker = new Worker(server);
        else if (operationMode == OP_PROXY) {
            newWorker = new ProxyWorker(server);
            ProxyWorker *pw = (ProxyWorker*)newWorker;
            pw->associateMap(&proxyConnections);
        }

        newWorker->setControlPort(&cp);
        newWorker->setDash(&dash);
        newWorker->setThreadWriter(&threadWriter);
        newWorker->setWorkerId(i);

        newWorker->start();
        printf("started thread %d.\n", i);
        
        workerThreads.push_back(newWorker);
    }

    workerPtr = &workerThreads;

    Select maintenance;
    maintenance.setTimeout(3,0);

    while (!cp.isDone()) {
        maintenance.wait();

        //TODO: do maintenance here.
    }

    // shut down the sockets by connecting to them.
    for (int j = 0; j < opt_threads; j++) {
        ClientSocket cs("127.0.0.1", opt_port);
        cs.connect();
        cs.writeLine("");
        cs.close();
    }



    // finally, join all threads
    for (int j = 0; j < opt_threads; j++) {
        Worker *c = workerThreads[j];
        if (c) {
            c->join();
            delete c;
            c = NULL;
        }
    }

    cp.join();

    // clean up
    server->close();
    delete server;
    server = NULL;

    printf("goodbye.\n");
}
/////////////////////////////////////////////////
void signal_cleanup(int sig) {
    printf("sigint received.  going down.\n");
    exit(sig);
}
/////////////////////////////////////////////////
void signal_pipe(int sig) {
    printf("sigpipe caught.  doing nothing!\n");
}
/////////////////////////////////////////////////
