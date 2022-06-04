#include "FindFile.h"
#include "ThreadPool.h"
#include <map>
#include <functional>

#include "Params.h"

mutex mtx;
//std::atomic<bool> result (false);
bool result = false;
//std::atomic<vector<int> > finishedFuncs;
//vector<int> finishedFuncs;
//map <thread::id , bool> finishedFuncs ;///
//map <int , bool > finishedFuncs ;

bool checkDr(const char*   directoryToCheck, const string fileName){

	for (int i =0; i<100; i++){
		
		cout<<"Func1 "<<i<<endl;
	}
	return true;
}
bool checkDir(const char*   directoryToCheck, const string fileName){
	
	cout<<"Inside\n";
	if(result) {
		
		//finishedFuncs[this_thread::get_id()] = true;
		 return false;
	}
	
	DIR *dir; 
	struct dirent *ent;
 	
	
	
    dir = opendir(directoryToCheck);
	
	cout<<"Before Job Cycle\n";
    while ((ent=readdir(dir)) != nullptr) {
    	
    	cout<<"Job Cycle\n";
    	if ( (ent->d_name[0] =='$' ) ||  (ent->d_name[0] == '.' )  ) continue;
    	if(result) {
    	//	finishedFuncs[this_thread::get_id()] = true;
			return false;
      	}
  
       	cout<<"Name: "<<ent->d_name<<endl;
        if (ent->d_name == fileName) {

        	closedir(dir);
           	cout<<"FOUND!! In " << directoryToCheck<<endl;
         //  	mtx.lock();
          	result = true;
         //	mtx.unlock();
         //	finishedFuncs[this_thread::get_id()] = true;
          	return true;
		  }
		  
		  else {
		  	if(result) {
		  ///		finishedFuncs[this_thread::get_id()] = true;
			  	return false;
			}
		 
		  	char* path = new char[MAXPATHLENGTH];
		  	strcpy(path, directoryToCheck);
			strcat(path, "/");
			strcat(path, ent->d_name);
		  	
		  	if(checkDir(path , fileName)){
		  	closedir(dir);
		  //	finishedFuncs[this_thread::get_id()] = true;
          	return true;
		  	
		  }
		 
		  }

    }

    closedir(dir);
    //finishedFuncs[this_thread::get_id()] = true;
	return false;
	
}


bool findFile(string fileName) {
	
	ThreadPool pool;
	
	DIR *dir; 
	char *root;
	
	const int maxThreads = 20;
	vector<thread> threads;

	
	if (ISWIN) {
	 root = "C:/";	
	}  
	else   root = "/";
	
	result = false;
	struct dirent *ent;
	 	
	    dir = opendir(root);
	   
	 
	    while ((ent=readdir(dir)) != nullptr) {
	    	

	    	if (ent->d_name[0] =='$' ) continue;

	    	if(result) break;

	        if(ent->d_name == fileName){
	            closedir (dir);	
	            cout<<"file is found in: " << root <<endl;  
				result = true;
				return result; 	
				}
				
				else {
					if(result) break;
					
						pool.Start();
						
						char* path = new char[MAXPATHLENGTH];
				
						strcpy(path, root);
						strcat(path, "/");
						strcat(path, ent->d_name);

				
					//	function<bool(const char* , const string)> tempfunc= checkDir;   
						function<bool(const char* , const string)> tempfunc= checkDr;   
					
					//	tempfunc(path, fileName);
					//	pool.QueueJob(tempfunc( path, fileName));////
					pool.QueueJob(Params(tempfunc, path, fileName));
				
				 

				
				

						
					
					

				}
	    }
 
 
 	if (!result) 	cout<<"file is not found"<<endl;   
    closedir(dir);
    pool.Stop();
    return result;
}