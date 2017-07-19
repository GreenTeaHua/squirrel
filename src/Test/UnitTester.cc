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

#include <iostream>
#include <string>
#include <vector>
#include <cppunit/TestFailure.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TextTestProgressListener.h>
#include <cppunit/TextOutputter.h>
#include <Test/UnitTest.hh>
#include <Test/Registry.hh>
#include <Core/Configuration.hh>

namespace UnitTest {

class ProgressListener: public CppUnit::TestListener
{
public:
	ProgressListener() : curTestFailure_(false), allTestsPassed_(true) {}
	virtual ~ProgressListener() {}

	virtual void startSuite(CppUnit::Test *suite)
	{
		std::string name = suite->getName();
		if (name.empty()) name = "unnamed";
		std::cerr
		<< name
		<< " (" << suite->getChildTestCount() << ")"
		<< std::endl;
	}

	virtual void startTest(CppUnit::Test *test)
	{
		std::cerr
		<< "    "
		<< (test->getName().empty() ? "n/a" : test->getName())
		<< std::endl;
		curTestFailure_ = false;
	}

	virtual void addFailure(const CppUnit::TestFailure &failure)
	{
		curTestFailure_ = true;
		allTestsPassed_ = false;
	}

	virtual void endTest(CppUnit::Test *test)
	{
		std::cerr
		<< "        => "
		<< (curTestFailure_ ? "FAILED" : "OK")
		<< std::endl;
	}

	bool allTestsPassed() const { return allTestsPassed_; }

private:
	ProgressListener(const ProgressListener &copy);
	void operator =(const ProgressListener &copy);
	bool curTestFailure_, allTestsPassed_;
};


class UnitTester
{
public:
	UnitTester() {}

	int main();

protected:
	CppUnit::Test* findTest(CppUnit::Test *root, const std::string &name);
};

CppUnit::Test* UnitTester::findTest(CppUnit::Test *root, const std::string &name)
{
	std::deque<CppUnit::Test*> to_visit;
	to_visit.push_back(root);
	while (!to_visit.empty()) {
		CppUnit::Test *t = to_visit.front();
		to_visit.pop_front();
		if (t->getName() == name)
			return t;
		for (int i = 0; i < t->getChildTestCount(); ++i) {
			to_visit.push_back(t->getChildTestAt(i));
		}
	}
	return 0;
}


int UnitTester::main()
{
	CppUnit::TestResult controller;
	CppUnit::TestResultCollector result;
	controller.addListener(&result);
	ProgressListener progressListener;
	controller.addListener(&progressListener);
	CppUnit::TestRunner runner;
	Test::TestSuiteRegistry &registry = Test::TestSuiteRegistry::instance();
	CppUnit::Test *root = registry.makeTest();
	// run all known tests
	runner.addTest(root);

	runner.run(controller);
	CppUnit::TextOutputter output(&result, std::cout);
	output.write();
	return !progressListener.allTestsPassed();
}

} // namespace

int main(int argc, const char* argv[]) {
	// create an empty configuration
	Core::Configuration::initialize(argc, argv);

	UnitTest::UnitTester unitTester;
	return unitTester.main();
}
