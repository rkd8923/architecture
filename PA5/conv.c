#include "conv.h"
static int BLOCK = 4;
void convolution(const int M, const int N, const int *input, int *output, const int filter[3][3]) 
{
	//Write your code here
	for(int i = 0 ; i < M ; i += BLOCK)
	{
		for(int j = 0 ; j < N ; j += BLOCK)
		{
			for (int ii = i; ii < i + BLOCK; ii++) {
				for (int jj = j; jj < j + BLOCK; jj++) {
					int locate = ii * N + jj;
					int first = (ii - 1) * N;
					int second = ii * N;
					int third = (ii + 1) * N;
					if (ii - 1 >= 0) {
						if (jj - 1 >= 0) output[locate] += input[first + (jj - 1)] * filter[0][0];
						output[locate] += input[first + jj] * filter[0][1];
						if (jj + 1 < N) output[locate] += input[first + (jj + 1)] * filter[0][2];
					}

					if (jj - 1 >= 0) output[locate] += input[second + (jj - 1)] * filter[1][0];
					output[locate] += input[locate] * filter[1][1];
					if (jj + 1 < N) output[locate] += input[second + (jj + 1)] * filter[1][2];

					if (ii + 1 < M) {
						if (jj - 1 >= 0) output[locate] += input[third + (jj - 1)] * filter[2][0];
						output[locate] += input[third + jj] * filter[2][1];
						if (jj + 1 < N) output[locate] += input[third + (jj + 1)] * filter[2][2];
					}
				}
			}

			// int locate = i * N + j;
			// int first = (i - 1) * N;
			// int second = i * N;
			// int third = (i + 1) * N;

			// if (i - 1 >= 0) {
			// 	if (j - 1 >= 0) output[locate] += input[first + (j - 1)] * filter[0][0];
			// 	output[locate] += input[first + j] * filter[0][1];
			// 	if (j + 1 < N) output[locate] += input[first + (j + 1)] * filter[0][2];
			// }

			// if (j - 1 >= 0) output[locate] += input[second + (j - 1)] * filter[1][0];
			// output[locate] += input[locate] * filter[1][1];
			// if (j + 1 < N) output[locate] += input[second + (j + 1)] * filter[1][2];

			// if (i + 1 < M) {
			// 	if (j - 1 >= 0) output[locate] += input[third + (j - 1)] * filter[2][0];
			// 	output[locate] += input[third + j] * filter[2][1];
			// 	if (j + 1 < N) output[locate] += input[third + (j + 1)] * filter[2][2];
			// }
		}
	}
}



