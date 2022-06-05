#include "ThreadPool.h"

#include <iostream>

ThreadPool:: ThreadPool(){
	
	//Start();
}


void ThreadPool::Start() {
	
    const int num_threads = 8; 
    threads.resize(num_threads);
    for (int i = 0; i < num_threads; i++) {
      
        threads.push_back(thread(ThreadLoop, this)); //
    }
}





void ThreadPool::ThreadLoop() {
	

    while (true) {
    	

       function<bool(char* , string)> job;
       char*   directoryToCheck;
	   string fileName;
        {
            std::unique_lock<std::mutex> lock(mtx);
            mutex_condition.wait(lock, [this] {
                return !jobs.empty() || should_terminate;
            });
            if (should_terminate) {
                return;
            }

            job = jobs.front().func;
            directoryToCheck= jobs.front().directoryToCheck;
           fileName = jobs.front().fileName;

            jobs.pop();

        }

      if(job( directoryToCheck, fileName)){
      	

      	{
      		//unique_lock<mutex> lock(mtx); //?
      		lock_guard<mutex> lk(mtx);
      		should_terminate = true;
		}
		mutex_condition.notify_all();
      	
	  } 

    }

}



void ThreadPool::QueueJob(Params job){
    {
        //std::unique_lock<std::mutex> lock(mtx);
        lock_guard<mutex> lk(mtx);
        jobs.push(job);
        

    }
    mutex_condition.notify_one();

}





bool ThreadPool::busy() {
    bool poolbusy= false;
    {
        //std::unique_lock<std::mutex> lock(mtx);
        lock_guard<mutex> lk(mtx);
        poolbusy = jobs.empty();
    }
    return poolbusy;
}


void ThreadPool::Stop() {

    {
        //unique_lock<mutex> lock(mtx);
        lock_guard<mutex> lk(mtx);
        should_terminate = true;
    }
    mutex_condition.notify_all();
   

    
    for (vector<thread>::iterator it =threads.begin(); it !=threads.end(); it++ ){	
    

	if (it->joinable())	it->join();
	} 

    threads.clear();

}

