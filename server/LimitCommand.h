#ifndef __LimitCommand_h_
#define __LimitCommand_h_

#include "../core/Dash.h"
#include <ControlPort/Command.h>
#include <stdlib.h>
#include <sstream>

class LimitCommand : public Command {
protected:
    Dash *dash;
    
public:
    LimitCommand();

    std::string execute(const std::vector< std::string >& list);
    void associateDash(Dash *d);

    virtual ~LimitCommand();
};

#endif
