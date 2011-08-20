#include "ThreadWriter.h"
/////////////////////////////////////////////////
ThreadWriter::ThreadWriter() {

}
/////////////////////////////////////////////////
ThreadWriter::ThreadWriter(const std::string &filename) {
    load(filename);
}
/////////////////////////////////////////////////
void ThreadWriter::run() {
    flush();
}
/////////////////////////////////////////////////
void ThreadWriter::flush() {
    queuelock.lock();

    std::vector<std::string>::iterator itr = queue.begin();
    for (; itr != queue.end(); itr++) {
        out << *itr << std::endl;
    }

    // clear the queue
    queue.clear();

    queuelock.unlock();
}
/////////////////////////////////////////////////
void ThreadWriter::load(const std::string &filename) {
    out.open(filename.c_str(), std::ios::app);
}
/////////////////////////////////////////////////
void ThreadWriter::add(const std::string &str) {
    queuelock.lock();

    queue.push_back(str);

    queuelock.unlock();
}
/////////////////////////////////////////////////
bool ThreadWriter::hasError() {
    if (out)
        return true;
    return false;
}
/////////////////////////////////////////////////
ThreadWriter::~ThreadWriter() {

}
/////////////////////////////////////////////////
