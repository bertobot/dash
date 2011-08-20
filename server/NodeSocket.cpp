#include "NodeSocket.h"
/////////////////////////////////////////////////
NodeSocket::NodeSocket(const Socket &rhs) : ThreadSocket(rhs) {

}
/////////////////////////////////////////////////
bool NodeSocket::challenge() {
    Select s;
    std::stringstream ss;

    s.add(getSocketDescriptor() );
    s.setTimeout(60, 0);            // set to 60 seconds for now

    // we are expecting a challenge.  if we don't hear back in some time, close the connection
    int challengeDescriptor = s.canRead();
    if (challengeDescriptor == 0) {
        ss.str("");
        ss << getClientIP() << ":" << getClientPort() << " did not respond to challenge in time." << std::endl;
        debug(ss.str() );
        ss.str("");

        cleanup();
        return false;
    }

    else if (challengeDescriptor == -1) {
        ss.str("");
        ss << getClientIP() << ":" << getClientPort() << " error'd out while waiting." << std::endl;
        debug(ss.str() );
        ss.str("");

        cleanup();
        return false;
    }

    // now for the challenge

    std::string str = Socket::readLine();
    deWhiteSpace(str);

    // TODO: do the actual challenge

    debugAndRespond("challenge accepted.");

    return true;
}
/////////////////////////////////////////////////
void NodeSocket::onLoop() {
    Select s;
    std::stringstream ss;

    s.add(getSocketDescriptor() );
    s.setTimeout(60, 0);            // set to 60 seconds for now

    // check that the connection is still valid
    if (!Socket::isValid() ) {
        debug("socket no longer valid.  closing...");
        done = true;
        return;
    }

    // pull data from the wire into the socket's buffer
    if (s.canRead() <= 0) {
        ss.str("");
        ss << getClientIP() << ":" << getClientPort() << " stalled.  closing connection..." << std::endl;
        debug(ss.str() );
        ss.str("");

        cleanup();
        return;
    }

    /////////////////////////////////////////
    // command parse phase

    std::string str = Socket::readLine();
    deWhiteSpace(str);

    std::vector<std::string> tokens = split(' ', str);
    std::string command = tokens[0];

    // process commands here

    debug("[recv] " + str);

    if (command.empty() ) {
        // no op, which is different from continue
        done = true;
    }

    else if (command == "exit") {
        done = true;
    }

    else {
//                errorcount++;
        respond("nok");
    }
}
/////////////////////////////////////////////////
void NodeSocket::run() {
    std::string str;
    std::string command;

    bool runOnce = true;

    int errorcount = 0;
    // set this number higher to have a higher message-error tolerance
    int maxerrors = 0;
    Select s;

    std::stringstream ss (std::stringstream::out);
    ss << getClientIP() << ":" << getClientPort() << " has connected." << std::endl;

    debug(ss.str() );
    ss.str("");

    // challenge
    if (!challenge() )
        return;

    ss << "server 1.0. you are client " << getSocketDescriptor() << "\r\n";
    Socket::write(ss.str() );
    ss.str("");

    // TODO: break out your select-in-socket library into it's own library.

    try {
        while (!done) {
            onLoop();

            // break out of loop if done or thread has been stopped.
            if (done || isStopped() ) {
                done = true;
                break;
            }

            done = done || isStopped();
        }
    }
    catch(...) {
        debug("critical: " + str);
    }

    // debug
    ss.clear();
    ss << getClientIP() << ":" << getClientPort() << " has disconnected." << std::endl;
    debug(ss.str() );

    // cleanup
    cleanup();
}
/////////////////////////////////////////////////
void NodeSocket::stop() {
    done = true;
}
/////////////////////////////////////////////////
NodeSocket::~NodeSocket() {
    //printf("NodeSocket Destructor\n");
	//cleanup();
}
/////////////////////////////////////////////////
