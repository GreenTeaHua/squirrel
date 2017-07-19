/*
 * Copyright 2016 Alexander Richard
 *
 * This file is part of Squirrel.
 *
 * Licensed under the Academic Free License 3.0 (the "License").
 * You may not use this file except in compliance with the License.
 * You should have received a copy of the License along with Squirrel.
 * If not, see <https://opensource.org/licenses/AFL-3.0>.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */

#ifndef MATH_MULTITHREADINGHELPER_HH_
#define MATH_MULTITHREADINGHELPER_HH_

namespace Math {

/**
 *
 * generic multithreading for vector operations
 * useful for BLAS 1 operations or similar which are not automatically
 * parallelized
 *
 * (application would be much easier in C++x11 with std::bind)
 *
 */


/*
 *
 * parallelization of function of type vector + scalar to vector, e.g. axpy
 *
 *
 */



template<typename T>
void mt_sv2v(int N, T alpha, const T *X, T *Y, void (*fn)(int, T, const T*, T*), int nThreads){
	int nParts = nThreads < 1 ? 1 : nThreads;
	nParts = nParts > N ? std::max(1,N) : nParts;
	int d = N / nParts;
	int r = N % nParts;
	if (r == 0){
#pragma omp parallel for
		for (int partId = 0; partId < nParts ; partId++){
			fn(d, alpha, X + partId * d, Y+ partId * d);
		}
	}
	else{
#pragma omp parallel for
		for (int partId = 0; partId < nParts; partId++){
			if (partId < nParts - 1)
				fn(d, alpha, X + partId * d, Y + partId * d);
			else
				fn(d + r, alpha, X + (nParts -1)* d, Y + (nParts -1)* d);
		}
	}
}

/*
 *
 * parallelization of function of type vector to vector, e.g. exp
 * (unfortunately, design error in vr_exp, first vector is not const!)
 *
 */



template<typename T>
void mt_v2v(int N, T *X, T *Y, void (*fn)(int, T*, T*), int nThreads){
	int nParts = nThreads < 1 ? 1 : nThreads;
	nParts = nParts > N ? std::max(1,N) : nParts;

	int d = N / nParts;
	int r = N % nParts;
	if (r == 0){
#pragma omp parallel for
		for (int partId = 0; partId < nParts ; partId++){
			fn(d, X + partId * d, Y+ partId * d);
		}
	}
	else{
#pragma omp parallel for
		for (int partId = 0; partId < nParts; partId++){
			if (partId < nParts - 1)
				fn(d, X + partId * d, Y + partId * d);
			else
				fn(d + r, X + (nParts -1)* d, Y + (nParts -1)* d);
		}
	}
}


/*
 *
 * parallelization of function of type scalar, vector, vector-> scalar, e.g. nrm2, dot, asum
 * reduction with operator +
 *
 */

template<typename T>
T mt_svv2s(int N, T alpha, const T *X, const T *Y, T (*fn)(int, T, const T*, const T*), int nThreads){
	int nParts = nThreads < 1 ? 1 : nThreads;
	nParts = nParts > N ? std::max(1,N) : nParts;

	int d = N / nParts;
	int r = N % nParts;
	T result = 0.0;
	if (r == 0){
#pragma omp parallel for reduction(+:result)
		for (int partId = 0; partId < nParts ; partId++){
			result += fn(d, alpha, X + partId * d, Y+ partId * d);
		}
	}
	else{
#pragma omp parallel for reduction(+:result)
		for (int partId = 0; partId < nParts; partId++){
			if (partId < nParts - 1)
				result += fn(d, alpha, X + partId * d, Y+ partId * d);
			else
				result += fn(d + r, alpha, X + (nParts -1)* d, Y + (nParts -1)* d);
		}
	}
	return result;
}


}

#endif /* MATH_MULTITHREADINGHELPER_HH_ */
