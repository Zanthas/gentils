#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	vector<string> files;

	bool flagN = false;

	for(int i = 1; i < argc; i++)
	{
		string curarg = argv[i];
		if(curarg[0] == '-')
		{
			if(curarg == "-v" || curarg == "--version")
			{
				cout << "gcat 0.1" << endl;
				return 0;
			}
			else if(curarg == "-h" || curarg == "--help")
			{
				cout << "Usage: cat file1 [file2] ... [-n]" << endl;
				cout << "-n: number lines" << endl;
				return 0;
			}
			else if(curarg == "-n" || curarg == "--number")
			{
				flagN = true;
			}
			else
			{
				cout << "Option " << curarg << " not recognized." << endl;
				return -1;
			}
		}
		else
		{
			files.push_back(curarg);
		}
	}

	long long curline = 0;

	for(int i = 0; i < files.size(); i++)
	{
		ifstream inFile;
		inFile.open(files[i].c_str(), ios::in);

		if(inFile)
		{
			string in;
			while(getline(inFile, in))
			{
				if(flagN)
				{
					curline++;
					cout << curline << ". ";
				}
				cout << in << endl;
			}
		}
	}
}
