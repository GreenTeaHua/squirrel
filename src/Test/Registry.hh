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

#ifndef _TEST_REGISTRY_HH
#define _TEST_REGISTRY_HH

#include <map>
#include <string>
#include <cppunit/Test.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/TestFactory.h>

namespace Test {

/**
 * Registry for all test cases.
 */
class TestSuiteRegistry: public CppUnit::TestFactory
{
public:
	typedef void (*TestMethod)();

	/**
	 * return the only TestSuiteRegistry instance (singleton)
	 */
	static TestSuiteRegistry& instance();

	/**
	 * add a test case to the given test suite.
	 */
	bool addTest(const std::string &module, const std::string &suiteName, CppUnit::Test *test);

	/**
	 * generate a CppUnit test case including all registered test cases.
	 */
	CppUnit::Test* makeTest();

	virtual ~TestSuiteRegistry() {}
protected:
	typedef std::map<std::string, CppUnit::TestSuite*> SuiteMap;
	typedef std::map<std::string, SuiteMap> ModuleMap;
	ModuleMap modules_;

private:
	TestSuiteRegistry() {}
	static TestSuiteRegistry *instance_;
};


/**
 * adds a test case to the registry.
 * to be used as static object.
 */
template<class T>
class RegisterTest
{
public:
	RegisterTest(const std::string &module, const std::string &suiteName,
			const std::string &testName, void(T::*m)()) :
				registry_(TestSuiteRegistry::instance())
{
		registry_.addTest(module, suiteName, new CppUnit::TestCaller<T>(testName, m));
}
protected:
	RegisterTest() : registry_(TestSuiteRegistry::instance()) {}
	TestSuiteRegistry &registry_;
};

/**
 * adds a test fixture to the registry.
 * to be used as static object.
 */
template<class T>
class RegisterTestCase: public RegisterTest<T>
{
public:
	RegisterTestCase(const std::string &module, const std::string &suiteName, const std::string &testName)
{
		this->registry_.addTest(module, suiteName, new T(testName));
}
};

}  // namespace Test

#endif  // _TEST_REGISTRY_HH
