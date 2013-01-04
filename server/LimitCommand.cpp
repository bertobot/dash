#include "LimitCommand.h"

LimitCommand::LimitCommand()
{
    name = "limit";
    dash = NULL;
}

void LimitCommand::associateDash(Dash* d)
{
    dash = d;
}

std::string LimitCommand::execute(const std::vector< std::string >& list)
{
    // TODO: log this error
    if (! dash)
        return "error: dash is null.";

    std::stringstream ss;

    if (list.size() == 1 ) {
        ss << "age limit: " << dash->getAgeLimit() << std::endl;
        ss << "count limit: " << dash->getCountLimit() << std::endl;        
    }

    if (list.size() > 2) {
        long int parameter = atoi(list[2].c_str() );
        
        if (list[1] == "age")
            dash->setAgeLimit(parameter);

        else if (list[1] == "count")
            dash->setCountLimit(parameter);
    }

    if (list.size() > 1) {
        if (list[1] == "age")
            ss << "age limit: " << dash->getAgeLimit() << std::endl;
        
        else if (list[1] == "count")
            ss << "count limit: " << dash->getCountLimit() << std::endl;
    }

    return ss.str();
}

LimitCommand::~LimitCommand()
{
    dash = NULL;
}
