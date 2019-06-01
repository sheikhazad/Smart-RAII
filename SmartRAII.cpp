#include "SmartRAII.hpp"
#include <fstream>
#include <memory> // RAII For file

////////////////////////////////////////////////////////////////////////////////
//This method shows how shared_ptr can be used as RAII for ifstream
//and avoids exception handling to close file descriptor
////////////////////////////////////////////////////////////////////////////////
void SmartRAII::readInputFile()
{
	string sLine;
	ifstream inFile;

	inFile.open(m_sFileName.c_str());
	if (inFile.is_open())
    {
        //1. RAII for file, file will be closed in normal flow and exception.
        //2. RAII enables us to avoid exception handling just to close file.
        //3. shared_ptr will never call it's own deleter but will be replaced by local lambda function provided.
        //4. So, inFile object is never deleted by shared_ptr but closed only.
        //5. inFile will be deleted only when it goes out of scope.
        shared_ptr<ifstream> ifp = shared_ptr<ifstream>(&inFile,[](ifstream* fp) -> void
                                                                {   cout<< "\nReader: Closing file by shared_ptr" << endl;
                                                                    fp->close();
                                                                });
        cout<<"Reading from file:" << endl << endl;
        while( getline(*ifp, sLine) )
        {
           cout<< sLine << endl;
        }
    }
    else{
	    throw runtime_error("Unable to open file");
	}
}
////////////////////////////////////////////////////////////////////////////////
//This method shows how shared_ptr can be used as RAII for ofstream
//and avoids exception handling to close file descriptor
////////////////////////////////////////////////////////////////////////////////
void SmartRAII::writeIntoInputFile()
{
	string sLine;
	ofstream ofFile;
	ofFile.open(m_sFileName.c_str(), std::ios::app);

	if (ofFile.is_open())
    {
        //1. RAII for file, file will be closed in normal flow and exception.
        //2. RAII enables us to avoid exception handling just to close file.
        //3. shared_ptr will never call it's own deleter but will be replaced by local lambda function provided.
        //4. So, ofFile object is never deleted by shared_ptr but closed only.
        //5. ofFile will be deleted only when it goes out of scope.
        shared_ptr<ofstream> ofp = shared_ptr<ofstream>(&ofFile,[](ofstream* fp) -> void
                                                                {   cout<< "\n Writer: Closing file by shared_ptr" << endl;
                                                                    fp->close();
                                                                });

        //In case end of the file doesn't start at new line, then start writing at new line
        cout<<"Enter what you want to write into file: " << endl << endl;
        *ofp << "\r\n";
        getline(cin, sLine);

        //Same as ofFile <<  sLine << endl;
        *ofp <<  sLine << endl;
        cout<<"Written successfully into file" << endl;
    }
    else{
	    throw runtime_error( "Unable to open file");
	}
}


int main(int argc, char** argv)
{
	try
	{
		if(argc != 2){
			throw runtime_error("ERROR: Number of command-line arguments should be 1, which is Input file to read/write.\nUsage: ./SmartRAII.exe <InputFile> \n");
		}

		SmartRAII aSmartRAII(argv[1]);

		char ch;
	    do{
                cout << "\nPls select what you want to do: " << endl;
                cout << "1. Want to write into file, Enter W : " << endl;
                cout << "2. Want to  read from file, Enter R : " << endl;
                cout << "3. Want to exit, Enter E : " << endl;
                cout << "Choose one (W/R/E) : ";

                cin >> ch;
                cin.clear();
                cin.ignore(1);

                switch(ch)
                {   //For W, R and default cases, in performance critical system "continue" can be used instead of "break".
                    //Using "continue" will avoid overhead for checking while() condition.
                    //However I have chosen "break" instead of "continue" as I prefer clarity over performance.

                    case 'W': aSmartRAII.writeIntoInputFile();
                              break;
                    case 'R': aSmartRAII.readInputFile();
                              break;
                    case 'E': cout<<"Successfully exited!" <<  endl;
                              break;
                    default:  cerr << "Wrong selection, pls select right choice:" <<endl;
                              break;
                }//Ends Switch()

            }while (ch != 'E');
	}
	catch(const exception& ex){
	    cerr <<"\nEXCEPTION - " << ex.what() << endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
