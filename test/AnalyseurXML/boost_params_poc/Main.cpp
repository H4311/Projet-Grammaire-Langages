#include <boost/program_options.hpp>
#include <iostream>
#include <iterator>
#include <string>
#include <fstream>

using namespace std;
namespace po = boost::program_options;

int main(int ac, char * av[])
{
	try {
		po::options_description desc("Allowed options");
		desc.add_options()
			("help", "produce help message")
			("xml", po::value<string>(), "Set xml file to parse")
			("dtd", po::value<string>(), "Set dtd file to parse")
		;

		po::variables_map vm;
		po::store(po::parse_command_line(ac, av, desc), vm);
		po::notify(vm);    

		if (vm.count("help")) {
			cout << desc << endl;
			return 1;
		}

		if (vm.count("xml")) {
			cout << "xml file " << vm["xml"].as<string>() << endl;
			
			string line;
			ifstream fic(vm["xml"].as<string>().c_str());
			if (fic.is_open())
			{
				while (fic.good())
				{
					getline(fic, line);
					cout << line << endl;
				}
				
				fic.close();
			}
			
		}
		if (vm.count("dtd"))
		{
			cout << "dtd file " << vm["dtd"].as<string>() << endl;
		}
	
	} catch(exception& e) {
        cerr << "error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
    
}
