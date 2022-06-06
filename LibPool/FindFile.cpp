#include "FindFile.h"
#include "ThreadPool.h"
#include <map>
#include <functional>
#include<memory>
#include<atomic>

#include "Params.h"

mutex mtx;
std::atomic<bool> result (false);


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
      
          	result = true;
       
         
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
	   
	 	pool.start(); 
	 	
	    while ((ent=readdir(dir)) != nullptr) {
	    	
		
	    	if (ent->d_name[0] =='$' ) continue;

	    	if(result) break;
	    	

			
	        if(ent->d_name == fileName){
	            closedir (dir);	
	            cout<<"file is found in: " << root <<endl;  
				result = true;
				
				pool.terminate();
 			
    		
    			cout<<"Root\n";
				return result; 	
				}
				
				else {
					if(result) break;
					
					
						
						
						char* path = new char[MAXPATHLENGTH];
				
						strcpy(path, root);
						strcat(path, "/");
						strcat(path, ent->d_name);
						
					
				
						function<bool(const char* , const string)> tempfunc= checkDir;   
						pool.queueJob(Params(tempfunc, path, fileName));  
				
				

				}
				
		
	    }
 
 
 

	while(!result){
		
		if(!pool.busy()){
			
			pool.stop();
			if (!result) 	cout<<"file is not found"<<endl;   
			break;
		}
		
	}
   
    pool.stop();
    
    return result;
}