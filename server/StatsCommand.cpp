#include "StatsCommand.h"

StatsCommand::StatsCommand()
{
    name = "stats";
    dash = NULL;
}

void StatsCommand::associateDash(Dash* d)
{
    dash = d;
}

std::string StatsCommand::execute(const std::vector< std::string >& list)
{
    // TODO: log this error
    if (! dash)
        return "error: dash is null.";

    std::vector<std::string> keys = dash->getKeys();

    std::stringstream ss;

    for (unsigned int i = 0; i < keys.size(); i++) {
        Value v = dash->peek(keys[i]);
        ss << keys[i] << " " << v.timestamp << " " << v.count << " ";

        v.isEmpty() ? ss << 0 : ss << 1;

        ss << std::endl;
    }
    

    return ss.str();
}

StatsCommand::~StatsCommand()
{
    dash = NULL;
}
