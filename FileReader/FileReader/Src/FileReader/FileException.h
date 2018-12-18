



#ifndef FILEEXCEPTION_H
#define FILEEXCEPTION_H

#include <exception>

namespace tigran
{
	namespace file
	{
		namespace exception
		{
			struct FileException;
			struct FileTypeNotSupported;
			struct NotInitialized;
			struct EmptyFile;
			struct OutOfBounds;
			struct CouldNotOpenFileMapping;
			struct CouldNotMapsViewOfFileMapping;
			struct CouldNotOpenFileOnHardDrive;
			struct CouldNotCreateFileMapping;
			struct FileAreadyMappedInMemory;
		}
	}
}

// @struct FileException
// @brief Base class of all file reading exceptions
struct tigran::file::exception::FileException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Undefined exception.";
	}

	// destructor
	virtual ~FileException() throw()
	{}
};

// @struct FileTypeNotSupported
// @brief Thrown, if file type not supported
struct tigran::file::exception::FileTypeNotSupported : public FileException
{
	const char* what() const throw()
	{
		return "File type not supported.";
	}
};

// @struct NotInitialized
// @brief Thrown, if not initialized
struct tigran::file::exception::NotInitialized : public FileException
{
	const char* what() const throw()
	{
		return "Not initialized.";
	}
};

// @struct EmptyFile
// @brief Thrown, if empty file provided
struct tigran::file::exception::EmptyFile : public FileException
{
	const char* what() const throw()
	{
		return "Empty file provided.";
	}
};

// @struct OutOfBounds
// @brief Thrown, if out of bounds
struct tigran::file::exception::OutOfBounds : public FileException
{
	const char* what() const throw()
	{
		return "Out of bounds.";
	}
};

// @struct CouldNotOpenFileMapping
// @brief Thrown, if could not open file mapping
struct tigran::file::exception::CouldNotOpenFileMapping : public FileException
{
	const char* what() const throw()
	{
		return "Could not open file mapping.";
	}
};

// @struct CouldNotMapsViewOfFileMapping
// @brief Thrown, if could not maps a view of a file mapping
struct tigran::file::exception::CouldNotMapsViewOfFileMapping : public FileException
{
	const char* what() const throw()
	{
		return "Could not maps a view of a file mapping.";
	}
};

// @struct CouldNotOpenFileOnHardDrive
// @brief Thrown, if could not open file on hard drive
struct tigran::file::exception::CouldNotOpenFileOnHardDrive : public FileException
{
	const char* what() const throw()
	{
		return "Could not open file on hard drive.";
	}
};

// @struct CouldNotCreateFileMapping
// @brief Thrown, if could not create file mapping
struct tigran::file::exception::CouldNotCreateFileMapping : public FileException
{
	const char* what() const throw()
	{
		return "Could not create file mapping.";
	}
};

// @struct FileAreadyMappedInMemory
// @brief Thrown, if file already mapped in memory
struct tigran::file::exception::FileAreadyMappedInMemory : public FileException
{
	const char* what() const throw()
	{
		return "File already mapped in memory.";
	}
};

#endif // !FILEEXCEPTION_H

