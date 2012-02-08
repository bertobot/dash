#include "ProxyWorker.h"
/////////////////////////////////////////////////
ProxyWorker::ProxyWorker(ServerSocket *server) : Worker(server) {
    map = NULL;
    timeout = 3;
}
/////////////////////////////////////////////////
void ProxyWorker::processRequest()
{
    // TODO: log this as an error.
    if (! map)
        return;
    
    std::string message;    
    Select s1, s2;
    
    s1.setTimeout(timeout, 0);
    s2.setTimeout(timeout, 0);
    
    s1.add(client->getSocketDescriptor());

    if (! s1.canRead().empty() ) {
        message = client->readLine();
    }
    else {
        // timeout
        return;
    }


    std::map< std::string, ClientSocket >::iterator itr = map->begin();

    for (; itr != map->end(); itr++) {
        if (itr->second.connect() )
            s2.add(itr->second.getSocketDescriptor() );
    }

    std::vector<int> ready = s2.canWrite();
    
    for (unsigned int i = 0; i < ready.size(); i++) {
        Socket t(ready[i]);
        t.writeLine(message);
    }

    ready = s2.canRead();
    std::stringstream ss;
    for (unsigned int i = 0; i < ready.size(); i++) {
        Socket t(ready[i]);

        message = t.readLine();

        int size = atoi(message.c_str() );

        ss << size;

        if (size > 0)
            ss << '\n' << t.readLine();

        // respond to the client;
        client->writeLine(ss.str());

        // log and close

        printf("%s:%d %s\n", t.getClientIP().c_str(), t.getClientPort(), ss.str().c_str() );
        t.close();

        ss.str("");

        // only need to return one
        break;
    }
}
/////////////////////////////////////////////////
void ProxyWorker::associateMap(std::map< std::string, ClientSocket >* m)
{
    map = m;
}
/////////////////////////////////////////////////
ProxyWorker::~ProxyWorker() {
    map = NULL;
}
/////////////////////////////////////////////////
