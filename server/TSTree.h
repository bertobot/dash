#ifndef __ts_tree_h_
#define __ts_tree_h_
/////////////////////////////////////////////////
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
/////////////////////////////////////////////////
struct Sample {
    long ts;
    std::string val;
};

struct TSSample {
    long key;
    std::string sample[60];

    TSSample() {
		/*
        for (int i = 0; i < 60; i++) {
            sample[i] = -1;
        }
		*/
    }

    std::vector<std::string> toString() {
        std::vector<std::string> result;
        std::string string;

        std::stringstream ss;

        for (int i = 0; i < 60; i++) {
            ss.str("");

            ss << (key + (i * 60) ) << "," << sample[i];

            result.push_back(ss.str() );
        }

        return result;
    }
};

//typedef std::map<long, double> TSSample;
typedef std::map<long, TSSample * > TSNode;
/////////////////////////////////////////////////
class TSTree {
    public:

        TSTree();
        TSTree(int);

        void addKey(const long&);

        void addSample(const Sample&);
        void addSample(const long&, const std::string&);

        void setPeriod(int);
        int getPeriod();

        std::vector<TSSample> getRange(long ts, long te);
        std::vector<long *> getRangeKeys(long ts, long te);

        TSSample * getKey(const long&);

        virtual ~TSTree();

    protected:
        TSNode root;

        long keyPeriod;
        long period;

};
/////////////////////////////////////////////////
#endif
