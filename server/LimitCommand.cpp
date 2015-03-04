#include "LimitCommand.h"

std::string LimitCommand::execute(const std::vector< std::string >& list)
{
    // TODO: log this error
    if (! mDash)
        return "error: dash is null.";

    std::stringstream ss;

    if (list.size() == 1 ) {
        ss << "age limit: " << mDash->getAgeLimit() << std::endl;
        ss << "count limit: " << mDash->getCountLimit() << std::endl;        
    }

    if (list.size() > 2) {
        long int parameter = atoi(list[2].c_str() );
        
        if (list[1] == "age")
            mDash->setAgeLimit(parameter);

        else if (list[1] == "count")
            mDash->setCountLimit(parameter);
    }

    if (list.size() > 1) {
        if (list[1] == "age")
            ss << "age limit: " << mDash->getAgeLimit() << std::endl;
        
        else if (list[1] == "count")
            ss << "count limit: " << mDash->getCountLimit() << std::endl;
    }

    return ss.str();
}

// vim: ts=4:sw=4:expandtab
