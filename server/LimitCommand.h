#ifndef __LimitCommand_h_
#define __LimitCommand_h_

#include "../core/Dash.h"
#include <ControlPort/Command.h>
#include <stdlib.h>
#include <sstream>

class LimitCommand : public Command {
public:
    LimitCommand(Dash *dash) : Command("limit", "control limit factor on keys expiry") { mDash = dash; }

    virtual ~LimitCommand() { mDash = NULL; }

    std::string execute(const std::vector< std::string >& list);

private:
    Dash *mDash;

};

#endif
// vim: ts=4:sw=4:expandtab
