#include <windows.h>
#include <vector>
#include "unit_test.h"

// for setting color of the text
enum ETextColor
{
	Red = 12,
	Green = 10,
	White = 15
};

// call this in pairs (set color, print stuff, set white)
void SetTextColor(ETextColor color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

// contains all tests
class TestManager
{
public:
	// it's a singleton
	static TestManager& GetInstance()
	{
		static TestManager mgr;
		return mgr;
	}

	// this is called by Test constructor
	void AddTest(Test* test)
	{
		m_tests.push_back(test);
	}

	// call this in main
	void RunAllTests()
	{
		SetTextColor(White);
		printf("Run %llu tests:\n", m_tests.size());

		int numFailed = 0;

		for (Test* test : m_tests)
		{
			if (!test->Execute())
			{
				numFailed++;
			}
		}

		if (numFailed > 0)
			SetTextColor(Red);
		else
			SetTextColor(Green);

		printf("%i out of %llu tests failed.\n", numFailed, m_tests.size());

		SetTextColor(White);
	}

private:
	std::vector<Test*> m_tests;
};

Test::Test(const char* category, const char* name) : m_category(category)
, m_name(name)
, m_hasPassed(true)
{
	TestManager::GetInstance().AddTest(this);
}

bool Test::Execute()
{
	SetTextColor(White);
	printf("  Test %hs::%hs ", m_category, m_name);

	OnExecute();

	if (m_hasPassed)
	{
		SetTextColor(Green);
		printf("SUCCEEDED\n");
	}

	return m_hasPassed;
}

void Test::Assert(bool condition, const char* message)
{
	if (!condition)
	{
		SetTextColor(Red);
		if (m_hasPassed)
		{
			printf("FAILED\n");
		}

		m_hasPassed = false;

		printf("    %hs\n", message);
	}
}

void RunAllTests()
{
	TestManager::GetInstance().RunAllTests();
}
