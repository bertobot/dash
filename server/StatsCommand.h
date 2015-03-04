#ifndef __StatsCommand_h_
#define __StatsCommand_h_

#include "../core/Dash.h"
#include <ControlPort/Command.h>
#include <iostream>
#include <sstream>

class StatsCommand : public Command {
public:
    StatsCommand(Dash *dash) : Command("stats", "show stats on keys") { mDash = dash; }

    virtual ~StatsCommand() { mDash = NULL; }

    std::string execute(const std::vector< std::string >& list);

private:
    Dash *mDash;

};

#endif
// vim: ts=4:sw=4:expandtab
