#include "DashClient.h"
/////////////////////////////////////////////////
DashClient::DashClient(ClientSocket *client)
{
    this->client = client;
}
/////////////////////////////////////////////////
std::string DashClient::get(const std::string& key)
{
    std::stringstream ss("get " + key);
    if (client) {
	client->write(ss.str() );
	return client->read();
    }

    // TODO: exception!
}
/////////////////////////////////////////////////
void DashClient::put(const std::string& key, const std::string& value)
{
    std::stringstream ss(key + " " + value);
    if (client) {
	client->write(ss.str() );
	client->read();
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
