#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <thread>
#include <forward_list>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

#include "Params.h"


using namespace std;

class ThreadPool {
public:
	
	ThreadPool();
    void start();

    void queueJob(Params job);

    void stop();
    void terminate();
    bool busy();

private:
    void threadLoop();

    bool should_terminate = false;          
    mutex mtx;                  
    condition_variable mutex_condition; 

    vector<std::thread> threads;
 
    queue<Params> jobs;
};




#endif