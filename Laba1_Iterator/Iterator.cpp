#include <iostream>
#include "Iterator.h"


FileIterator::FileIterator(const string & _fileMask)
{
	FileMask = _fileMask;
}

bool FileIterator::Maska(const string mask, const string file)
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

// Функция DisplayFiles отображает файлы и каталоги, имена которых соответствуют указанной FileMask

void FileIterator::DisplayFiles(const string& FileMask)
{
	string path, name;

	_finddata_t FindData;   // уникальный дескриптор для вызова функций _findnext и _findclose
	intptr_t    FindHandle; // структура, которая получает информацию об найденном файле или подкаталоге


	string defFileMask = FileMask.substr(0, FileMask.find_last_of('\\') + 1) + "*.*";//маска к-ю ввели до последней \ + *.*
	FindHandle = _findfirst(defFileMask.c_str(), &FindData);

	if (FindHandle == -1L)
		return;

	do
	{

		if ((FindData.name == string(".")) || (FindData.name == string("..")))
			continue;


		if ((IsDirectory(FindData)) == true)//если ето папка
		{
			cout << (IsDirectory(FindData) ? "Directory" : "File") << ": " << FindData.name << "  file size=" << FindData.size << " bytes" << endl;
			const string  maska = (FileMask.substr(FileMask.find_last_of('\\') + 1));
			name = FindData.name;
			path = defFileMask.substr(0, FileMask.find_last_of('\\'));
			cout << path << "\\" << name << endl << endl;//вывод пути к файлу/папке 

			string defFileMask1 = defFileMask.insert(defFileMask.find_last_of('\\') + 1, string(FindData.name) + '\\');//вставить в маску имя папки +\
						
			string defmask = defFileMask1.substr(0, defFileMask1.find_last_of('\\') + 1) + maska;

			it2 = new FileIterator(defmask);//внутренний итератор с новой маской
			if (it2->hasMore())
			{
				DisplayFiles(defmask);
			}



		}

		if (Maska(FileMask.substr(FileMask.find_last_of('\\') + 1), string(FindData.name)))
		{
			cout << (IsDirectory(FindData) ? "Directory" : "File") << ": " << FindData.name << "  file size=" << FindData.size << " bytes" << endl;

			name = FindData.name;
			path = defFileMask.substr(0, FileMask.find_last_of('\\'));
			cout << path << "\\" << name << endl << endl;//вывод пути к файлу/папке 

			continue;
		}
	} while (_findnext(FindHandle, &FindData) == 0);
	_findclose(FindHandle);
}


bool FileIterator::hasMore()
{
	if (cache != NULL)
		return true;
	return cache != NULL;
}

inline bool FileIterator::IsDirectory(const _finddata_t &FindData)
{
	return ((FindData.attrib & _A_SUBDIR) != 0);
}
