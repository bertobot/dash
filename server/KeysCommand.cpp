#include "KeysCommand.h"

std::string KeysCommand::execute(const std::vector< std::string >& list)
{
    // TODO: log this error
    if (! mDash)
        return "error: dash is null.";

    std::string response;

    for (unsigned int i = 0; i < mDash->getKeys().size(); i++)
        response += mDash->getKeys()[i] + '\n';

    return response;
}

// vim: ts=4:sw=4:expandtab
