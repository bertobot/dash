#include "TSTree.h"
/////////////////////////////////////////////////
TSTree::TSTree() {
    keyPeriod = 3600;
    period = 60;
}
/////////////////////////////////////////////////
void TSTree::addKey(const long& ts) {
    // we assume here that s.ts has been snapped to the minute
    long key = (ts / keyPeriod) * keyPeriod;
    TSSample *sample = root[key];

    // debug
    printf("TSTree addKey: key %d added.\n", key);

    if (!sample) {
        sample = new TSSample();
        root[key] = sample;
    }
}
/////////////////////////////////////////////////
void TSTree::addSample(const Sample &s) {
    addSample(s.ts, s.val);
}
/////////////////////////////////////////////////
void TSTree::addSample(const long &ts, const std::string &v) {
    addKey(ts);

    // we assume here that s.ts has been snapped to the minute
    long key = (ts / keyPeriod) * keyPeriod;
    int diff = (ts - key) / period;

    // diff should be the index of the minute, in relation to the key

    TSSample *sample = root[key];

    if (!sample) {
        sample = new TSSample();
    }

    sample->key = key;
    sample->sample[diff] = v;

    root[key] = sample;
}
/////////////////////////////////////////////////
std::vector<TSSample> TSTree::getRange(long ts, long te) {

    std::vector<TSSample> result;

    long startKey = (ts / keyPeriod) * keyPeriod;
    long numKeys = (te - ts) / keyPeriod;

    for (long i = startKey; i < te; i += keyPeriod) {
        // debug
        printf("TSStree getRange: looking for key %d\n", i);

        if (root[i])
            result.push_back(*root[i]);
    }

    return result;
}
/////////////////////////////////////////////////
std::vector<long*> TSTree::getRangeKeys(long ts, long te) {
    std::vector<long *> result;

    long startKey = (ts / keyPeriod) * keyPeriod;
    long numKeys = (te - ts) / keyPeriod;

    for (long i = startKey; i < te; i += keyPeriod) {
        // debug
        printf("TSStree getRange: looking for key %d\n", i);

        if (root[i]) {
            long *p = &(root[i]->key);
            result.push_back(p);
        }
        else
            result.push_back(NULL);
    }

    return result;
}
/////////////////////////////////////////////////
TSSample * TSTree::getKey(const long &k) {
    return root[k];
}
/////////////////////////////////////////////////
void TSTree::setPeriod(int p) {
    period = p;
}
/////////////////////////////////////////////////
int TSTree::getPeriod() {
    return period;
}
/////////////////////////////////////////////////
TSTree::~TSTree() {

}
/////////////////////////////////////////////////
