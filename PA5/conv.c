#include "conv.h"
void convolution(const register int M, const register int N, const register int *input, register int *output, const int filter[3][3]) 
{
	register int _filter[9] = {
		filter[0][0], filter[0][1], filter[0][2],
		filter[1][0], filter[1][1], filter[1][2],
		filter[2][0], filter[2][1], filter[2][2]
	};
	//Write your code here
	for(register int i = 0 ; i < M ; i ++)
	{
		register int j = 0;
		for(; j < N ; j += 4)
		{
			register int locate = i * N + j;
			if (i - 1 >= 0) {
				register int first = locate - N;
				if (j - 1 >= 0) output[locate] += input[first - 1] * _filter[0];
				output[locate] += input[first] * _filter[1];
				if (j + 1 < N) output[locate] += input[first + 1] * _filter[2];
			}

			if (j - 1 >= 0) output[locate] += input[locate - 1] * _filter[3];
			output[locate] += input[locate] * _filter[4];
			if (j + 1 < N) output[locate] += input[locate + 1] * _filter[5];

			if (i + 1 < M) {
				register int third = locate + N;
				if (j - 1 >= 0) output[locate] += input[third - 1] * _filter[6];
				output[locate] += input[third] * _filter[7];
				if (j + 1 < N) output[locate] += input[third + 1] * _filter[8];
			}

			locate++;
			if (i - 1 >= 0) {
				register int first = locate - N;
				if (j >= 0) output[locate] += input[first - 1] * _filter[0];
				output[locate] += input[first] * _filter[1];
				if (j + 2 < N) output[locate] += input[first + 1] * _filter[2];
			}

			if (j >= 0) output[locate] += input[locate - 1] * _filter[3];
			output[locate] += input[locate] * _filter[4];
			if (j + 2 < N) output[locate] += input[locate + 1] * _filter[5];

			if (i + 1 < M) {
				register int third = locate + N;
				if (j >= 0) output[locate] += input[third - 1] * _filter[6];
				output[locate] += input[third] * _filter[7];
				if (j + 2 < N) output[locate] += input[third + 1] * _filter[8];
			}
						locate++;
			if (i - 1 >= 0) {
				register int first = locate - N;
				if (j >= 0) output[locate] += input[first - 1] * _filter[0];
				output[locate] += input[first] * _filter[1];
				if (j + 2 < N) output[locate] += input[first + 1] * _filter[2];
			}

			if (j >= 0) output[locate] += input[locate - 1] * _filter[3];
			output[locate] += input[locate] * _filter[4];
			if (j + 2 < N) output[locate] += input[locate + 1] * _filter[5];

			if (i + 1 < M) {
				register int third = locate + N;
				if (j >= 0) output[locate] += input[third - 1] * _filter[6];
				output[locate] += input[third] * _filter[7];
				if (j + 2 < N) output[locate] += input[third + 1] * _filter[8];
			}
						locate++;
			if (i - 1 >= 0) {
				register int first = locate - N;
				if (j >= 0) output[locate] += input[first - 1] * _filter[0];
				output[locate] += input[first] * _filter[1];
				if (j + 2 < N) output[locate] += input[first + 1] * _filter[2];
			}

			if (j >= 0) output[locate] += input[locate - 1] * _filter[3];
			output[locate] += input[locate] * _filter[4];
			if (j + 2 < N) output[locate] += input[locate + 1] * _filter[5];

			if (i + 1 < M) {
				register int third = locate + N;
				if (j >= 0) output[locate] += input[third - 1] * _filter[6];
				output[locate] += input[third] * _filter[7];
				if (j + 2 < N) output[locate] += input[third + 1] * _filter[8];
			}
		}


	}
}