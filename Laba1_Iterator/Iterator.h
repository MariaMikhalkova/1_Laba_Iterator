#include <io.h>

class FileItem
{
public:
	std::string name;
	std::string path;
	int isDir;
	tm dateCreated;

	FileItem() {};
	FileItem(const std::string& name, const std::string& path, time_t dateCreate);
	void Show();
};

class FileIterator
{
	FileItem* cache;
	std::string FileMask;
	FileIterator* it;
	intptr_t FindHandle;

	FileItem* doSearch(const std::string & fileMask);
	FileItem* Serch_ib_dir(const std::string & fileMask);

	inline bool IsDirectory(const _finddata_t & FindData);

	bool compareToMask(const std::string & mask, const std::string & file);

public:
	FileIterator() : FindHandle(NULL) {};
	FileIterator(const std::string & fileMask);

	bool hasMore();

	FileItem * Next();

	void setFileMask(const std::string & mask);
};
