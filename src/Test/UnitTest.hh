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

#ifndef _TEST_UNIT_TEST_HH
#define _TEST_UNIT_TEST_HH

/**
 * Sprint Unit Testing Framework
 *
 * What is a unit test?
 *
 * A unit test verifies the functionality of individual units of source code.
 * A unit is the smallest testable part of an application, in our case a class.
 * Have a look in the literature for more detailed descriptions of the
 * principles of unit testing.
 *
 *
 * How to write unit tests?
 *
 * - Create a file Test/<Module>_<SourceFile>.cc
 *   e.g. Test/Core_StringUtilities.cc
 * - Write test cases using TEST() or TEST_F()  (see below)
 * - add the new file to Test/Makefile to the TEST_O target
 * - run 'make test' in src/Test
 *
 * Simple test cases are defined using
 *   TEST(Module, TestSuite, TestCase) {
 *       // test code
 *   }
 *
 * More complex tests can be defined using a TestFixture:
 *
 * class MyTest : public Test::Fixture {
 * public:
 *     void setUp() {
 *         // initialize and create test data
 *         // using member variables
 *     }
 *     void tearDown() {
 *         // delete test data
 *     }
 * protected:
 *     // shared members
 * }
 *
 * TEST_F(Module, MyTest, Foo) {
 *     // test behavior "Foo"
 *     // using the initialized members
 * }
 *
 * TEST_F(Module, MyTest, Bar) {
 *     // another test case using the same data
 * }
 *
 * The individual tests have to use the EXPECT_* macros (see below).
 * For example
 *     EXPECT_EQ(10, value);
 *     EXPECT_TRUE(doit());
 *
 * See Test/Core_StringUtilities.cc for an example.
 *
 *
 * The unit testing framework is based on CppUnit.
 * See http://cppunit.sourceforge.net/doc/lastest/cppunit_cookbook.html
 */

#include <map>
#include <cassert>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>
#include <Test/Registry.hh>
#include <Core/Configuration.hh>

#define EXPECT_TRUE(v) CPPUNIT_ASSERT(v)
#define EXPECT_FALSE(v) CPPUNIT_ASSERT(!(v))
#define EXPECT_EQ(x, y) CPPUNIT_ASSERT_EQUAL(x, y)
#define EXPECT_DOUBLE_EQ(x, y, d) CPPUNIT_ASSERT_DOUBLES_EQUAL(x, y, d)
#define EXPECT_GE(x, y) CPPUNIT_ASSERT((x) >= (y))
#define EXPECT_NE(x, y) CPPUNIT_ASSERT((x) != (y))
#define EXPECT_GT(x, y) CPPUNIT_ASSERT((x) > (y))
#define EXPECT_LE(x, y) CPPUNIT_ASSERT((x) <= (y))
#define EXPECT_LT(x, y) CPPUNIT_ASSERT((x) < (y))

namespace Test
{
/**
 * Test fixture see comments above.
 */
typedef CppUnit::TestFixture Fixture;


/**
 * Test fixture for classes derived from Core::Configurable / Core::Component,
 * which require a configuration object.
 *
 * Use like this:
 *
 * class MyTest : public Test::ConfigurableFixture
 * {
 * public:
 *     void setUp() {
 *         setParameter("param-a", "1");
 *         setParameter("param-x", "abc");
 *         obj_ = new MyClass(config);
 *     }
 *
 *     void tearDown() {
 *         delete obj_;
 *     }
 * protected:
 *     MyClass *obj_;
 * };
 *
 * TEST_F(Module, MyTest, Foo)
 * {
 *     EXPECT_EQ(obj_->value(), 1);
 * }
 *
 */

} // namespace Test


#define STR(s) #s

// Define a test function N in TestSuite S.
#define TEST(M, S, N) \
		class TestCase_ ## M ## _ ## S ## _ ## N : public CppUnit::TestCase { \
		public: \
		TestCase_ ## M ## _ ## S ## _ ## N(std::string name) : CppUnit::TestCase(name) {} \
		virtual ~TestCase_ ## M ## _ ## S ## _ ## N () {} \
		static CppUnit::Test *suite() { \
			CppUnit::TestSuite *suite = new CppUnit::TestSuite(STR(S ## _ ## N)); \
			suite->addTest(new TestCase_ ## M ## _ ## S ## _ ## N("")); \
			return suite; \
		} \
		void runTest(); \
}; \
static Test::RegisterTestCase<TestCase_ ## M ## _ ## S ## _ ## N> \
Register_TestCase_ ## M ## _ ## S ## _ ## N(STR(M), STR(S), STR(N)); \
void TestCase_ ## M ## _ ## S ## _ ## N::runTest()

// Define a test case N for test fixture S.
#define TEST_F(M, S, N) \
		class TestFixture_ ## M ## _ ## S ## _ ## N : public S { \
		public: \
		TestFixture_ ## M ## _ ## S ## _ ## N () {} \
		virtual ~TestFixture_ ## M ## _ ## S ## _ ## N () {} \
		void TEST_ ## N (); \
}; \
static Test::RegisterTest<TestFixture_ ## M ## _ ## S ## _ ## N> \
Register_TestFixture_ ## M ## _ ## S ## _ ## N(\
		STR(M), STR(S), STR(N), \
		& TestFixture_ ## M ## _ ## S ## _ ## N ::TEST_ ## N); \
		void TestFixture_ ## M ## _ ## S ## _ ## N ::TEST_ ## N ()


#endif  // _TEST_UNIT_TEST_HH
