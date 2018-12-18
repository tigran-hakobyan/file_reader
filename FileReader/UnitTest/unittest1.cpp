#include "stdafx.h"
#include "CppUnitTest.h"
#include "../FileReader/Src/FileReader/FileReader.h"
#include "../FileReader/Src/FileReader/FileException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			mFileReader = new tigran::file::FileReader();
			auto func = [this] { mFileReader->GetCell(100, 100); };
			Assert::ExpectException<tigran::file::exception::NotInitialized>(func);
		}

	private:
		tigran::file::FileReader* mFileReader;

	};
}