#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_7.2/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest72Iter
{
    TEST_CLASS(UnitTest72Iter)
    {
    public:

        TEST_METHOD(TestMethod1)
        {
            const int i = 2;
            const int j = 3;
            int k;

            int** a = new int* [i];
            for (int p = 0; p < i; p++) {
                a[p] = new int[j];
            }

            a[0][0] = { 0 }; a[1][0] = { 0 }; a[0][1] = { 1 }; a[1][1] = { 1 }; a[0][2] = { 2 };
            a[1][2] = { 2 };

            k = FindMaxFromMinEvenColumn(a, i, j);
            Assert::AreEqual(k, 1);

            for (int p = 0; p < i; p++) {
                delete[] a[p];
            }
            delete[] a;
        }
    };
}