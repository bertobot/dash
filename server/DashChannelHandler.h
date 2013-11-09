#ifndef __DashChannelHandler_h_
#define __DashChannelHandler_h_

#include "../core/Dash.h"

#include <netty++/ChannelHandler.h>
#include <libstrmanip++/utils.h>

#include <iostream>
#include <vector>
#include <errno.h>
#include <string.h>

class DashChannelHandler : public ChannelHandler {
public:
    DashChannelHandler(Dash *dash);

    virtual ~DashChannelHandler();

    void onMessageReceived(Channel &channel);

private:
    Dash *dash;
};

#endif

// vim: ts=4:sw=4:expandtab
