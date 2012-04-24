#include <iostream>
#include <string>
#include <boost/regex.hpp>

using namespace std;

int main(int argc, char **argv) 
{
	boost::cmatch what;
	
	boost::regex reg1("(titre,)(p,)+");
	string test1("titre,p,p,");
	
	if (regex_match(test1.c_str(), what, reg1)) 
	{
		cout << "Test 1 Matched !" << endl;
	}
	else
	{
		cout << "Test 1 Failed !" << endl;	
	}
	
	string test2("titre,a,p,");
	
	if (regex_match(test2.c_str(), what, reg1)) 
	{
		cout << "Test 2 Matched !" << endl;
	}
	else
	{
		cout << "Test 2 Failed !" << endl;
	}
	
	return 0;
}