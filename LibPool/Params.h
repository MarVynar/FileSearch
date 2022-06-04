#ifndef PARAMS_H
#define PARAMS_H

#include <functional>
#include <string>

using namespace std;

struct Params{
	
	function<bool(char* , const string)> func;
	char* directoryToCheck;
	string fileName;
	

	Params(	function<bool(char* , const string)> func, char* directoryToCheck , string fileName );
	Params(const Params &another);
	
	Params& operator = (const Params &another);
	
	
};


#endif