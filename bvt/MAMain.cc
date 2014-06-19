#include "stdtest.h"

void TestCML();
void TestML();
void TestMB();
void TestStreams();
void TestVector();
void TestAlgorithms();
void TestObjectVector();
void TestString();
void TestStringVector();
void TestStringStreams();
void TestFunctors();
void TestSetAndMultiset();
void ObjectSerialization();
void TestCoutCinCerr();
void TestMap();
void TestMultiMap();
void TestUTF8();
void TestBitset();
void TestIntegralTuples();
void TestEnumArithmetic();
void TestStackAndQueue();
void TestUtility();
void TestMatrixAlgorithms();
void TestSimdAlgorithms();
void TestHeapOperations();
void TestFStream();
void TestMacros();
void TestTypelists();
void TestIntegralArrays();

#define StdTestHarness(fn) StdTestCall(#fn "\n", &fn)

void StdTestCall(const char* name, void (*fn)()) {
  maWriteLog(name, strlen(name));
  fn();
} 

extern "C"
int MAMain()
{
	StdTestHarness(TestCML);
	StdTestHarness(TestML);
	StdTestHarness(TestMB);
	StdTestHarness(TestStreams);
	StdTestHarness(TestVector);
//	StdTestHarness(TestAlgorithms);
	StdTestHarness(TestObjectVector);
	StdTestHarness(TestString);
	StdTestHarness(TestStringVector);
	StdTestHarness(TestStringStreams);
	StdTestHarness(TestFunctors);
	StdTestHarness(TestSetAndMultiset);
	StdTestHarness(ObjectSerialization);
	StdTestHarness(TestCoutCinCerr);
	StdTestHarness(TestMap);
//	StdTestHarness(TestMultiMap);
	StdTestHarness(TestUTF8);
	StdTestHarness(TestBitset);
	StdTestHarness(TestIntegralTuples);
	StdTestHarness(TestEnumArithmetic);
	StdTestHarness(TestStackAndQueue);
	StdTestHarness(TestUtility);
	StdTestHarness(TestMatrixAlgorithms);
	StdTestHarness(TestSimdAlgorithms);
	StdTestHarness(TestHeapOperations);
	StdTestHarness(TestFStream);
	StdTestHarness(TestMacros);
	StdTestHarness(TestTypelists);
	StdTestHarness(TestIntegralArrays);
}
