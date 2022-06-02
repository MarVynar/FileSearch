#include "FindFile.h"



//bool FileFinder::checkDr(){}
bool result = false;

bool checkDir(const char* const  directoryToCheck, const string fileName){
	
	if(result) return false;
	
	DIR *dir; 
	struct dirent *ent;
 	
	
	
    dir = opendir(directoryToCheck);

    while ((ent=readdir(dir)) != nullptr) {
    	
    	
    	if ( (ent->d_name[0] =='$' ) ||  (ent->d_name[0] == '.' )  ) continue;
    	
       			
        if (ent->d_name == fileName) {

        	closedir(dir);
           	cout<<"FOUND!! In " << directoryToCheck<<endl;
          	result = true;
         
          	return true;
		  }
		  
		  else {
		  	if(result) return false;
		 
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
	
	DIR *dir; 
	char *root;
	//bool  result=false; 
	const int maxThreads = 8;
	vector<thread> threads;
	//result=false;
	
	if (ISWIN) {
	 root = "C:/";	
	}  
	else   root = "/";
	
	struct dirent *ent;
	 
	
	    dir = opendir(root);
	 
	    while ((ent=readdir(dir)) != nullptr) {
	    		
	    	if (ent->d_name[0] =='$' ) continue;
	    	
	        printf("%s\n", ent->d_name);
	        if(ent->d_name == fileName){
	            closedir (dir);	
	            cout<<"file is found in" << root <<endl;   	
				}
				
				else {
	
					//if (threads.size() < maxThreads)
					{
						char* path = new char[MAXPATHLENGTH];
				
						strcpy(path, root);
						strcat(path, "/");
						strcat(path, ent->d_name);
					
				//	thread tempthread(checkDr);
					threads.push_back(thread (checkDir, (path), (fileName)));
				
	
	
					if (result)
						{
						
					
					
				
							for (vector<thread>::iterator it =threads.begin(); it !=threads.end(); it++ ){	(*it).join();	}  
	  				 		closedir(dir);
							return result;
						}
						
					}
					
//					else {
//						
//						for (vector<thread>::iterator it =threads.begin(); it !=threads.end(); it++ ){	
//						
//					
//						}  
//					}
				}
	    }
 
 	for (vector<thread>::iterator it =threads.begin(); it !=threads.end(); it++ ){	(*it).join();	}  
 	
 	cout<<"file is not found"<<endl;   
    closedir(dir);
    return result;
}