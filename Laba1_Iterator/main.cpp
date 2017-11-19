#include <iostream>
#include <string>

#include "Iterator.h"

void main(int argc, char *argv[])
{
	std::string FileMask;
	FileIterator * it = new FileIterator();

	if (argc > 1)
		FileMask = argv[1];
	else
	{
		std::cout << "Enter a drive, directory, and/or file mask to list ([drive:][path]filemask) -> " << std::endl;
		std::cin >> FileMask;
		std::cout << std::endl;
		if (!FileMask.length())
			return;
	}


	it->setFileMask(FileMask);
	FileItem *file;

	while (it->hasMore())
	{
		file = it->Next();
		file->Show();

	}
}