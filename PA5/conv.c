#include "conv.h"

void convolution(const int M, const int N, const int *input, int *output, const int filter[3][3]) 
{
	//Write your code here
	for(int i = 0 ; i < M ; i++)
	{
		for(int j = 0 ; j < N ; j++)
		{
			int locate = i * N + j;
			int first = (i - 1) * N;
			int second = i * N;
			int third = (i + 1) * N;

			if (i - 1 >= 0) {
				if (j - 1 >= 0) output[locate] += input[first + (j - 1)] * filter[0][0];
				output[locate] += input[first + j] * filter[0][1];
				if (j + 1 < N) output[locate] += input[first + (j + 1)] * filter[0][2];
			}

			if (j - 1 >= 0) output[locate] += input[second + (j - 1)] * filter[1][0];
			output[locate] += input[locate] * filter[1][1];
			if (j + 1 < N) output[locate] += input[second + (j + 1)] * filter[1][2];

			if (i + 1 < M) {
				if (j - 1 >= 0) output[locate] += input[third + (j - 1)] * filter[2][0];
				output[locate] += input[third + j] * filter[2][1];
				if (j + 1 < N) output[locate] += input[third + (j + 1)] * filter[2][2];
			}
		}
	}
}



