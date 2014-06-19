#include "stdtest.h"

extern "C"
int MAMain()
{
	StdTestHarness (TestCML);
	StdTestHarness (TestML);
	StdTestHarness (TestMB);
	StdTestHarness (TestStreams);
	StdTestHarness (TestVector);
	StdTestHarness (TestAlgorithms);
	StdTestHarness (TestObjectVector);
	StdTestHarness (TestString);
	StdTestHarness (TestStringVector);
	StdTestHarness (TestStringStreams);
	StdTestHarness (TestFunctors);
	StdTestHarness (TestSetAndMultiset);
	StdTestHarness (ObjectSerialization);
	StdTestHarness (TestCoutCinCerr);
	StdTestHarness (TestMap);
	StdTestHarness (TestMultiMap);
	StdTestHarness (TestUTF8);
	StdTestHarness (TestBitset);
	StdTestHarness (TestIntegralTuples);
	StdTestHarness (TestEnumArithmetic);
	StdTestHarness (TestStackAndQueue);
	StdTestHarness (TestUtility);
	StdTestHarness (TestMatrixAlgorithms);
	StdTestHarness (TestSimdAlgorithms);
	StdTestHarness (TestHeapOperations);
	StdTestHarness (TestFStream);
	StdTestHarness (TestMacros);
	StdTestHarness (TestTypelists);
	StdTestHarness (TestIntegralArrays);
}