#ifndef THREADTHS_H_INCLUDED
#define THREADTHS_H_INCLUDED

#include "dismantler.h"
#include <mutex>
#include <condition_variable>
#include <queue>

class threadThs {

public:
    explicit threadThs(const std::string &f_in, const std::string &f_ou){
        file_name = f_in;
        file_name_o = f_ou;
        DIS = new dismatler(file_name, file_name_o);
    }
    void run();
    bool isExit, isDone;
private:
    std::string file_name, file_name_o;
    dismatler *DIS;
    void producer();
    void consumer();
};

#endif // THREADTHS_H_INCLUDED
