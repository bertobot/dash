#include "ProxyNodeSocket.h"
/////////////////////////////////////////////////
ProxyNodeSocket::ProxyNodeSocket(const ClientSocket &rhs) : ClientSocket(rhs), thread() {
    returnCode = 0;
}
/////////////////////////////////////////////////
ProxyNodeSocket::ProxyNodeSocket(const std::string &hostname, int port) : ClientSocket(hostname, port), thread() {
    returnCode = 0;
}
/////////////////////////////////////////////////
bool ProxyNodeSocket::isMetroUp() {
    // send a ping
    respond("ping");

    // TODO: attempt to get pong, but do it with a timeout
    get();
    std::string response = readLine();
    deWhiteSpace(response);

    if (response == "pong") {
        return true;
    }

    return false;
}
/////////////////////////////////////////////////
int ProxyNodeSocket::write(const std::string &str) {
    sendString = str;
    start();
    return returnCode;
}
/////////////////////////////////////////////////
// run
//
// unlike our normal run() being a loop, this
// run method will be an asynchronous write.
//
void ProxyNodeSocket::run() {
    if (isMetroUp() ) {
        returnCode = ::send(getSocketDescriptor(), sendString.c_str(), sendString.length(), MSG_NOSIGNAL);
    }
    else {
        returnCode = -1;
    }
}
/////////////////////////////////////////////////
void ProxyNodeSocket::stop() {

}
/////////////////////////////////////////////////
void ProxyNodeSocket::debugAndRespond(const std::string & str) {
    debug(str);
    respond(str);
}
/////////////////////////////////////////////////
void ProxyNodeSocket::respond(const std::string &str) {
    // TODO: isn't this in the threadsocket base class?

    if (isValid() ) {
        try {
            Socket::write(str + "\r\n", MSG_NOSIGNAL);
        }
        catch (...) {
            printf("fatal: couldn't write!\n");
        }
    }
    else {
        debug("warning: was not able to send '" + str + "' because socket wasn't ready for writing.");
    }
}
/////////////////////////////////////////////////
ProxyNodeSocket::~ProxyNodeSocket() {

}
/////////////////////////////////////////////////
