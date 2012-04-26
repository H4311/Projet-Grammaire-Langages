# ifndef __TEST_FRAMEWORK_H__
# define __TEST_FRAMEWORK_H__

struct TestCase
{
	TestCase(string _desc) { desc = _desc; }
	virtual bool operator()() = 0;

	string desc;
};

class TestSuite
{
	private:
		void printTestHeader(string desc)
		{
			static int testNum = 0;
			++testNum;
			cout.width(80);
			cout.fill('*');
			cout << "\n";
			cout << "Test " << testNum << " : " << desc << "\n";
			cout.width(80);
			cout.fill('*');
			cout << "\n";
		}

		list<TestCase*> tests;

	public:
	~TestSuite()
	{
		for(list<TestCase*>::iterator it = tests.begin(); it != tests.end(); ++it)
		{
			delete *it;
		}
	}

	void add(TestCase * t)
	{
		tests.push_back(t);
	}

	void launch()
	{
		for(list<TestCase*>::iterator it = tests.begin(); it != tests.end(); ++it)
		{
			printTestHeader((*it)->desc);
			cout << "Test " << ( ( (**it)() ) ? "réussi" : "échoué") << endl;
		}
		cout.width(80);
		cout.fill('*');
		cout << '\n' << endl;
	}
};

# endif
