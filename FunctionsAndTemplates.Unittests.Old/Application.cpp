#include <iostream>
#include <string>
#include "../FunctionsAndTemplates/MemFunctor.h"


struct LOL
{
	int lol()
	{
		return 5;
	}

	void printSomethingInLOL(const std::string& test)
	{
		std::cout << "Printing from LOL: " << test << std::endl;
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

	void printthis(const std::string& input)
	{
		std::cout << input + " " + std::to_string(i) << std::endl;
	}

	int i;
};

int anotherlol()
{
	return 2;
}

void testi()
{
	std::cout << "Testi" << std::endl;
}

void swagtest(const std::string& input)
{
	std::cout << "swagtest: " << input << std::endl;
}

typedef void empty;

int main()
{
	Deligate<const std::string&> response;
	Deligate<void> anotherResponse;

	anotherResponse.add(&testi);
	anotherResponse.invoke();

	stringTester stringT(5);
	LOL lolT;
	

	response.add(&stringTester::printthis, &stringT);
	response.add(&LOL::printSomethingInLOL, &lolT);
	response.add(&swagtest);

	response.invoke("Hej med dig");

	//LOL qwe;
	//auto test = mem_fc(&LOL::lol);

	//stringTester tester(5);

	//auto anotherTester = mem_fc(&stringTester::printthis);

	//auto sponk = [](int a) { return a; };

	//std::cout << anotherTester(&tester, "Hej med dig, hvordan går det?");

	////auto testOne = memfc<int()>(&anotherlol);

	//auto testTwo = mem_fc(&anotherlol);

	//auto derp = mem_fc(&swagtest);

	//std::cout << "Hello world" << test(&qwe) << std::endl;
}