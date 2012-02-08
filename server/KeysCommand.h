#ifndef __KeysCommand_h_
#define __KeysCommand_h_

#include "../core/Dash.h"
#include <ControlPort/Command.h>

class KeysCommand : public Command {
protected:
    Dash *dash;
    
public:
    KeysCommand();

    std::string execute(const std::vector< std::string >& list);
    void associateDash(Dash *d);

    virtual ~KeysCommand();
};

#endif
