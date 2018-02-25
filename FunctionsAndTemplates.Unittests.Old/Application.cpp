#include <iostream>
#include <string>
#include "../FunctionsAndTemplates/MemFunctor.h"


class TestClass
{
public:

	TestClass() : testEvent_(new Deligate<const std::string&>)
	{
		
	}

	void test()
	{
		testEvent_.invoke("Hej");
	}

	void lololol()
	{
		std::cout << "rofl" << std::endl;
	}

	Event<TestClass, const std::string&> testEvent_;
	
private:
	
};

void TestOne(const std::string& testOne)
{
	std::cout << __FUNCTION__ << std::endl;
}

void TestTwo(const std::string& testTwo)
{
	std::cout << __FUNCTION__ << std::endl;
}


int main()
{
	TestClass test;


	Deligate<void> del;

	del.add(&TestClass::lololol);

	//test.testEvent_.add(&TestOne);
	//test.testEvent_.add(&TestTwo);

	

	//test.test();
}