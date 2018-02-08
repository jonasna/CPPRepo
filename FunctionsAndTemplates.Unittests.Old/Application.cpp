#include <iostream>
#include <string>
#include "../FunctionsAndTemplates/MemFunctor.h"


struct LOL
{
	int lol()
	{
		return 5;
	}
};

class stringTester
{
public:

	stringTester(int i = 0)
	{
		this->i = i;
	}

	void doThat()
	{
		std::cout << "I is: " << i << std::endl;
	}

	std::string printthis(const std::string& input)
	{
		return input + " " + std::to_string(i);
	}

	int i;
};

int anotherlol()
{
	return 2;
}

std::string swagtest(const std::string& input, int lol)
{
	return input;
}

int main()
{
	LOL qwe;
	auto test = mem_fc(&LOL::lol);

	stringTester tester(5);

	auto anotherTester = mem_fc(&stringTester::printthis);

	std::cout << anotherTester(&tester, "Hej med dig, hvordan går det?");

	//auto testOne = memfc<int()>(&anotherlol);

	auto testTwo = mem_fc(&anotherlol);

	auto derp = mem_fc(&swagtest);

	std::cout << "Hello world" << test(&qwe) << std::endl;
}