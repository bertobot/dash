#include "DashClient.h"

std::string DashClient::get(const std::string& key)
{
    std::stringstream ss("get " + key);
    
    if (mClient) {
        // write our get command
        mClient->write(ss.str() );
	
        BufferedReader bchannel(mClient);
	    // the first response is the size of the payload.
	    
	    std::stringstream ss(bchannel.readLine() );

	    // TODO: may have to change MySocket::Socket to be unsigned int instead of int
	    
	    //unsigned int size = 0;
	    int size = 0;
	    ss >> size;

	    return mClient->read(size);
	}

    return "";
}

void DashClient::put(const std::string& key, const std::string& value)
{
    std::stringstream ss("put " + key + " " + value);
    
    if (mClient) {
	    mClient->write(ss.str() );

        BufferedReader bchannel(mClient);

	    std::string response = bchannel.readLine();

	    // TODO: do something with response.
	}
}

// vim: ts=4:sw=4:expandtab
