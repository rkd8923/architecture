#include "conv.h"

void convolution(const int M, const int N, const int *input, int *output, const int filter[3][3]) 
{
	//Write your code here
	for(int i = 0 ; i < M ; i++)
	{
		for(int j = 0 ; j < N ; j++)
		{
			if (i - 1 < 0) output[i * N + j] += 0;
			else {
				if (j - 1 < 0) output[i * N + j] += 0;
				else output[i * N + j] += input[(i-1) * N + (j - 1)] * filter[0][0];
				output[i * N + j] += input[(i-1) * N + j] * filter[0][1];
				if (j + 1 >= N) output[i * N + j] += 0;
				else output[i * N + j] += input[(i-1) * N + (j + 1)] * filter[0][2];
			}

			if (j - 1 < 0) output[i * N + j] += 0;
			else output[i * N + j] += input[i * N + (j - 1)] * filter[1][0];
			output[i * N + j] += input[i * N + j] * filter[1][1];
			if (j + 1 >= N) output[i * N + j] += 0;
			else output[i * N + j] += input[i * N + (j + 1)] * filter[1][2];

			if (i + 1 >= M) output[i * N + j] += 0;
			else {
				if (j - 1 < 0) output[i * N + j] += 0;
				else output[i * N + j] += input[(i + 1) * N + (j - 1)] * filter[2][0];
				output[i * N + j] += input[(i + 1) * N + j] * filter[2][1];
				if (j + 1 >= N) output[i * N + j] += 0;
				else output[i * N + j] += input[(i + 1) * N + (j + 1)] * filter[2][2];
			}
		}
	}
}



