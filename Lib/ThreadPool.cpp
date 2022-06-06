#include "ThreadPool.h"

#include <iostream>

ThreadPool:: ThreadPool(){
	

}


void ThreadPool::start() {
	
    const int num_threads = 8; 
    threads.resize(num_threads);
    for (int i = 0; i < num_threads; i++) {
      
        threads.push_back(thread(threadLoop, this)); //
    }
}





void ThreadPool::threadLoop() {
	

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
      
      		lock_guard<mutex> lk(mtx);
      		should_terminate = true; 
		}
		mutex_condition.notify_all();
      	
	  } 

    }

}

void ThreadPool::queueJob(Params job){
    {

        lock_guard<mutex> lk(mtx);
        jobs.push(job);
        

    }
    mutex_condition.notify_one();

}





bool ThreadPool::busy() {
    bool poolbusy= false;
    {
 
        lock_guard<mutex> lk(mtx);
        poolbusy = !jobs.empty();
    }
    return poolbusy;
}


void ThreadPool::stop() {

    {
      
        lock_guard<mutex> lk(mtx);
        //should_terminate = true; ///?
    }
    mutex_condition.notify_all();
   

    
    for (vector<thread>::iterator it =threads.begin(); it !=threads.end(); it++ ){	
    
    	
	if (it->joinable())	it->join();
	} 

    threads.clear();
 
}


void ThreadPool::terminate() {
	cout<<"EnteringStop\n";
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
