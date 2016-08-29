#include <iostream>
#include "Substitute.h"
using namespace std;

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		cout << "invalid number of arguments! #: " << argc << endl;
	}
	string old_string = argv[1];
	string new_string = argv[2];

	Substitute *substitute = new Substitute(argv[3]);
	substitute->substitute(old_string, new_string);
	delete substitute;
	return 0;
}	
