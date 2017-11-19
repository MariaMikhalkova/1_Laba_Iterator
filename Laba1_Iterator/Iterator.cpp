#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>

#include "Iterator.h"

using namespace std;


FileItem::FileItem(const string& name, const string& path, time_t dateCreate)
{
	this->name = name;
	this->path = path;
	_localtime64_s(&this->dateCreated, &dateCreate);
}
void FileItem::Show()
{
	cout << left << setfill(' ') << setw(40) << path + "\\" + name;
	cout << right << setfill('0') << setw(2) << dateCreated.tm_mday << '.'
		<< right << setfill('0') << setw(2) << 1 + dateCreated.tm_mon << '.'
		<< 1900 + dateCreated.tm_year << endl;
}

FileIterator::FileIterator(const string & fileMask)
{
	FileMask = fileMask;
	FindHandle = 0;
	it = NULL;
}

void FileIterator::setFileMask(const string & mask)
{
	FileMask = mask;
	it = NULL;
}

bool FileIterator::hasMore()
{
	cache = doSearch(FileMask);
	return cache != NULL;
}

FileItem * FileIterator::Next()
{
	if (cache != NULL)
	{
		FileItem * res = cache;
		cache = NULL;
		return res;
	}
	FileItem * res = doSearch(FileMask);
	if (res == NULL)
		throw("File not found.");
	return res;
}

inline bool FileIterator::IsDirectory(const _finddata_t & FindData)
{
	return ((FindData.attrib & _A_SUBDIR) != 0);
}

bool FileIterator::compareToMask(const string & mask, const string & file)
{
	int pos = 0;
	for (unsigned int i = 0; i < mask.length(); ++i)
		for (unsigned int j = pos; j < file.length(); ++j)
		{
			pos = j;
			if (mask[i] == '*')
			{
				if (file[j] == '.')
					break;
				else
					continue;
			}
			else if ((mask[i] == '?') || (mask[i] == file[j]))
			{
				++pos;
				break;
			}
			return false;
		}
	return true;
}

FileItem* FileIterator::doSearch(const string & fileMask)
{
	FileItem *a;
	string newFileMask;
	_finddata_t FindData;
	do{
		if (it != NULL)
		{
			a = it->doSearch(newFileMask);
			if (a != NULL){// it->setFileMask(newFileMask);
				return a;
			}
			else{ delete it; it = NULL; }
		}
		a = Serch_ib_dir(fileMask);
		if (a == NULL){ return a; }
		if (a->isDir == 0)
		{
			if (compareToMask(fileMask.substr(fileMask.find_last_of('\\') + 1), string(FindData.name)))
			{/*
			 string name = FindData.name;
			 string path = defFileMask.substr(0, defFileMask.find_last_of('\\'));
			 if (path == "*.*")
			 path = " root ";
			 time_t create = FindData.time_create;
			 cache = new FileItem(name, path, create);
			 return cache;*/
				return a;
			}

		}
		else{

			newFileMask = (a->path + '\\' + a->name + '\\');

			it = new FileIterator(newFileMask);

		}
		/*
		string defFileMask = fileMask.substr(0, fileMask.find_last_of('\\') + 1) + "*.*";

		if (FindHandle == 0)
		FindHandle = _findfirst(defFileMask.c_str(), &FindData);

		while (_findnext(FindHandle, &FindData) != -1L)
		{
		if ((FindData.name == string(".")) || (FindData.name == string("..")))
		continue;

		if (IsDirectory(FindData))
		{

		string newFileMask = fileMask;
		newFileMask.insert(fileMask.find_last_of('\\') + 1, string(FindData.name) + '\\');
		a = Serch_ib_dir(newFileMask);

		/*
		while (a != NULL)
		{
		a = Serch_ib_dir(newFileMask);
		}*/
		//this->subIterator = new FileIterator(newFileMask);
		//while (this->subIterator->hasMore())
		//	this->subIterator->Next()->Show();
		/*	}

		if (compareToMask(fileMask.substr(fileMask.find_last_of('\\') + 1), string(FindData.name)))
		{
		string name = FindData.name;
		string path = defFileMask.substr(0, defFileMask.find_last_of('\\'));
		if (path == "*.*")
		path = " root ";
		time_t create = FindData.time_create;
		cache = new FileItem(name, path, create);
		return cache;

		}
		/*else
		{
		string newFileMask;
		//newFileMask.insert(fileMask.find_last_of('\\') + 1, string(FindData.name) + '\\');
		newFileMask = (a->path + "\\" + a->name);
		it = new FileIterator(newFileMask);
		return a;
		}*/


		//return NULL;
	} while (1);
	_findclose(FindHandle);

}


FileItem* FileIterator::Serch_ib_dir(const string & fileMask)
{
	FileItem* a;
	//it = new FileIterator(fileMask);

	_finddata_t FindData;

	FileIterator* subit;


	string str1 = ".", str2 = "..";
	bool i = 0;
	string defFileMask = fileMask.substr(0, fileMask.find_last_of('\\') + 1) + "*.*";
	if (FindHandle == NULL){
		if ((FindHandle = _findfirst(defFileMask.c_str(), &FindData)) == -1L)
			return NULL;
	}
	else{
		if ((_findnext(FindHandle, &FindData)) != 0)
			return NULL;
	}

	string name = FindData.name;
	string path = fileMask.substr(0, defFileMask.find_last_of('\\'));
	if (path == "*.*")
		path = " root ";
	time_t create = FindData.time_create;
	a = new FileItem(name, path, create);
	if (IsDirectory(FindData))
	{
		a->isDir = 1;
	}
	else{ a->isDir = 0; }
	if ((a->name == str1) || (a->name == str2)){
		delete a;
		a = Serch_ib_dir(fileMask);
	}

	return a;

	/*
	if (FindHandle == NULL){
	if ((FindHandle = _findfirst(fileMask.c_str(), &FindData)) == -1L)
	return NULL;
	}
	else{
	if ((_findnext(FindHandle, &FindData)) != 0)
	return NULL;
	}
	a = new FileItem;
	if (FindData.attrib & _A_SUBDIR)
	i = 1;
	//a->set(file.name, Mask, i);
	*/



	/*
	if (hFind == NULL){
	if ((hFind = _findfirst(str.c_str(), &file)) == -1L)
	return NULL;
	}
	else{
	if ((_findnext(hFind, &file)) != 0)
	return NULL;
	}

	if (FindHandle == 0)
	FindHandle = _findfirst(fileMask.c_str(), &FindData);

	while (_findnext(FindHandle, &FindData) != 0)
	{
	if ((FindData.name == string(".")) || (FindData.name == string("..")))
	continue;

	a = Serch_ib_dir(fileMask);
	}
	a = new FileItem;

	//a->set(file.name, Mask, i);
	return a;
	*/

}





