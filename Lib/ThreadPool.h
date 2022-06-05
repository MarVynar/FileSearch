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
    void Start();
   // void QueueJob(const function<void()>& job);
   // void QueueJob(function<void()>& job);
   // void QueueJob(function<bool(char* , const string)>& job);
    void QueueJob(Params job);
   // void QueueJob(void (*job)());
    void Stop();
    bool busy();

private:
    void ThreadLoop();

    bool should_terminate = false;          
    mutex mtx;                  
    condition_variable mutex_condition; 
   // condition_variable isFound;
    vector<thread> threads;
    //queue<function<bool(char* , const string)> > jobs;
    queue<Params> jobs;
};




#endif