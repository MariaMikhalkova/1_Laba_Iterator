#include <iostream>
#include "Iterator.h"


FileIterator::FileIterator(const string & _fileMask)
{
	FileMask = _fileMask;
}


// ������� DisplayFiles ���������� ����� � ��������, ����� ������� ������������� ��������� FileMask

void FileIterator::DisplayFiles(const string& FileMask)
{
	_finddata_t FindData;   // ���������� ���������� ��� ������ ������� _findnext � _findclose
	intptr_t    FindHandle; // ���������, ������� �������� ���������� �� ��������� ����� ��� �����������

	string defFileMask = FileMask.substr(0, FileMask.find_last_of('\\') + 1) + "*.*";//����� �-� ����� �� ��������� \ + *.*
	FindHandle = _findfirst(defFileMask.c_str(), &FindData);

	if (FindHandle == -1L)
		return;

	do
	{
		if ((FindData.name == string(".")) || (FindData.name == string("..")))
			continue;
		cout << (IsDirectory(FindData) ? "Directory" : "File") << ": " << FindData.name << "  file size=" << FindData.size << " bytes" << endl;
		if ((IsDirectory(FindData)) == true)//���� ��� �����
		{
			string defFileMask1 = defFileMask.insert(defFileMask.find_last_of('\\') + 1, string(FindData.name) + '\\');//�������� � ����� ��� ����� +\
									
			it2 = new FileIterator(defFileMask1);//���������� �������� � ����� ������
			if (it2->hasMore())
			{
				DisplayFiles(defFileMask1);
			}

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

















