



#include "../FileReader/FileException.h"
#include "FileReaderFactory.h"
#include "../Abstract/AbstractFileReader.h"
#include "../Concrete/CSV/CSVFileReader.h"

tigran::file::AbstractFileReader* tigran::file::FileReaderFactory::
CreateFileReader(file::FileReader::FileType type) throw(exception::FileException)
{
	file::AbstractFileReader* fileReader = nullptr;

	switch (type)
	{
		case tigran::file::FileReader::FileType::CSV : {
			fileReader = new file::CSVFileReader();
			break;
		}
		default : {
			throw exception::FileTypeNotSupported();
		}	
	}

	return fileReader;
}