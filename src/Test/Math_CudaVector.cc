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
#include <Math/CudaVector.hh>
#include <Math/CudaMatrix.hh>

class TestCudaVector: public Test::Fixture
{
public:
	void setUp();
	void tearDown();
};

void TestCudaVector::setUp(){ }

void TestCudaVector::tearDown(){ }

TEST_F(Test, TestCudaVector, resize)
{
	Math::CudaVector<f64> x;
	EXPECT_TRUE(x.empty());
	x.initComputation();
	x.resize(2);
	x.finishComputation();
	EXPECT_EQ(x.nRows(),2u);
	EXPECT_EQ(x.size(),2u);
	x.at(0) = -1.0;
	x.at(1) = 1.0;
	EXPECT_EQ(x.at(0), -1.0);
	EXPECT_EQ(x.at(1), 1.0);

	Math::CudaVector<f32> x2;
	EXPECT_TRUE(x2.empty());
	x2.initComputation();
	x2.resize(2);
	x2.finishComputation();
	EXPECT_EQ(x2.nRows(),2u);
	EXPECT_EQ(x2.size(),2u);
	x2.at(0) = -1.0;
	x2.at(1) = 1.0;
	EXPECT_EQ(x2.at(0), (f32)-1.0);
	EXPECT_EQ(x2.at(1), (f32)1.0);
}

TEST_F(Test, TestCudaVector, copyStructure)
{
	Math::CudaVector<f64> x;
	Math::CudaVector<f64> y;
	x.initComputation();
	y.initComputation();
	y.resize(2);
	EXPECT_EQ(y.nRows(),2u);
	x.copyStructure(y);
	EXPECT_EQ(x.nRows(),2u);

	Math::CudaVector<f32> x2;
	Math::CudaVector<f32> y2;
	x2.initComputation();
	y2.initComputation();
	y2.resize(2);
	EXPECT_EQ(y2.nRows(),2u);
	x2.copyStructure(y2);
	EXPECT_EQ(x2.nRows(),2u);
}

TEST_F(Test, TestCudaVector, copy)
{
	Math::CudaVector<f64> x;
	Math::CudaVector<f64> y;
	y.resize(2);
	x.resize(2);
	x.at(0) = 2.0;
	x.at(1) = 4.0;
	x.initComputation();
	y.initComputation(false);
	y.copy(x);
	y.finishComputation();
	EXPECT_EQ(2.0, y.at(0));
	EXPECT_EQ(4.0, y.at(1));

	Math::CudaVector<f32> x2;
	Math::CudaVector<f32> y2;
	y2.resize(2);
	x2.resize(2);
	x2.at(0) = 2.0;
	x2.at(1) = 4.0;
	x2.initComputation();
	y2.initComputation(false);
	y2.copy(x2);
	y2.finishComputation();
	EXPECT_EQ((f32)2.0, y2.at(0));
	EXPECT_EQ((f32)4.0, y2.at(1));
}

TEST_F(Test, TestCudaVector, copyBlockFromVector)
{
	Math::CudaVector<f64> x;
	Math::CudaVector<f64> y;
	y.resize(2);
	x.resize(2);
	x.at(0) = 2.0;
	x.at(1) = 4.0;
	x.initComputation();
	y.initComputation(false);
	y.setToZero();
	y.copyBlockFromVector(x, 1, 0, 1);
	y.finishComputation();
	EXPECT_EQ(4.0, y.at(0));
	EXPECT_EQ(0.0, y.at(1));
}

TEST_F(Test, TestCudaVector, setToZero)
{
	Math::CudaVector<f64> x;
	x.resize(2);
	x.initComputation();
	x.setToZero();
	x.finishComputation();
	EXPECT_EQ(x.size(),2u);
	EXPECT_EQ(x.at(0), 0.0);
	EXPECT_EQ(x.at(1), 0.0);

	Math::CudaVector<f32> x2;
	x2.resize(2);
	x2.initComputation();
	x2.setToZero();
	x2.finishComputation();
	EXPECT_EQ(x2.size(),2u);
	EXPECT_EQ(x2.at(0), (f32)0.0);
	EXPECT_EQ(x2.at(1), (f32)0.0);
}

TEST_F(Test, TestCudaVector, copyConstructor){
	Math::CudaVector<f32> x(2);
	x.at(0) = 1.0f;
	x.at(1) = 0.0f;
	Math::CudaVector<f32>y(x);
	EXPECT_EQ(x.size(), y.size());
	EXPECT_EQ(x.at(0), y.at(0));
	EXPECT_EQ(x.at(1), y.at(1));
}

TEST_F(Test, TestCudaVector, assignment){
	Math::CudaVector<f32> x(2);
	x.at(0) = 1.0f;
	x.at(1) = 0.0f;
	Math::CudaVector<f32>y;
	y = x;
	EXPECT_EQ(x.size(), y.size());
	EXPECT_EQ(x.at(0), y.at(0));
	EXPECT_EQ(x.at(1), y.at(1));
}

TEST_F(Test, TestCudaVector, add)
{
	Math::CudaVector<f64> x;
	Math::CudaVector<f64> y;
	y.resize(2);
	x.resize(2);
	x.at(0) = 1.0;
	x.at(1) = 2.0;
	y.at(0) = 2.0;
	y.at(1) = 4.0;
	x.initComputation();
	y.initComputation();
	x.add(y, 0.5);
	x.finishComputation();
	EXPECT_EQ(2.0, x.at(0));
	EXPECT_EQ(4.0, x.at(1));

	Math::CudaVector<f32> x2;
	Math::CudaVector<f32> y2;
	y2.resize(2);
	x2.resize(2);
	x2.at(0) = 1.0;
	x2.at(1) = 2.0;
	y2.at(0) = 2.0;
	y2.at(1) = 4.0;
	x2.initComputation();
	y2.initComputation();
	x2.add(y2, 0.5f);
	x2.finishComputation();
	EXPECT_EQ((f32)2.0, x2.at(0));
	EXPECT_EQ((f32)4.0, x2.at(1));

	Math::CudaVector<f64> x3;
	Math::CudaVector<f32> y3;
	y3.resize(2);
	x3.resize(2);
	x3.at(0) = 1.0;
	x3.at(1) = 2.0;
	y3.at(0) = 2.0;
	y3.at(1) = 4.0;
	x3.initComputation();
	y3.initComputation();
	x3.add(y3, 0.5f);
	x3.finishComputation();
	EXPECT_EQ(2.0, x3.at(0));
	EXPECT_EQ(4.0, x3.at(1));

}

TEST_F(Test, TestCudaVector, multiply)
{
	Math::CudaMatrix<f32> A(2,3);
	for (u32 i = 0; i < 2; i++) {
		for (u32 j = 0; j < 3; j++) {
			A.at(i,j) = i+j;
		}
	}
	Math::CudaVector<f32> v(3);
	v.at(0) = 0;
	v.at(1) = 1;
	v.at(2) = 2;
	Math::CudaVector<f32> w(2);
	w.at(0) = 10;
	w.at(1) = 5;
	A.initComputation();
	v.initComputation();
	w.initComputation();
	w.multiply(A, v, false, 1.5, -2.0);
	w.finishComputation();
	v.finishComputation();
	EXPECT_EQ(w.at(0), (f32)-12.5);
	EXPECT_EQ(w.at(1), (f32)2);

	w.at(0) = 2;
	w.at(1) = 4;
	v.at(0) = 1;
	v.at(1) = 2;
	v.at(2) = -1;
	v.initComputation();
	w.initComputation();
	v.multiply(A, w, true, -1.0, 3.0);
	v.finishComputation();
	EXPECT_EQ(v.at(0), (f32)-1);
	EXPECT_EQ(v.at(1), (f32)-4);
	EXPECT_EQ(v.at(2), (f32)-19);
}

TEST_F(Test, TestCudaVector, addConstantElementwise)
{
	Math::CudaVector<f64> x;
	x.resize(2);
	x.at(0) = 1.0;
	x.at(1) = 2.0;
	x.initComputation();
	x.addConstantElementwise(2.0);
	x.finishComputation();
	EXPECT_EQ(3.0, x.at(0));
	EXPECT_EQ(4.0, x.at(1));

	Math::CudaVector<f32> x2;
	x2.resize(2);
	x2.at(0) = 1.0;
	x2.at(1) = 2.0;
	x2.initComputation();
	x2.addConstantElementwise(2.0);
	x2.finishComputation();
	EXPECT_EQ(3.0f, x2.at(0));
	EXPECT_EQ(4.0f, x2.at(1));
}

TEST_F(Test, TestCudaVector, scale)
{
	Math::CudaVector<f64> y;
	y.resize(2);
	y.at(0) = 2.0;
	y.at(1) = 4.0;
	y.initComputation();
	y.scale(0.5);
	y.finishComputation();
	EXPECT_EQ(1.0, y.at(0));
	EXPECT_EQ(2.0, y.at(1));

	Math::CudaVector<f32> y2;
	y2.resize(2);
	y2.at(0) = 2.0;
	y2.at(1) = 4.0;
	y2.initComputation();
	y2.scale(0.5);
	y2.finishComputation();
	EXPECT_EQ((f32)1.0, y2.at(0));
	EXPECT_EQ((f32)2.0, y2.at(1));
}

TEST_F(Test, TestCudaVector, dot)
{
	Math::CudaVector<f64> x;
	Math::CudaVector<f64> y;
	y.resize(2);
	x.copyStructure(y);
	x.at(0) = 1.0;
	x.at(1) = 2.0;
	y.at(0) = 2.0;
	y.at(1) = 4.0;
	x.initComputation();
	y.initComputation();
	f64 dotproduct = x.dot(y);
	EXPECT_EQ(10.0, dotproduct);

	Math::CudaVector<f32> x2;
	Math::CudaVector<f32> y2;
	y2.resize(2);
	x2.copyStructure(y2);
	x2.at(0) = 1.0;
	x2.at(1) = 2.0;
	y2.at(0) = 2.0;
	y2.at(1) = 4.0;
	x2.initComputation();
	y2.initComputation();
	f32 dotproduct2 = x2.dot(y2);
	EXPECT_EQ((f32)10.0, dotproduct2);
}

TEST_F(Test, TestCudaVector, columnwiseSquaredEuclideanDistance)
{
	Math::CudaMatrix<f32> A;
	Math::CudaVector<f32> v;
	Math::CudaVector<f32> dist;
	A.resize(2,3);
	A.at(0,0) = 1.0;
	A.at(0,1) = 2.0;
	A.at(0,2) = 4.0;
	A.at(1,0) = 6.0;
	A.at(1,1) = 0.0;
	A.at(1,2) = 4.0;
	v.resize(2);
	v.at(0) = 1;
	v.at(1) = -1;
	dist.resize(3);
	A.initComputation();
	v.initComputation();
	dist.initComputation();
	dist.columnwiseSquaredEuclideanDistance(A, v);
	dist.finishComputation();
	EXPECT_EQ(dist.at(0), 49.0f);
	EXPECT_EQ(dist.at(1), 2.0f);
	EXPECT_EQ(dist.at(2), 34.0f);

	Math::CudaMatrix<f64> A2;
	Math::CudaVector<f64> v2;
	Math::CudaVector<f64> dist2;
	A2.resize(2,3);
	A2.at(0,0) = 1.0;
	A2.at(0,1) = 2.0;
	A2.at(0,2) = 4.0;
	A2.at(1,0) = 6.0;
	A2.at(1,1) = 0.0;
	A2.at(1,2) = 4.0;
	v2.resize(2);
	v2.at(0) = 1;
	v2.at(1) = -1;
	dist2.resize(3);
	A2.initComputation();
	v2.initComputation();
	dist2.initComputation();
	dist2.columnwiseSquaredEuclideanDistance(A2, v2);
	dist2.finishComputation();
	EXPECT_EQ(dist2.at(0), 49.0);
	EXPECT_EQ(dist2.at(1), 2.0);
	EXPECT_EQ(dist2.at(2), 34.0);
}

TEST_F(Test, TestCudaVector, columnwiseInnerProduct)
{
	Math::CudaMatrix<f64> A;
	Math::CudaMatrix<f64> B;
	Math::CudaVector<f64> v;
	A.resize(3,2);
	B.resize(3,2);
	v.resize(2);
	A.at(0,0) = 0;
	A.at(0,1) = 1;
	A.at(1,0) = -1;
	A.at(1,1) = -2;
	A.at(2,0) = 3;
	A.at(2,1) = -2;
	B.at(0,0) = 1;
	B.at(0,1) = -4;
	B.at(1,0) = -3;
	B.at(1,1) = 2;
	B.at(2,0) = 4;
	B.at(2,1) = 3;
	A.initComputation();
	B.initComputation();
	v.initComputation();
	v.columnwiseInnerProduct(A, B);
	v.finishComputation();
	EXPECT_EQ(15.0, v.at(0));
	EXPECT_EQ(-14.0, v.at(1));

	Math::CudaMatrix<f32> A2;
	Math::CudaMatrix<f32> B2;
	Math::CudaVector<f32> v2;
	A2.resize(3,2);
	B2.resize(3,2);
	v2.resize(2);
	A2.at(0,0) = 0;
	A2.at(0,1) = 1;
	A2.at(1,0) = -1;
	A2.at(1,1) = -2;
	A2.at(2,0) = 3;
	A2.at(2,1) = -2;
	B2.at(0,0) = 1;
	B2.at(0,1) = -4;
	B2.at(1,0) = -3;
	B2.at(1,1) = 2;
	B2.at(2,0) = 4;
	B2.at(2,1) = 3;
	A2.initComputation();
	B2.initComputation();
	v2.initComputation();
	v2.columnwiseInnerProduct(A2, B2);
	v2.finishComputation();
	EXPECT_EQ(15.0f, v2.at(0));
	EXPECT_EQ(-14.0f, v2.at(1));
}

TEST_F(Test, TestCudaVector, elementwiseMultiplication)
{
	Math::CudaVector<f64> x;
	Math::CudaVector<f64> y;
	x.resize(2);
	y.resize(2);
	x.at(0) = 1.0;
	x.at(1) = 2.0;
	y.at(0) = 2.0;
	y.at(1) = 4.0;
	x.initComputation();
	y.initComputation();
	x.elementwiseMultiplication(y);
	x.finishComputation();
	EXPECT_EQ(2.0, x.at(0));
	EXPECT_EQ(8.0, x.at(1));

	Math::CudaVector<f32> x2;
	Math::CudaVector<f32> y2;
	x2.resize(2);
	y2.resize(2);
	x2.at(0) = 1.0;
	x2.at(1) = 2.0;
	y2.at(0) = 2.0;
	y2.at(1) = 4.0;
	x2.initComputation();
	y2.initComputation();
	x2.elementwiseMultiplication(y2);
	x2.finishComputation();
	EXPECT_EQ((f32)2.0, x2.at(0));
	EXPECT_EQ((f32)8.0, x2.at(1));
}

TEST_F(Test, TestCudaVector, elementwiseDivision)
{
	Math::CudaVector<f64> x;
	Math::CudaVector<f64> y;
	x.resize(2);
	y.resize(2);
	x.at(0) = 1.0;
	x.at(1) = 2.0;
	y.at(0) = 2.0;
	y.at(1) = 4.0;
	x.initComputation();
	y.initComputation();
	y.elementwiseDivision(x);
	y.finishComputation();
	EXPECT_EQ(2.0, y.at(0));
	EXPECT_EQ(2.0, y.at(1));

	Math::CudaVector<f32> x2;
	Math::CudaVector<f32> y2;
	x2.resize(2);
	y2.resize(2);
	x2.at(0) = 1.0;
	x2.at(1) = 2.0;
	y2.at(0) = 2.0;
	y2.at(1) = 4.0;
	x2.initComputation();
	y2.initComputation();
	y2.elementwiseDivision(x2);
	y2.finishComputation();
	EXPECT_EQ((f32)2.0, y2.at(0));
	EXPECT_EQ((f32)2.0, y2.at(1));
}

TEST_F(Test, TestCudaVector, divide)
{
	Math::CudaVector<f64> y;
	y.resize(2);
	y.at(0) = 2.0;
	y.at(1) = 4.0;
	y.initComputation();
	y.divide(2.0);
	y.finishComputation();
	EXPECT_EQ(1.0, y.at(0));
	EXPECT_EQ(2.0, y.at(1));

	Math::CudaVector<f32> y2;
	y2.resize(2);
	y2.at(0) = 2.0;
	y2.at(1) = 4.0;
	y2.initComputation();
	y2.divide(2.0);
	y2.finishComputation();
	EXPECT_EQ((f32)1.0, y2.at(0));
	EXPECT_EQ((f32)2.0, y2.at(1));
}

TEST_F(Test, TestCudaVector, fill)
{
	Math::CudaVector<f64> y;
	y.resize(2);
	y.initComputation();
	y.fill(10.0);
	y.finishComputation();
	EXPECT_EQ(10.0, y.at(0));
	EXPECT_EQ(10.0, y.at(1));

	Math::CudaVector<f32> y2;
	y2.resize(2);
	y2.initComputation();
	y2.fill(10.0);
	y2.finishComputation();
	EXPECT_EQ((f32)10.0, y2.at(0));
	EXPECT_EQ((f32)10.0, y2.at(1));
}

TEST_F(Test, TestCudaVector, l1norm)
{
	Math::CudaVector<f64> y;
	y.resize(2);
	y.at(0) = 2.0;
	y.at(1) = -4.0;
	y.initComputation();
	f64 norm = y.l1norm();
	y.finishComputation();
	EXPECT_EQ(6.0, norm);

	Math::CudaVector<f32> y2;
	y2.resize(2);
	y2.at(0) = 2.0;
	y2.at(1) = -4.0;
	y2.initComputation();
	f32 norm2 = y2.l1norm();
	y2.finishComputation();
	EXPECT_EQ((f32)6.0, norm2);
}

TEST_F(Test, TestCudaVector, sum)
{
	Math::CudaVector<f64> y;
	y.resize(2);
	y.at(0) = 2.0;
	y.at(1) = -4.0;
	y.initComputation();
	EXPECT_EQ(-2.0, y.sum());

	Math::CudaVector<f32> y2;
	y2.resize(2);
	y2.at(0) = 2.0;
	y2.at(1) = -4.0;
	y2.initComputation();
	EXPECT_EQ(-2.0, y.sum());
}

TEST_F(Test, TestCudaVector, normEuclidean)
{
	Math::CudaVector<f64> y;
	y.resize(2);
	y.at(0) = 3.0;
	y.at(1) = -4.0;
	y.initComputation();
	f64 norm = y.normEuclidean();
	y.finishComputation();
	EXPECT_EQ(5.0, norm);

	Math::CudaVector<f32> y2;
	y2.resize(2);
	y2.at(0) = 3.0;
	y2.at(1) = -4.0;
	y2.initComputation();
	f32 norm2 = y2.normEuclidean();
	y2.finishComputation();
	EXPECT_EQ((f32)5.0, norm2);
}

TEST_F(Test, TestCudaVector, addSummedColumns){
	Math::CudaVector<f32> x(2);
	x.at(0) = 0.0;
	x.at(1) = 1.0;
	x.initComputation();

	Math::CudaMatrix<f32> X(2,3);
	X.at(0,0) = 0.0f;
	X.at(0,1) = -1.0f;
	X.at(0,2) = 2.0f;
	X.at(1,0) = -3.0f;
	X.at(1,1) = 4.0f;
	X.at(1,2) = -5.0f;
	X.initComputation();
	x.addSummedColumns(X,2.0);
	x.finishComputation();
	EXPECT_EQ(2.0f, x.at(0));
	EXPECT_EQ(-7.0f, x.at(1));
}
TEST_F(Test, TestCudaVector, addSummedColumnsChannelWise) {
	Math::CudaVector<f32> b_32(3);
	Math::CudaVector<f64> b_64(3);

	b_32.setToZero(); b_64.setToZero();

	Math::CudaMatrix<f64> m_64(12, 10);
	Math::CudaMatrix<f32> m_32(12, 10);

	m_64.setToZero(); m_32.setToZero();

	for(u32 i=0; i<12; i++)
	{
		for(u32 j=0; j<10; j++)
		{
			m_64.at(i, j) = i; m_32.at(i, j) = i;
		}
	}

	m_32.initComputation();
	m_64.initComputation();
	b_32.initComputation();
	b_64.initComputation();

	b_32.addSummedColumnsChannelWise(m_32, 3);
	b_64.addSummedColumnsChannelWise(m_64, 3);

	m_32.finishComputation(false);
	m_64.finishComputation(false);
	b_32.finishComputation();
	b_64.finishComputation();

	EXPECT_EQ(60.0f, b_32.at(0)); EXPECT_DOUBLE_EQ(60.0, b_64.at(0), 0.0000001);
	EXPECT_EQ(220.0f, b_32.at(1)); EXPECT_DOUBLE_EQ(220.0, b_64.at(1), 0.0000001);
	EXPECT_EQ(380.0f, b_32.at(2)); EXPECT_DOUBLE_EQ(380.0, b_64.at(2), 0.0000001);
}
TEST_F(Test, TestCudaVector, addSquaredSummedColumns){
	Math::CudaVector<f32> x(2);
	x.at(0) = 0.0;
	x.at(1) = 1.0;
	x.initComputation();

	Math::CudaMatrix<f32> X(2,3);
	X.at(0,0) = 0.0f;
	X.at(0,1) = -1.0f;
	X.at(0,2) = 2.0f;
	X.at(1,0) = -3.0f;
	X.at(1,1) = 4.0f;
	X.at(1,2) = -5.0f;
	X.initComputation();
	x.addSquaredSummedColumns(X,2.0);
	x.finishComputation();
	EXPECT_EQ(10.0f, x.at(0));
	EXPECT_EQ(101.0f, x.at(1));
}

TEST_F(Test, TestCudaVector, addSummedRows){
	Math::CudaVector<f32> x(3);
	x.at(0) = -1.0f;
	x.at(1) = 0.0f;
	x.at(2) = 1.0f;
	x.initComputation();

	Math::CudaMatrix<f32> X(5,3);
	X.at(0,0) = 3.0f;
	X.at(0,1) = -1.0f;
	X.at(0,2) = 2.0f;
	X.at(1,0) = -5.0f;
	X.at(1,1) = 3.0f;
	X.at(1,2) = 0.0f;
	X.at(2,0) = 2.0f;
	X.at(2,1) = 0.0f;
	X.at(2,2) = 1.0f;
	X.at(3,0) = 0.0f;
	X.at(3,1) = 1.0f;
	X.at(3,2) = 5.0f;
	X.at(4,0) = 2.0f;
	X.at(4,1) = -4.0f;
	X.at(4,2) = 8.0f;

	X.initComputation();

	x.addSummedRows(X,2.0);
	x.finishComputation();
	EXPECT_EQ(3.0f, x.at(0));
	EXPECT_EQ(-2.0f, x.at(1));
	EXPECT_EQ(33.0f, x.at(2));

	x.at(0) = -1.0f;
	x.at(1) = 0.0f;
	x.at(2) = 1.0f;
	x.initComputation();

	x.addSummedRows(X);
	x.finishComputation();
	EXPECT_EQ(1.0f, x.at(0));
	EXPECT_EQ(-1.0f, x.at(1));
	EXPECT_EQ(17.0f, x.at(2));


}


TEST_F(Test, TestCudaVector, addSummedRowsFast){
	Math::CudaVector<f32> x(2);
	x.at(0) = -1.0;
	x.at(1) = 1.0;
	x.initComputation();

	Math::CudaMatrix<f32> X(100,2);
	for (u32 i = 0; i < 100; i++){
		X.at(i, 0) = (f32) i;
		X.at(i, 1) = (f32) -(i+1.0f);
	}
	//    std::cout << "INIT" << std::endl;
	//    X.show();
	//    std::cout << "-----" << std::endl;
	X.initComputation();

	Math::CudaMatrix<f32> tmp(32,2);
	tmp.initComputation(false);
	//    X.syncAndShow();
	//    x.syncAndShow();
	x.addSummedRows(X, tmp, 2.0);
	x.finishComputation();
	//    x.show();
	EXPECT_EQ(9899.0f, x.at(0));
	EXPECT_EQ(-10099.0f, x.at(1));
}



TEST_F(Test, TestCudaVector, getMaxOfColumns){
	Math::CudaVector<f32> x(3);
	x.initComputation();

	Math::CudaMatrix<f32> X(5,3);
	X.at(0,0) = 1.0f;
	X.at(0,1) = -1.0f;
	X.at(0,2) = 2.0f;
	X.at(1,0) = -5.0f;
	X.at(1,1) = 3.0f;
	X.at(1,2) = 0.0f;
	X.at(2,0) = 2.0f;
	X.at(2,1) = 0.0f;
	X.at(2,2) = 1.0f;
	X.at(3,0) = 0.0f;
	X.at(3,1) = 1.0f;
	X.at(3,2) = 5.0f;
	X.at(4,0) = 2.0f;
	X.at(4,1) = -4.0f;
	X.at(4,2) = 8.0f;

	X.initComputation();

	x.getMaxOfColumns(X);
	x.finishComputation();
	EXPECT_EQ(2.0f, x.at(0));
	EXPECT_EQ(3.0f, x.at(1));
	EXPECT_EQ(8.0f, x.at(2));
}


TEST_F(Test, TestCudaVector, max){
	Math::CudaVector<f32> x(5);
	x.at(0) = -1.5;
	x.at(1) = 0.0;
	x.at(2) = 1.0;
	x.at(3) = 0.5;
	x.at(4) = -0.5;
	x.initComputation();
	f32 result = x.max();
	EXPECT_EQ(1.0f, result);
}


TEST_F(Test, TestCudaVector, getMaxOfColumnsFast){
	Math::CudaVector<f32> x(2);
	x.initComputation();

	Math::CudaMatrix<f32> X(100,2);
	for (u32 i = 0; i < 100; i++){
		X.at(i, 0) = (f32) (i % 7);
		X.at(i, 1) = (f32) (i / 6);
	}
	X.initComputation();

	Math::CudaMatrix<f32> tmp(32,2);
	tmp.initComputation(false);

	x.getMaxOfColumns(X, tmp);
	x.finishComputation();
	EXPECT_EQ(6.0f, x.at(0));
	EXPECT_EQ(16.0f, x.at(1));
}

TEST_F(Test, TestCudaVector, swapWithVector)
{
	Math::CudaVector<f64> x;
	Math::CudaVector<f64> y;
	x.resize(3);
	y.resize(3);
	x.at(0) = 1.0;
	x.at(1) = -2.0;
	x.at(2) = -4.0;
	y.at(0) = 3.5;
	y.at(1) = -1.5;
	y.at(2) = 0.0;
	x.initComputation();
	y.initComputation();
	x.swap(y);
	x.finishComputation();
	EXPECT_EQ(3.5, x.at(0));
	EXPECT_EQ(-1.5, x.at(1));
	EXPECT_EQ(0.0, x.at(2));

	Math::CudaVector<f32> x2;
	Math::CudaVector<f32> y2;
	x2.resize(3);
	y2.resize(3);
	x2.at(0) = 1.0;
	x2.at(1) = -2.0;
	x2.at(2) = -4.0;
	y2.at(0) = 3.5;
	y2.at(1) = -1.5;
	y2.at(2) = 0.0;
	x2.initComputation();
	y2.initComputation();
	x2.swap(y2);
	x2.finishComputation();
	EXPECT_EQ((f32)3.5, x2.at(0));
	EXPECT_EQ((f32)-1.5, x2.at(1));
	EXPECT_EQ((f32)0.0, x2.at(2));
}

TEST_F(Test, TestCudaVector, swapWithMatrix)
{
	Math::CudaMatrix<f64> A;
	Math::CudaVector<f64> v;
	A.resize(2,2);
	v.resize(3);
	A.initComputation();
	v.initComputation();
	A.setToZero();
	A.addConstantElementwise(1.0);
	v.setToZero();
	v.addConstantElementwise(2.0);
	v.swap(A);
	A.finishComputation();
	v.finishComputation();
	EXPECT_EQ(3u, A.nRows());
	EXPECT_EQ(1u, A.nColumns());
	EXPECT_EQ(4u, v.nRows());
	for (u32 i = 0; i < A.nRows(); i++) {
		EXPECT_EQ(2.0, A.at(i,0));
	}
	for (u32 i = 0; i < v.nRows(); i++) {
		EXPECT_EQ(1.0, v.at(i));
	}
}

TEST_F(Test, TestCudaVector, isFinite)
{
	Math::CudaVector<f64> x;
	x.resize(4);
	x.setToZero();
	EXPECT_TRUE(x.isFinite());
	x.at(2) = std::log(0.0);
	EXPECT_FALSE(x.isFinite());
	x.at(2) = std::sqrt(-1.0);
	EXPECT_FALSE(x.isFinite());

	Math::CudaVector<f32> x2;
	x2.resize(4);
	x2.setToZero();
	EXPECT_TRUE(x2.isFinite());
	x2.at(2) = std::log(0.0f);
	EXPECT_FALSE(x2.isFinite());
	x2.at(2) = std::sqrt(-1.0f);
	EXPECT_FALSE(x2.isFinite());
}

TEST_F(Test, TestCudaVector, rpropUpdate)
{
	Math::CudaVector<f64> weights;
	Math::CudaVector<f64> newGradients;
	Math::CudaVector<f64> oldGradients;
	Math::CudaVector<f64> updateValues;
	weights.resize(6);
	newGradients.copyStructure(weights);
	oldGradients.copyStructure(weights);
	updateValues.copyStructure(weights);

	weights.at(0) = 3.0;
	weights.at(1) = 2.0;
	weights.at(2) = 1.0;
	weights.at(3) = -1.0;
	weights.at(4) = -2.0;
	weights.at(5) = -3.0;

	newGradients.at(0) = 2.0;
	newGradients.at(1) = -1.0;
	newGradients.at(2) = 1.0;
	newGradients.at(3) = 2.0;
	newGradients.at(4) = -2.5;
	newGradients.at(5) = 0.0;

	oldGradients.at(0) = -2.0;
	oldGradients.at(1) = 3.0;
	oldGradients.at(2) = 0.0;
	oldGradients.at(3) = 1.5;
	oldGradients.at(4) = -1.0;
	oldGradients.at(5) = 2.0;

	updateValues.at(0) = -1.0;
	updateValues.at(1) = 2.0;
	updateValues.at(2) = 1.5;
	updateValues.at(3) = -2.0;
	updateValues.at(4) = 1.0;
	updateValues.at(5) = -1.5;

	weights.initComputation();
	newGradients.initComputation();
	oldGradients.initComputation();
	updateValues.initComputation();

	weights.rpropUpdate(newGradients, oldGradients, updateValues, 1.2, 0.5, 100, -0.0001);

	weights.finishComputation();
	newGradients.finishComputation();
	oldGradients.finishComputation();
	updateValues.finishComputation();

	EXPECT_EQ(3.0001, weights.at(0));
	EXPECT_EQ(3.0, weights.at(1));
	EXPECT_EQ(-0.5, weights.at(2));
	EXPECT_EQ(1.4, weights.at(3));
	EXPECT_EQ(-0.8, weights.at(4));
	EXPECT_EQ(-3.0, weights.at(5));

}
