#include<iostream>
#include <string>

#include "FindFile.h"



using namespace std;


bool checkLetters(string filename){
	
	for (int i =0; i< filename.size(); i++){
			
			if (! ( ((filename[i] >=48)&& (filename[i] <=57) ) || ((filename[i] >=65)&& (filename[i] <=90) ) || ((filename[i] >=97)&& (filename[i] <=122) ) || (filename[i] ==46) )  ) {
	
				
				cout<<"Please enter correct file name with its extension"<<endl;
				 return false;
			}
			
		}
	return true;
}

string getFileName(){
	
	string fileName; 

	
	while (true){
		cin>>fileName; 
		
		if (!checkLetters(fileName)) {continue;	}
		
		std::size_t firstOccurrence = fileName.find(".");
		std::size_t lastOccurrence = fileName.rfind(".");
		if ((firstOccurrence== lastOccurrence) && (firstOccurrence!= string::npos)) { break;	}
		else {	cout<<"Please enter correct file name with its extension"<<endl;}
		
	}
		
	return fileName; 
}




int main() 
{


		while (true){
			
			cout<<"Please enter file name with its extension"<<endl;  
			string fileName= getFileName();  	
			findFile(fileName);
			char ch;
			do{
				cout <<"Do you want more?Y/N"<<endl;
				cin>>ch;	
			}while(!((ch== 'y')||(ch== 'Y')||(ch== 'n')||(ch== 'N')));

			if(toupper(ch)== 'N') break;
		}

 return 0;

}