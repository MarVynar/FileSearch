#include "ThreadPool.h"

#include <iostream>

ThreadPool:: ThreadPool(){
	
	//Start();
}


void ThreadPool::Start() {
	
    const int num_threads = 3; 
    threads.resize(num_threads);
    for (int i = 0; i < num_threads; i++) {
      
        threads.push_back(thread(ThreadLoop, this)); //
    }
}





void ThreadPool::ThreadLoop() {
	
//	cout<<"Entering\n";
    while (true) {
    	
    //	cout<<"EnteringLoop\n";
       function<bool(char* , const string)> job;
        {
            std::unique_lock<std::mutex> lock(mtx);
            mutex_condition.wait(lock, [this] {
                return !jobs.empty() || should_terminate;
            });
            if (should_terminate) {
                return;
            }
         //   cout<<"Jobs\n";
            job = jobs.front();
         //   cout<<"Jobs added\n";
            jobs.pop();
         //   cout<<"Jobs removed\n";
        }
      //  cout<<"After\n";
        job("C:/", "11.txt");
    }
   // cout<<"After Loop\n";
}


//void ThreadPool::QueueJob(const std::function<void()>& job) {
//void ThreadPool::QueueJob( std::function<void()>& job) {
//void ThreadPool::QueueJob(void (*job)()){
void ThreadPool::QueueJob(function<bool(char* , const string)>& job){

    {
        std::unique_lock<std::mutex> lock(mtx);
        jobs.push(job);
        
       // function<void()> tmpJob = job;
       // jobs.push(tmpJob);
    }
    mutex_condition.notify_one();
}





bool ThreadPool::busy() {
    bool poolbusy= false;
    {
        std::unique_lock<std::mutex> lock(mtx);
        poolbusy = jobs.empty();
    }
    return poolbusy;
}


void ThreadPool::Stop() {
	cout<<"EnteringStop\n";
    {
        unique_lock<mutex> lock(mtx);
        should_terminate = true;
    }
    mutex_condition.notify_all();
   
    cout<<"Stopping Vecs\n";
    
    for (vector<thread>::iterator it =threads.begin(); it !=threads.end(); it++ ){	
    
    	 cout<<"Into Stopping Vecs\n";
		//(*it).join();
		it->join();
	} 
	cout<<"Stopped Vecs\n"; 
    threads.clear();
    cout<<"Stoped\n";
}

