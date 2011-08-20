#include "Worker.h"
/////////////////////////////////////////////////
Worker::Worker(ServerSocket *server) : thread() {
	// TODO: this should throw an exception if server is null.

	this->server = server;
    shutdownflag = false;
	
	workerId = -1;
}
/////////////////////////////////////////////////
void Worker::run() {
	std::stringstream ss;

	while (! shutdownflag) {
		try {
			client = new Socket(server->accept() );

			if (challenge())
				processRequest();

			client->close();
			delete client;
			client = NULL;
		}

		catch(...) {
			printLocal("busted...");
			shutdownflag = true;
			::exit(111);
			throw;
		}

		ss.str("");
		ss << "thread " << workerId << " finished.";
		printLocal(ss.str() );
	}

	ss.str("");
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
	if (client)
	    rc = client->close();
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
    // NOTE: purposely empty
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
Worker::~Worker() {
    close();
}
/////////////////////////////////////////////////
