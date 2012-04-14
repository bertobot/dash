#include "Worker.h"
/////////////////////////////////////////////////
Worker::Worker(ServerSocket *server) : thread() {
    // TODO: this should throw an exception if server is null.

    shutdownflag = false;
    this->server = server;
    this->client = NULL;
    this->tw = NULL;
    this->dash = NULL;
    this->controlPort = NULL;
    
    workerId = -1;
}
/////////////////////////////////////////////////
void Worker::run() {
    while (! shutdownflag) {
        if (controlPort && controlPort->isDone()) {
            break;
        }
        
	try {
	    client = new Socket(server->accept() );

	    if (challenge())
		processRequest();

	    client->close();
	}

	catch(...) {
	    printLocal("busted...");

	    //shutdownflag = true;
	    //::exit(111);
	    //throw;
	}

	// clean up
	delete client;
        client = NULL;

	std::stringstream ss;
	ss << "thread " << workerId << " finished.";
	printLocal(ss.str() );
    }

    std::stringstream ss;
    ss << "Worker " << workerId << " finished.";
    printLocal(ss.str() );
}
/////////////////////////////////////////////////
void Worker::stop() {
    shutdownflag = true;
}
/////////////////////////////////////////////////
int Worker::close() {
    int rc = -2;
    if (client) {
	rc = client->close();
    }
    
    return rc;
}
/////////////////////////////////////////////////
void Worker::printLocal(const std::string & str) {
    time_t seconds = time(NULL);
    std::cerr << seconds << " [threadserver] " << str << std::endl;
}
/////////////////////////////////////////////////
void Worker::printLocalAndRespond(const std::string & str) {
    printLocal(str);
    respond(str);
}
/////////////////////////////////////////////////
void Worker::respond(const std::string &str) {
    if (! client) {
        // TODO: should this be an exception?
        
        printLocal("respond: client is null!\n");
        return;
    }
    
    if (client->isValid() ) {
        try {
            client->write(str + "\r\n", MSG_NOSIGNAL);
        }
        catch (...) {
            printLocal("fatal: couldn't write!\n");
        }
    }
    else {
        printLocal("warning: was not able to send '" + str + "' because socket wasn't ready for writing.");
    }
}
/////////////////////////////////////////////////
bool Worker::challenge() {
    // NOTE: purposely empty
    return true;
}
/////////////////////////////////////////////////
void Worker::processRequest()
{
    Select s;
    s.setTimeout(180);

    if (client) {
	s.add(client->getSocketDescriptor() );

	std::vector<int> fds = s.canRead();

	if (fds.size() > 0) {
	    std::string input = client->readLine();	    
	    std::vector<std::string> tokens = split(' ', input);

	    printLocal(input);

	    /*
	     * protocols supported:
	     * 
	     * put <key> <value>
	     * get <key>
	     * 
	     * search <key|value> <regular expression>
	     *
	     */

	    //respond("ok - " + input);

	    if (tokens[0] == "put") {
		if (tokens.size() < 3) {
		    respond("nok");
		    return;
		}

                dash->put(tokens[1], ::join(' ', tokens, 2) );

		respond("ok");
	    }

	    else if (tokens[0] == "get") {
		if (tokens.size() != 2) {
		    respond("nok");
		    return;
		}

		Value v = dash->get(tokens[1]);
		std::stringstream ss;
		ss << v.value.length() << '\n' << v.value;
		
		respond(ss.str() );
	    }
	}
	else {
	    respond("timeout.");
	}
    }

}
/////////////////////////////////////////////////
void Worker::setThreadWriter(ThreadWriter* threadWriter)
{
    tw = threadWriter;
}
/////////////////////////////////////////////////
void Worker::setWorkerId(int id) {
	workerId = id;
}
/////////////////////////////////////////////////
int Worker::getWorkerId() const {
	return workerId;
}
/////////////////////////////////////////////////
void Worker::setDash(Dash *d)
{
    this->dash = d;
}
/////////////////////////////////////////////////
void Worker::setControlPort(ControlPort* cp)
{
    this->controlPort = cp;
}
/////////////////////////////////////////////////
Worker::~Worker() {
    close();

    if (client)
        delete client;

    tw = NULL;
    dash = NULL;
    controlPort = NULL;
}
/////////////////////////////////////////////////
