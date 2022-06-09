#ifndef THREADPOOL_H
#define THREADPOOL_H

<<<<<<< Updated upstream
#define _WIN32_WINNT 0x0501
=======
//#define _WIN32_WINNT 0x0501
>>>>>>> Stashed changes

//#include <thread> //Usual Compiler
#include "mingw.thread.h" //MingW
#include <forward_list>
#include <vector>
//#include <mutex>//Usual Compiler
//#include <condition_variable>//Usual Compiler
#include "mingw.mutex.h" //MingW
#include "mingw.condition_variable.h" //MingW
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

    vector<thread> threads;
 
    queue<Params> jobs;
};




#endif