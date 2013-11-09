#include "DashChannelHandler.h"
/////////////////////////////////////////////////
DashChannelHandler::DashChannelHandler(Dash *dash) : ChannelHandler() {
    this->dash = dash;
}
/////////////////////////////////////////////////
void DashChannelHandler::onMessageReceived(Channel &channel) {
	std::string input = channel.readLine();	    
    std::vector<std::string> tokens = split(' ', input);

    /*
     * protocols supported:
     * 
     * put <key> <value>
     * get <key>
     * 
     * search <key|value> <regular expression>
     *
     */

    //respond("ok - " + input);

    if (tokens[0] == "put") {
        if (tokens.size() < 3) {
            channel.writeLine("nok");
            return;
        }

        dash->put(tokens[1], ::join(' ', tokens, 2) );

        channel.writeLine("ok");
    }

    else if (tokens[0] == "get") {
        if (tokens.size() != 2) {
            channel.writeLine("nok");
            return;
        }

        Value v = dash->get(tokens[1]);
        std::stringstream ss;
        ss << v.value.length() << '\n';

        channel.writeLine(ss.str() + v.value );
    }
}
/////////////////////////////////////////////////
DashChannelHandler::~DashChannelHandler() {
    dash = NULL;
}
/////////////////////////////////////////////////
// vim: ts=4:sw=4:expandtab
