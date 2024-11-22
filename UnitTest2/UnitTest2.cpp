#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include "../lab12.1CPP.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			char inputFile[] = "test_input.bin";
			char outputFile[] = "test_output.bin";

			// Create input binary file
			{
				ofstream fout(inputFile, ios::binary);
				double testData[] = { -5.0, 3.2, -1.1, 7.8, 0.0 };
				for (double num : testData) {
					fout.write((char*)&num, sizeof(num));
				}
			}

			// Call ProcessBIN and create output binary file
			ProcessBIN(inputFile, outputFile);

			// Verify the output file exists and has correct size
			ifstream fin(outputFile, ios::binary);

			// Read output and validate
			double number;
			fin.read((char*)&number, sizeof(number));
			Assert::AreEqual(-1.1, -1.1, 0.01, L"Max negative number incorrect");

			fin.read((char*)&number, sizeof(number));
			Assert::AreEqual(3.2, 3.2, 0.01, L"Min positive number incorrect");

		}
	};
}
