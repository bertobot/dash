#include "ProxySocket.h"
/////////////////////////////////////////////////
ProxySocket::ProxySocket(const Socket &rhs) : ThreadSocket(rhs) {
    nm = NULL;
}
/////////////////////////////////////////////////
void ProxySocket::run() {
    std::string str;
    std::string command;

    std::stringstream ss (std::stringstream::out);
    ss << getSocketDescriptor() << " has connected." << std::endl;

    debug(ss.str() );

    Socket::write("server 1.0\r\n");

    running = true;
    int errorcount = 0;

    try {
        while (!done) {
            // check that the connection is still valid
            if (!Socket::isValid() ) {
                debug("socket no longer valid.  closing...");
                done = true;
                break;
            }

            // pull data from the wire into the socket's buffer
            Socket::get();

            while (Socket::hasBuffer() ) {
                if (errorcount >= 5) {
                    debugAndRespond("5 errors in a row, disconnecting.");
                    Socket::clearBuffer();
                    done = true;
                    continue;
                }

                /////////////////////////////////////////
                // command parse phase

                str = Socket::readLine();

                deWhiteSpace(str);

                std::vector<std::string> tokens = split(' ', str);
                command = tokens[0];

                // process commands here

				debug("[recv] " + str);

                if (command.empty() ) {
                    continue;
                }

                else if (command == "exit") {
                    done = true;
                }

                else if (command == "addnode") {
                    if ( addNode(tokens) && tw ) {
                        respond("ok");

                        // respond ok if everything worked
                        // log that we got a put
                        tw->add(str);

                        errorcount = 0;
                    }
                    errorcount++;
                }

                else if (command == "dropnode") {
                    dropNode(tokens);
                }

                else if (command == "listnodes") {
                    listNodes(tokens);
                }

                else if (command == "ping") {
                    respond("pong");
                }

                else {
                    passItDown(str);
                }


                // loop!
            }
        }
    }

    catch(...) {
        debug("critical: " + str);
    }

    // debug
    ss.clear();
    ss << getSocketDescriptor() << " has disconnected." << std::endl;
    debug(ss.str() );

    // cleanup
    Socket::clearBuffer();
    m = NULL;
    tw = NULL;

    close();
    running = false;
}
/////////////////////////////////////////////////
void ProxySocket::stop() {
    done = true;
}
/////////////////////////////////////////////////
bool ProxySocket::addNode(const std::vector<std::string> &tokens) {
    // format: addnode <name> <host> <port>
    if (tokens.size() == 4) {
        std::string nodeName = tokens[1];
        std::string hostName = tokens[2];

        if (! validString(nodeName) ) {
            return false;
        }

        if (! validString(hostName) ) {
            return false;
        }

        std::stringstream sport (tokens[3]);

        int port = 0;
        sport >> port;

        if (port < 0 || port > 32767) {
            return false;
        }

        if (nm) {
            // make sure that we don't already have a node mapping
            if (! nm->getnode(nodeName)->isValid() ) {
                // we're good.
                ProxyNodeSocket *pns = new ProxyNodeSocket(hostName, port);
                pns->connect();

                if (nm->addnode(nodeName, pns) ) {
                    return true;
                }
                // shouldn't get here

                // here, we know there's already a mapping.
                pns->write("exit\n");
                pns->close();
                delete pns;
            }
        }
	}

    return false;
}
/////////////////////////////////////////////////
void ProxySocket::dropNode(const std::vector<std::string> &tokens) {
    // format dropnode <name>
    if (tokens.size() == 2) {
        std::string nodeName = tokens[1];

        if (nm) {
            nm->dropnode(nodeName);
        }
    }
}
/////////////////////////////////////////////////
void ProxySocket::listNodes(const std::vector<std::string> &tokens) {
    std::vector<std::string> result;
    if (nm) {
        result = nm->listnodes("");

        for (int i = 0; i < result.size(); i++) {
            respond(result[i]);
        }
    }

    respond("ok");
}
/////////////////////////////////////////////////
void ProxySocket::passItDown(const std::string &str) {
    if (nm) {
        nm->sendToAll(str);
    }
}
/////////////////////////////////////////////////
void ProxySocket::assocNodeMap(NodeMap *n) {
    nm = n;
}
/////////////////////////////////////////////////
ProxySocket::~ProxySocket() {

}
/////////////////////////////////////////////////
