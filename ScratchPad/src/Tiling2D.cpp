#include <iostream>

void makeTiled(int* dst, int* src, int M, int N, int B)
{
	//src
	//  1  2  3  4  5  6
	//  7  8  9 10 11 12
	// 13 14 15 16 17 18
	// 19 20 21 22 23 24

	//dst
	//  1  2  5  6  9 10
	//  3  4  7  8 11 12
	// 13 14 17 18 21 22
	// 15 16 19 20 23 24

	int srcindex, dstindex;

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N / B; j++)
		{
			srcindex = i*N + j*B;
			dstindex = j*N + i*B;
			memcpy_s((void*)(dst + dstindex), B, (void*)(src + srcindex), B);
		}
	}


	// M=4 N=6

	// 0  6  2
	// 8  4 10
	//12 18 14
	//20 16 22

	//00 01 02
	//10 11 12
	//20 21 22
	//30 31 32
}


void TestTiling()
{
	int* src = new int[24];
	for (int i = 0; i < 24; i++)
	{
		*(src + i) = i + 1;
	}
	int* dst = new int[24];
	makeTiled(dst, src, 4, 6, 2);
}
