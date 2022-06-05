#include "FindFile.h"
#include "ThreadPool.h"
#include <map>
#include <functional>

#include "Params.h"

mutex mtx;
//std::atomic<bool> result (false);
bool result = false;



bool checkDir(const char*   directoryToCheck,  string fileName){
	

	if(result) {
		
	
		 return false;
	}
	
	DIR *dir; 
	struct dirent *ent;
 	
	
	
    dir = opendir(directoryToCheck);
	

    while ((ent=readdir(dir)) != nullptr) {
    	
   
    	if ( (ent->d_name[0] =='$' ) ||  (ent->d_name[0] == '.' )  ) continue;
    	if(result) {
    
			return false;
      	}
  
       
        if (ent->d_name == fileName) {

        	closedir(dir);
           	cout<<"FOUND!! In " << directoryToCheck<<endl;
           	mtx.lock();
          	result = true;
         	mtx.unlock();
    
          	return true;
		  }
		  
		  else {
		  	if(result) {
		  
			  	return false;
			}
		 
		  	char* path = new char[MAXPATHLENGTH];
		  	strcpy(path, directoryToCheck);
			strcat(path, "/");
			strcat(path, ent->d_name);
		  	
		  	if(checkDir(path , fileName)){
		  	closedir(dir);
		  
          	return true;
		  	
		  }
		 
		  }

    }

    closedir(dir);
  
    cout<<"Close Dir"<<endl;
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
	   
	 	pool.Start();
	 	
	    while ((ent=readdir(dir)) != nullptr) {
	    	
			
	    	if (ent->d_name[0] =='$' ) continue;

	    	if(result) break;
	    	
	
			
	        if(ent->d_name == fileName){
	            closedir (dir);	
	            cout<<"file is found in: " << root <<endl;  
				result = true;
				
				pool.Stop();
 			
    			closedir(dir);
    		
				return result; 
				}
				
				else {
					if(result) break;
					
					
						
						
						char* path = new char[MAXPATHLENGTH];
				
						strcpy(path, root);
						strcat(path, "/");
						strcat(path, ent->d_name);

				
						function<bool(const char* , const string)> tempfunc= checkDir;   

					pool.QueueJob(Params(tempfunc, path, fileName));
				
				 

				
				

						
					
					

				}
				

	    }
 
 	cout<<"After MLoop\n";
 	pool.Stop();
 	cout<<"After pool\n";
    closedir(dir);
    if (!result) 	cout<<"file is not found"<<endl;   

    return result;
}