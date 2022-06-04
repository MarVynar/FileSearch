#include "FindFile.h"
#include "ThreadPool.h"
#include <map>
#include <functional>



mutex mtx;
//std::atomic<bool> result (false);
bool result = false;
//std::atomic<vector<int> > finishedFuncs;
//vector<int> finishedFuncs;
//map <thread::id , bool> finishedFuncs ;///
//map <int , bool > finishedFuncs ;


bool checkDir(const char*   directoryToCheck, const string fileName){
	
	if(result) {
		
		//finishedFuncs[this_thread::get_id()] = true;
		 return false;
	}
	
	DIR *dir; 
	struct dirent *ent;
 	
	
	
    dir = opendir(directoryToCheck);

    while ((ent=readdir(dir)) != nullptr) {
    	
    	
    	if ( (ent->d_name[0] =='$' ) ||  (ent->d_name[0] == '.' )  ) continue;
    	if(result) {
    	//	finishedFuncs[this_thread::get_id()] = true;
			return false;
      	}
  
       	
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

				
						function<bool(const char* , const string)> tempfunc= checkDir;   
					
						tempfunc(path, fileName);
					//	pool.QueueJob(tempfunc( path, fileName));////
				//	pool.QueueJob(tempfunc, path, fileName);
				
				 

				
				

						
					
					

				}
	    }
 
 
 	if (!result) 	cout<<"file is not found"<<endl;   
    closedir(dir);
    pool.Stop();
    return result;
}