#include "../core/Dash.h"
#include <iostream>
/////////////////////////////////////////////////
int main() {

    Dash dash;
    Value v;

    std::string
	msg1 = "this is a test.",
	msg2 = "in a real emergency, you will hear a siren.";

    dash.put("t1", msg1);
    dash.put("t2", msg2);

    v = dash.get("t1");
    if (v.value == msg1)
	std::cout << "1... ok" << std::endl;
    else {
	std::cerr << "1... fail." << std::endl;
	return 1;
    }

    v = dash.get("t2");
    if (v.value == msg2)
	std::cout << "2... ok" << std::endl;
    else {
	std::cerr << "2... fail." << std::endl;
	return 2;
    }

    if (dash.get("t3").isEmpty() )
	std::cout << "3... ok" << std::endl;
    else {
	std::cerr << "3... fail." << std::endl;
	return 3;
    }	

    return 0;
}