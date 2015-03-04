#include "StatsCommand.h"

std::string StatsCommand::execute(const std::vector< std::string >& list)
{
    // TODO: log this error
    if (! mDash)
        return "error: dash is null.";

    std::vector<std::string> keys = mDash->getKeys();

    std::stringstream ss;

    for (unsigned int i = 0; i < keys.size(); i++) {
        Value v = mDash->peek(keys[i]);
        ss << keys[i] << " " << v.timestamp << " " << v.count << " ";

        v.isEmpty() ? ss << 0 : ss << 1;

        ss << std::endl;
    }
    

    return ss.str();
}

// vim: ts=4:sw=4:expandtab
