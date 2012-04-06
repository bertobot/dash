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

    KVStore dirty = dash.getDirtyValues();

    for (KVStore::iterator itr = dirty.begin(); itr != dirty.end(); itr++) {
        std::cout << itr->first << " is dirty." << std::endl;
    }

    return 0;
}
