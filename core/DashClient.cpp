#include "DashClient.h"
/////////////////////////////////////////////////
DashClient::DashClient(ClientSocket *client)
{
    this->client = client;
}
/////////////////////////////////////////////////
std::string DashClient::get(const std::string& key)
{
    Select s;
    s.setTimeout(180);
    std::stringstream ss("get " + key);
    
    if (client) {
	s.add(client->getSocketDescriptor() );

	std::vector<int> fds = s.canWrite();
	
	if (fds.size() > 0)
	    client->write(ss.str() );
	
	fds = s.canRead();

	if (fds.size() > 0) {
	    // the first response is the size of the payload.
	    
	    std::stringstream ss(client->readLine() );

	    // TODO: may have to change MySocket::Socket to be unsigned int instead of int
	    
	    //unsigned int size = 0;
	    int size = 0;
	    ss >> size;

	    return client->read(size);
	}
    }

    // TODO: exception!
}
/////////////////////////////////////////////////
void DashClient::put(const std::string& key, const std::string& value)
{
    Select s;
    s.setTimeout(180);
    std::stringstream ss("put " + key + " " + value);
    
    if (client) {
	s.add(client->getSocketDescriptor() );

	std::vector<int> fds = s.canWrite();
	if (fds.size() > 0)
	    client->write(ss.str() );

	fds = s.canRead();
	
	if (fds.size() > 0) {
	    std::string response = client->readLine();

	    // TODO: do something with response.
	}
    }

    // TODO: exception;
}
/////////////////////////////////////////////////
DashClient::~DashClient()
{
    if (client) {
	client->close();
	delete client;
    }
}
/////////////////////////////////////////////////
