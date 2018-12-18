


#ifndef FILEREADERFACTORY_H
#define FILEREADERFACTORY_H

#include <Windows.h>
#include <string>

#include "../FileReader/FileReader.h"

namespace tigran
{
	namespace file
	{
		class AbstractFileReader;
	}
}

namespace tigran
{
	namespace file
	{
		class FileReaderFactory;
	}
}

class tigran::file::FileReaderFactory
{
public:
	static file::AbstractFileReader* CreateFileReader(file::FileReader::FileType type) throw(exception::FileException);
};

#endif // !FILEREADERFACTORY_H

