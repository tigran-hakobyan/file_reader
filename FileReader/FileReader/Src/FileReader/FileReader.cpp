


#include "FileReader.h"
#include "FileException.h"
#include "../Abstract/AbstractFileReader.h"
#include "../Factory/FileReaderFactory.h"

tigran::file::FileReader::
FileReader()
	: mFileReader(nullptr)
{
}

tigran::file::FileReader::
~FileReader()
{
	DestroyExisting();
}

void tigran::file::FileReader::
Init(FileType type, const char* fileName, DWORD dwFileSize) throw(exception::FileException)
{
	DestroyExisting();
	mFileReader = file::FileReaderFactory::CreateFileReader(type);
	mFileReader->InitWithFileInMemory(fileName, dwFileSize);
}

void tigran::file::FileReader::
Init(FileType type, const char* fileName) throw(exception::FileException)
{
	DestroyExisting();
	mFileReader = file::FileReaderFactory::CreateFileReader(type);
	mFileReader->InitWithFileOnHardDrive(fileName);
}

std::string tigran::file::FileReader::
GetCell(size_t colIndex, size_t rowIndex)  throw(exception::FileException)
{
	if (mFileReader) 
	{
		return mFileReader->GetCell(colIndex, rowIndex);
	}
	else
	{
		throw exception::NotInitialized();
	}
}

void tigran::file::FileReader::
GetColumn(size_t colIndex, std::vector<std::string>* outputBuffer)  throw(exception::FileException)
{
	if (mFileReader)
	{
		mFileReader->GetColumn(colIndex, outputBuffer);
	}
	else
	{
		throw exception::NotInitialized();
	}
}

void tigran::file::FileReader::
GetRow(size_t rowIndex, std::vector<std::string>* outputBuffer) throw(exception::FileException)
{
	if (mFileReader)
	{
		mFileReader->GetRow(rowIndex, outputBuffer);
	}
	else
	{
		throw exception::NotInitialized();
	}
}

void tigran::file::FileReader::
DestroyExisting()
{
	if (mFileReader)
	{
		delete mFileReader;
	}
	mFileReader = nullptr;
}



