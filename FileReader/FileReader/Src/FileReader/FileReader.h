



#ifndef FILEREADER_H
#define FILEREADER_H

#include <Windows.h>

#include <string>
#include <vector>

// Forward declarations
namespace tigran
{
	namespace file
	{
		class AbstractFileReader;

		namespace exception
		{
			struct FileException;
		}
	}
}

namespace tigran
{
	namespace file
	{
		class FileReader;
	}
}

/**
 * @brief class FileReader
*/
class tigran::file::FileReader
{
public:
	enum class FileType
	{
		CSV
	};

public:
	__declspec(dllexport) FileReader();
	__declspec(dllexport) virtual ~FileReader();

public:
	/*
	* Call this method to initialize with the file which is already in memory
	* @param type - the type of the file
	* @param fileName - the name of the file in memory
	* @param dwFileSize - the file size in memory
	*/
	__declspec(dllexport) void Init(FileType type, const char* fileName, DWORD dwFileSize) throw(exception::FileException);

	/*
	* Call this method to initialize with the file from hard drive
	* @param type - the type of the file
	* @param fileName - the path to the file on the hard drive
	*/
	__declspec(dllexport) void Init(FileType type, const char* fileName) throw(exception::FileException);

	/*
	* Provides the cell's value as string by given row index and column index
	* @param colIndex - column index of cell
	* @param rowIndex - row index of cell
	*/
	__declspec(dllexport) std::string GetCell(size_t colIndex, size_t rowIndex) throw(exception::FileException);

	/*
	* Method which retrieves all values in specified column and stores them in provided buffer
	* Doesn't modify output buffer if anything wrong
	* @param colIndex - the index of the column to get data from
	* @param outputBuffer - buffer where retrieved values are stored
	*/
	__declspec(dllexport) void GetColumn(size_t colIndex, std::vector<std::string>* outputBuffer) throw(exception::FileException);

	/*
	* Method which retrieves all values in specified row and stores them in provided buffer
	* Doesn't modify output buffer if anything wrong
	* @param rowIndex the index of the row to get data from
	* @param outputBuffer buffer where retrieved values are stored
	*/
	__declspec(dllexport) void GetRow(size_t rowIndex, std::vector<std::string>* outputBuffer) throw(exception::FileException);

private:
	void DestroyExisting();

private:
	file::AbstractFileReader* mFileReader;
};

#endif // !FILEREADER_H

