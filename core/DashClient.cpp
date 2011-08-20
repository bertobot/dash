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
    std::stringstream ss("get " + key);
    
    if (client) {
	s.add(client->getSocketDescriptor() );

	std::vector<int> fds = s.canWrite();
	
	if (fds.size() > 0)
	    client->write(ss.str() );
	
	fds = s.canRead();

	if (fds.size() > 0)
	    return client->readLine();
    }

    // TODO: exception!
}
/////////////////////////////////////////////////
void DashClient::put(const std::string& key, const std::string& value)
{
    Select s;
    std::stringstream ss(key + " " + value);
    
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
