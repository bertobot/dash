#include "../Dash.h"
#include <iostream>
/////////////////////////////////////////////////
int main() {

    Dash dash;

    std::string
	msg1 = "this is a test.",
	msg2 = "in a real emergency, you will hear a siren.";

    dash.put("t1", msg1);
    dash.put("t2", msg2);

    if (dash.get("t1") == msg1)
	std::cout << "1... ok" << std::endl;
    else {
	std::cerr << "1... fail." << std::endl;
	return 1;
    }

    if (dash.get("t2") == msg2)
	std::cout << "2... ok" << std::endl;
    else {
	std::cerr << "2... fail." << std::endl;
	return 2;
    }

    if (dash.get("t3").empty() )
	std::cout << "3... ok" << std::endl;
    else {
	std::cerr << "3... fail." << std::endl;
	return 3;
    }	

    return 0;
}