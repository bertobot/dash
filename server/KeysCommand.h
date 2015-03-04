#ifndef __KeysCommand_h_
#define __KeysCommand_h_

#include "../core/Dash.h"
#include <ControlPort/Command.h>

class KeysCommand : public Command {
public:
    KeysCommand(Dash *dash) : Command("keys", "show all keys") { mDash = dash; }

    virtual ~KeysCommand() { mDash = NULL; }

    std::string execute(const std::vector< std::string >& list);

private:
    Dash *mDash;

};

#endif
// vim: ts=4:sw=4:expandtab
