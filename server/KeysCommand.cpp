#include "KeysCommand.h"

KeysCommand::KeysCommand()
{
    name = "keys";
    dash = NULL;
}

void KeysCommand::associateDash(Dash* d)
{
    dash = d;
}

std::string KeysCommand::execute(const std::vector< std::string >& list)
{
    // TODO: log this error
    if (! dash)
        return "error: dash is null.";

    std::string response;

    for (unsigned int i = 0; i < dash->getKeys().size(); i++)
        response += dash->getKeys()[i] + '\n';

    return response;
}

KeysCommand::~KeysCommand()
{
    dash = NULL;
}
