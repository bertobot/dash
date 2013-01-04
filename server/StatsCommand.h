#ifndef __StatsCommand_h_
#define __StatsCommand_h_

#include "../core/Dash.h"
#include <ControlPort/Command.h>

#include <sstream>

class StatsCommand : public Command {
protected:
    Dash *dash;
    
public:
    StatsCommand();

    std::string execute(const std::vector< std::string >& list);
    void associateDash(Dash *d);

    virtual ~StatsCommand();
};

#endif
