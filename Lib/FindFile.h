#ifndef FINDFILE_H
#define FINDFILE_H

#include<iostream>
#include<dirent.h>
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <locale.h>
#include <thread>
#include <vector>
#include <mutex> 




#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_WIN64)
  		
  		#define ISWIN true
  		#else #define ISWIN false
#endif

#define MAXPATHLENGTH 1000

using namespace std;

//class FileFinder{
	
//extern	std::atomic<bool>  result; 
extern bool result;

//public:


	bool checkDir(const char* directoryToCheck,  string fileName);
	bool findFile(string fileName);
	
//};



#endif