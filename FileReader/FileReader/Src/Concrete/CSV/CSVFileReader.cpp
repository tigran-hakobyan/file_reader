



#include "CSVFileReader.h"
#include "../../FileReader/FileException.h"

tigran::file::CSVFileReader::
CSVFileReader()
{
}

tigran::file::CSVFileReader::
~CSVFileReader()
{
	if (!mBuf.empty())
		mBuf.clear();
}

void tigran::file::CSVFileReader::
InitWithFileInMemory(const char* fileName, DWORD dwFileSize) throw(exception::FileException)
{
	HANDLE hFileMapping = NULL;

	hFileMapping = OpenFileMapping(FILE_MAP_READ, FALSE, fileName);
	if (NULL == hFileMapping)
		throw exception::CouldNotOpenFileMapping();

	LPVOID lpMapAddress = MapViewOfFile(hFileMapping,	// handle to mapping object
		FILE_MAP_READ,									// read/write permission
		0,												// max. object size
		0,												// size of hFile
		0);												// map entire file

	CloseHandle(hFileMapping);

	if (NULL == lpMapAddress)
		throw exception::CouldNotMapsViewOfFileMapping();

	mLpMapAddress = (char*)lpMapAddress;
	mDwFileSize = dwFileSize;

	ReadCSV();

	UnmapViewOfFile(lpMapAddress);
}

void tigran::file::CSVFileReader::
InitWithFileOnHardDrive(const char* fileName) throw(exception::FileException)
{
	HANDLE fileHandle = NULL;
	HANDLE hFileMapping = NULL;

	fileHandle = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == fileHandle)
		throw exception::CouldNotOpenFileOnHardDrive();

	DWORD dwFileSize = GetFileSize(fileHandle, NULL);

	if (0 == dwFileSize)
	{
		CloseHandle(fileHandle);
		throw exception::EmptyFile();
	}

	hFileMapping = CreateFileMapping(
		fileHandle,
		NULL,
		PAGE_READONLY,
		0,
		0,
		"CSV_map");

	CloseHandle(fileHandle);

	if (NULL == hFileMapping)
		throw exception::CouldNotCreateFileMapping();

	else if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hFileMapping);
		throw exception::FileAreadyMappedInMemory();
	}

	LPVOID lpMapAddress = MapViewOfFile(hFileMapping,	// handle to mapping object
		FILE_MAP_READ,									// read/write permission
		0,												// max. object size
		0,												// size of hFile
		0);												// map entire file

	CloseHandle(hFileMapping);

	if (NULL == lpMapAddress)
		throw exception::CouldNotMapsViewOfFileMapping();

	mLpMapAddress = (char*)lpMapAddress;
	mDwFileSize = dwFileSize;

	ReadCSV();

	UnmapViewOfFile(lpMapAddress);
}

std::string tigran::file::CSVFileReader::
GetCell(size_t colIndex, size_t rowIndex) throw(exception::FileException)
{
	if (0 == rowIndex)
	{
		rowIndex = 1;
	}	
	if (0 == colIndex)
	{
		colIndex = 1;
	}

	if (mBuf.size() < rowIndex || mBuf[rowIndex - 1].size() < colIndex)
		throw exception::OutOfBounds();
	return mBuf[rowIndex - 1][colIndex - 1];
}

void tigran::file::CSVFileReader::
GetColumn(size_t colIndex, std::vector<std::string>* outputBuffer) throw(exception::FileException)
{
	if (0 == colIndex)
		colIndex = 1;
	if (!mBuf.empty() && mBuf[0].size() >= colIndex)
	{
		for (size_t i = 0; i < mBuf.size(); ++i)
			outputBuffer->push_back((mBuf[i].size() < colIndex) ? "" : mBuf[i][colIndex - 1]);
	}
	else
	{
		throw exception::OutOfBounds();
	}
}

void tigran::file::CSVFileReader::
GetRow(size_t rowIndex, std::vector<std::string>* outputBuffer) throw(exception::FileException)
{
	if (0 == rowIndex)
	{
		rowIndex = 1;
	}
		
	if (mBuf.size() < rowIndex)
	{
		throw exception::OutOfBounds();
	}	

	*outputBuffer = mBuf[rowIndex - 1];
}

void tigran::file::CSVFileReader::
ReadCSV()
{
	if (!mBuf.empty())
	{
		mBuf.clear();
	}

	size_t pos = 0;
	while (ReadLine(pos));
}

bool tigran::file::CSVFileReader::
ReadLine(size_t& pos)
{
	VS line;
	int ret;

	while (!(ret = ReadCell(pos, line)));

	if (2 == ret)
	{
		return false;
	}

	mBuf.push_back(line);
	return true;
}

int tigran::file::CSVFileReader::
ReadCell(size_t& pos, VS& line)
{
	std::string cell;

	do
	{
		if (pos >= mDwFileSize)
		{
			return 2;
		}	

		if ('\t' != mLpMapAddress[pos])
		{
			if ('\r'== mLpMapAddress[pos])
			{
				pos += 2;
				NormalizeCell(cell);
				line.push_back(cell);
				return 1;
			}
			cell += mLpMapAddress[pos];
		}
	} while ('\t' != mLpMapAddress[pos++]);

	NormalizeCell(cell);
	line.push_back(cell);

	return 0;
}

void tigran::file::CSVFileReader::
NormalizeCell(std::string& subStr)
{
	if (0 == subStr.length())
	{
		return;
	}

	std::string resStr = "";

	if ('\"' == subStr[0] && '\"' == subStr[subStr.length() - 1])
	{
		subStr = subStr.erase(0, 1);
		subStr = subStr.erase(subStr.length() - 1, 1);
		for (size_t i = 0; i < subStr.length(); ++i)
		{
			if (i + 1 <= subStr.length() && '\"' == subStr[i] && '\"' == subStr[i + 1])
				resStr = resStr + subStr[i++];
			else
				resStr = resStr + subStr[i];
		}
		subStr = resStr;
	}
}

