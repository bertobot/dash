#ifndef __ThreadWriter_h_
#define __ThreadWriter_h_

#include <MyThread/thread.h>
#include <MyThread/mutex.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>

/////////////////////////////////////////////////
class ThreadWriter {
private:
    std::vector<std::string> queue;
    std::ofstream out;
    mutex queuelock;

public:
    ThreadWriter();
    ThreadWriter(const std::string &);

    virtual void run();
    // virtual void stop();

    void load(const std::string &);
    void add(const std::string&);
    bool hasError();
    void flush();

    virtual ~ThreadWriter();
};

#endif
