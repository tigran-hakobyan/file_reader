



#ifndef ABSTRACTFILEREADER_H
#define ABSTRACTFILEREADER_H

#include <vector>
#include <string>

namespace tigran
{
	namespace file
	{
		class AbstractFileReader;
	}
}

/**
 * @brief class AbstractFileReader
*/
class tigran::file::AbstractFileReader
{
public:

	/*
	* Call this method to initialize with the file which is already in memory
	* @param fileName - the name of the file in memory
	* @param dwFileSize - the file size in memory
	*/
	virtual void InitWithFileInMemory(const char* fileName, DWORD dwFileSize) = 0;

	/*
	* Call this method to initialize with the file from hard drive
	* @param fileName - the path to the file on the hard drive
	*/
	virtual void InitWithFileOnHardDrive(const char* fileName) = 0;

	/*
	* Method which retrieves cell value as string by given row index and column index
	* @param colIndex column index of cell
	* @param rowIndex row index of cell
	*/
	virtual std::string GetCell(size_t colIndex, size_t rowIndex) = 0;

	/*
	* Method which retrieves all values in specified column and stores them in provided buffer
	* @param colIndex the index of the column to get data from
	* @param outputBuffer buffer where retrieved values are stored
	*/
	virtual void GetColumn(size_t colIndex, std::vector<std::string>* outputBuffer) = 0;

	/*
	* Method which retrieves all values in specified row and stores them in provided buffer
	* @param rowIndex the index of the row to get data from
	* @param outputBuffer buffer where retrieved values are stored
	*/
	virtual void GetRow(size_t rowIndex, std::vector<std::string>* outputBuffer) = 0;
};

#endif // !ABSTRACTFILEREADER_H


