



#ifndef CSVFILEREADER_H
#define CSVFILEREADER_H

#include <vector>
#include <string>

#include <Windows.h>
#include "../../Abstract/AbstractFileReader.h"

namespace tigran
{
	namespace exception
	{
		struct FileException;
	}
}

namespace tigran
{
	namespace file
	{
		class CSVFileReader;
	}
}

/**
 * @brief class CSVFileReader : AbstractFileReader
*/
class tigran::file::CSVFileReader : public tigran::file::AbstractFileReader
{
public:
	CSVFileReader();
	virtual ~CSVFileReader();

public:
	/*
	* Call this method to initialize with the file which is already in memory
	* @param fileName - the name of the file in memory
	* @param dwFileSize - the file size in memory
	*/
	virtual void InitWithFileInMemory(const char* fileName, DWORD dwFileSize) throw(exception::FileException);

	/*
	* Call this method to initialize with the file from hard drive
	* @param fileName - the path to the file on the hard drive
	*/
	virtual void InitWithFileOnHardDrive(const char* fileName) throw(exception::FileException);

public:
	/*
	* Method which retrieves cell value as string by given row index and column index
	* @param colIndex column index of cell
	* @param rowIndex row index of cell
	*/
	virtual std::string GetCell(size_t colIndex, size_t rowIndex) throw(exception::FileException);

	/*
	* Method which retrieves all values in specified column and stores them in provided buffer
	* @param colIndex the index of the column to get data from
	* @param outputBuffer buffer where retrieved values are stored
	*/
	virtual void GetColumn(size_t colIndex, std::vector<std::string>* outputBuffer) throw(exception::FileException);

	/*
	* Method which retrieves all values in specified row and stores them in provided buffer
	* @param rowIndex the index of the row to get data from
	* @param outputBuffer buffer where retrieved values are stored
	*/
	virtual void GetRow(size_t rowIndex, std::vector<std::string>* outputBuffer) throw(exception::FileException);

private:
	typedef std::vector<std::string> VS;
	typedef VS::iterator VS_ITER;
	typedef std::vector<VS> VVS;
	typedef VVS::iterator VVS_ITER;

private:
	void ReadCSV();
	bool ReadLine(size_t& pos);
	int ReadCell(size_t& pos, VS& line);
	void NormalizeCell(std::string& subStr);

private:
	VVS mBuf;
	DWORD mDwFileSize;
	char* mLpMapAddress;
};

#endif // !CSVFILEREADER_H

