#include "Params.h"

#include <cstring>

Params::Params(	function<bool(char* , const string)> func, char* dirToCheck , string fileName ){

	this->func = func;
	this->directoryToCheck = new char[strlen(dirToCheck)];
	strcpy(	this->directoryToCheck, dirToCheck);
	this->fileName = fileName;

}

Params::Params(const Params &another){
	
	this->func = another.func;
	this->directoryToCheck = new char[strlen(another.directoryToCheck)];
	strcpy(	this->directoryToCheck, another.directoryToCheck);
	this->fileName = another.fileName;
	
}
	
Params& Params::operator = (const Params &another){
	
	this->func = another.func;
	this->directoryToCheck = new char[strlen(another.directoryToCheck)];
	strcpy(	this->directoryToCheck, another.directoryToCheck);
	this->fileName = another.fileName;
	
	return *this;
}