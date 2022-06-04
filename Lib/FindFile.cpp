#include "FindFile.h"
#include <map>



mutex mtx;
//std::atomic<bool> result (false);
bool result = false;
//std::atomic<vector<int> > finishedFuncs;
//vector<int> finishedFuncs;
map <thread::id , bool> finishedFuncs ;
//map <int , bool > finishedFuncs ;

bool checkDir(const char* const  directoryToCheck, const string fileName){
	
	if(result) {
		
		finishedFuncs[this_thread::get_id()] = true;
		 return false;
	}
	
	DIR *dir; 
	struct dirent *ent;
 	
	
	
    dir = opendir(directoryToCheck);

    while ((ent=readdir(dir)) != nullptr) {
    	
    	
    	if ( (ent->d_name[0] =='$' ) ||  (ent->d_name[0] == '.' )  ) continue;
    	if(result) {
    		finishedFuncs[this_thread::get_id()] = true;
			return false;
      	}
  
       	
        if (ent->d_name == fileName) {

        	closedir(dir);
           	cout<<"FOUND!! In " << directoryToCheck<<endl;
           	mtx.lock();
          	result = true;
         	mtx.unlock();
         	finishedFuncs[this_thread::get_id()] = true;
          	return true;
		  }
		  
		  else {
		  	if(result) {
		  		finishedFuncs[this_thread::get_id()] = true;
			  	return false;
			}
		 
		  	char* path = new char[MAXPATHLENGTH];
		  	strcpy(path, directoryToCheck);
			strcat(path, "/");
			strcat(path, ent->d_name);
		  	
		  	if(checkDir(path , fileName)){
		  	closedir(dir);
		  	finishedFuncs[this_thread::get_id()] = true;
          	return true;
		  	
		  }
		 
		  }

    }

    closedir(dir);
    finishedFuncs[this_thread::get_id()] = true;
	return false;
	
}


bool findFile(string fileName) {
	

	
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

						if ( !threads.empty()){
							
							for (vector<thread>::iterator it =threads.begin(); it !=threads.end();  ){
						
						
							//	if ( finishedFuncs[it->get_id()] == true) {

							if ( (finishedFuncs.find(it->get_id()))->second == true) {
								
									mtx.lock();
									cout<<"Erasing " <<it->get_id()<<"+ "<< (finishedFuncs.find(it->get_id()))->second<<endl;
								//	threads.erase(it); ///to paste new process here?
									cout<<"Erased " <<it->get_id()<<"+ "<< (finishedFuncs.find(it->get_id()))->second<<endl;
								//	it++; //test
									mtx.unlock();
								}
								else {
									it++;
								}
													
						
							}
							
							int size = threads.size();
							
//							for (int it =0; it <size; it++ ){	
//						
//								if ( finishedFuncs[(threads.begin()+it)->get_id()] == true) {
//								
//									mtx.lock();
//									threads.erase(threads.begin()+it);
//								//	cout<<"Erased " <<(threads.begin()+it)->get_id()<<endl;
//									mtx.unlock();
//								}
//													
//						
//							}
								
						}
						
					
					
				/*/if (threads.size() >= maxThreads){
						
					
					/////Not accurate alternative for checking each thread/////
						for (vector<thread>::iterator it =threads.begin(); it !=threads.end(); it++ ){	
						
						it->join();
						threads.erase(it);

							
						
						} 
						
						
						
					}*/
				
					{
						char* path = new char[MAXPATHLENGTH];
				
						strcpy(path, root);
						strcat(path, "/");
						strcat(path, ent->d_name);
					
					//	thread tempThread (checkDir, (path), (fileName));
					//	int curSize= threads.size();
					//	finishedFuncs.insert(make_pair<curSize, false>);
					//	finishedFuncs.emplace(curSize, false);
						threads.push_back(thread (checkDir, (path), (fileName)));
						//	threads.push_back(tempThread);
						//const std::thread::id tmpId = threads.back().get_id();
						finishedFuncs.emplace(threads.back().get_id(), false);
						
	
	
						if (result)	{
									
							for (vector<thread>::iterator it =threads.begin(); it !=threads.end(); it++ ){	(*it).join();	}  
	  				 		closedir(dir);
							return result;
						}
						
					}
					

				}
	    }
 
 	for (vector<thread>::iterator it =threads.begin(); it !=threads.end(); it++ ){	(*it).join();	}  
 	if (!result) 	cout<<"file is not found"<<endl;   
    closedir(dir);
    return result;
}