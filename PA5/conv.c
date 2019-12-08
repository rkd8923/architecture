#include "conv.h"
// static int BLOCK = 4;
void convolution(const int M, const int N, const int *input, int *output, const int filter[3][3]) 
{
	//Write your code here
	for(int i = 0 ; i < M ; i += 1)
	{
		for(int j = 0 ; j < N ; j += 1)
		{
			// for (int ii = i; ii < i + BLOCK; ii++) {
			// 	for (int jj = j; jj < j + BLOCK; jj++) {
			// 		int locate = ii * N + jj;
			// 		int first = (ii - 1) * N;
			// 		int locate = ii * N;
			// 		int third = (ii + 1) * N;
			// 		if (ii - 1 >= 0) {
			// 			if (jj - 1 >= 0) output[locate] += input[first + (jj - 1)] * filter[0][0];
			// 			output[locate] += input[first + jj] * filter[0][1];
			// 			if (jj + 1 < N) output[locate] += input[first + (jj + 1)] * filter[0][2];
			// 		}

			// 		if (jj - 1 >= 0) output[locate] += input[locate + (jj - 1)] * filter[1][0];
			// 		output[locate] += input[locate] * filter[1][1];
			// 		if (jj + 1 < N) output[locate] += input[locate + (jj + 1)] * filter[1][2];

			// 		if (ii + 1 < M) {
			// 			if (jj - 1 >= 0) output[locate] += input[third + (jj - 1)] * filter[2][0];
			// 			output[locate] += input[third + jj] * filter[2][1];
			// 			if (jj + 1 < N) output[locate] += input[third + (jj + 1)] * filter[2][2];
			// 		}
			// 	}
			// }

			int locate = i * N + j;
			
			if (i - 1 >= 0) {
				int first = locate - N;
				if (j - 1 >= 0) output[locate] += input[first - 1] * filter[0][0];
				output[locate] += input[first] * filter[0][1];
				if (j + 1 < N) output[locate] += input[first + 1] * filter[0][2];
			}

			if (j - 1 >= 0) output[locate] += input[locate - 1] * filter[1][0];
			output[locate] += input[locate] * filter[1][1];
			if (j + 1 < N) output[locate] += input[locate + 1] * filter[1][2];

			if (i + 1 < M) {
				int third = locate + N;
				if (j - 1 >= 0) output[locate] += input[third - 1] * filter[2][0];
				output[locate] += input[third] * filter[2][1];
				if (j + 1 < N) output[locate] += input[third + 1] * filter[2][2];
			}
		}
	}
}



