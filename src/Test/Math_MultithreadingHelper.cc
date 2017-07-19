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

#include <Test/UnitTest.hh>
#include <Math/MultithreadingHelper.hh>

void setTo(int N, float *X, float val){
	for (int i = 0; i < N; i++)
		X[i] = val;
}

void setToZero(int N, float *X){
	setTo(N, X, 0.0);
}

void setToInc(int N, float *X){
	for (int i = 0; i < N; i++){
		X[i] = (float) i + 1.0f;
	}
}

void copy(int N, float *X, float *Y){
	for (int i = 0; i < N; i++){
		Y[i] = X[i];
	}
}


void axpy(int N, float alpha, const float *X, float *Y){
	for (int i = 0; i < N; i++){
		Y[i] += alpha * X[i];
	}
}

float dotx(int N, float alpha, const float *X, const float *Y){
	float result = 0.0f;
	for (int i = 0; i < N; i++){
		result  += X[i] * Y[i];
	}
	return alpha * result;
}


TEST(Math, MultithreadingHelper, mt_v2v)
{
	float *x = 0, *y = 0;
	void (*fn)(int, float*, float*) = copy;

	for (int nElements = 0; nElements <= 10; nElements++){
		x = new float[nElements];
		y = new float[nElements];
		for (int nThreads = 1; nThreads <= 4; nThreads++){
			setTo(nElements, x, 1.0);
			setTo(nElements, y, 0.0);
			Math::mt_v2v(nElements, x, y, fn, nThreads);

			for (int i = 0; i < nElements; i++){
				EXPECT_EQ(1.0f, y[i]);
			}
		}
		delete [] x;
		delete [] y;
	}
}

TEST(Math, MultithreadingHelper, mt_sv2v)
{
	float *x = 0, *y = 0;
	void (*fn)(int, float, const float*, float*) = axpy;

	for (int nElements = 0; nElements <= 10; nElements++){
		x = new float[nElements];
		y = new float[nElements];
		for (int nThreads = 1; nThreads <= 4; nThreads++){
			setTo(nElements, x, 1.0);
			setTo(nElements, y, 2.0);
			Math::mt_sv2v(nElements, 3.0f, x, y, fn, nThreads);

			for (int i = 0; i < nElements; i++){
				EXPECT_EQ(y[i], 5.0f);
			}
		}
		delete [] x;
		delete [] y;
	}
}

TEST(Math, MultithreadingHelper, mt_svv2s)
{
	float *x = 0, *y = 0;

	for (int nElements = 0; nElements <= 10; nElements++){
		x = new float[nElements];
		y = new float[nElements];

		for (int nThreads = 1; nThreads <= 4; nThreads++){
			setToInc(nElements, x);
			setTo(nElements, y, 1.0);
			float result = Math::mt_svv2s(nElements, 2.0f, x, y, dotx, nThreads);
			EXPECT_EQ(nElements * (nElements + 1.0f), result);
		}
		delete [] x;
		delete [] y;
	}
}
