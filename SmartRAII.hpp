#ifndef SMARTRAII_HPP_INCLUDED
#define SMARTRAII_HPP_INCLUDED

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

using namespace std;

/*
 This class:
 1. Demonstrates how shared_ptr can be smart enough to use as RAII in different scenarios other than just memory management.
    In this demo, we use it for closing file descriptor in normal and exception conditions.
 2. Write into input file
 3. Read from input file.
*/
class SmartRAII
{
	public:

		SmartRAII(string iFile) try :m_sFileName(iFile){
		}
		catch(const exception& ex){
		    cerr<< ex.what() << endl;
			throw runtime_error("Failed to create SmartRAII object.");
		}
		catch(...){
		    throw runtime_error("Failed to create SmartRAII object.");
		}

	    void readInputFile();
		void writeIntoInputFile();

        ~SmartRAII(){}

	private:

	    //Input File name
		string  m_sFileName;

};

#endif // SMARTRAII_HPP_INCLUDED
