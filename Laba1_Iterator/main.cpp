#include <io.h>
#include <string>
#include <iostream>
#include "Iterator.h"
using namespace std;

void main(int argc, char *argv[])
{
	string FileMask;
	FileIterator * it = new FileIterator();

	if (argc > 1)
		FileMask = argv[1];
	else
	{
		cout << "Enter a drive, directory, and/or file mask to list ([drive:][path]filemask): " << endl;
		cin >> FileMask;
		if (!FileMask.length())
			return;
	}

	it->DisplayFiles(FileMask);

}