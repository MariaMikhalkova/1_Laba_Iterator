#include <io.h>
#include <iostream>
#include <string>
using namespace std;

class FileItem

{
	string name;
	string path;

public:
	FileItem() {};

	FileItem(const string& namee, const string& pathh)
	{
		name == namee;
		path == pathh;
	}
};

class FileIterator
{
	FileItem * cache;
	string FileMask;

	FileIterator *it2;//итератор для внутренних проходов)

	inline bool IsDirectory(const _finddata_t &FindData);

public:
	FileIterator() {};
	FileIterator(const string & _fileMask);

	bool hasMore();

	void DisplayFiles(const string& FileMask);
	void FileIterator::setFileMask(const string & mask)
	{
		FileMask = mask;
	}
	bool Maska(const string mask, const string file);
};






