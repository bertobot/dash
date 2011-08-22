#include "../core/DashClient.h"
#include <iostream>
#include "../core/Dash.h"
/////////////////////////////////////////////////
int main() {

    ClientSocket client("localhost", 33000);

    DashClient dc(&client);

    std::string
	msg1 = "this is a test.",
	msg2 = "in a real emergency, you will hear a siren.";

    if (! client.connect() ) {
	printf("couldn't connect.\n");
	return 1;
    }
    
    dc.put("t1", msg1);
    dc.put("t2", msg2);

    if (dc.get("t1") == msg1) 
	std::cout << "1... ok" << std::endl;
    else {
	std::cerr << "1... fail." << std::endl;
	return 1;
    }

    //printf("count: %ld, length: %ld, timestamp: %ld\n", v.count, v.value.length(), v.timestamp);

    if (dc.get("t2") == msg2)
	std::cout << "2... ok" << std::endl;
    else {
	std::cerr << "2... fail." << std::endl;
	return 2;
    }

    //printf("count: %ld, length: %ld, timestamp: %ld\n", v.count, v.value.length(), v.timestamp);

    if (dc.get("t3").empty() )
	std::cout << "3... ok" << std::endl;
    else {
	std::cerr << "3... fail." << std::endl;
	return 3;
    }	

    return 0;
}
