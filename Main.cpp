#include <boost/program_options.hpp>
#include <iostream>
#include <iterator>
#include <string>
#include <fstream>

#include "xml/xml_processor.h"
#include "dtd/dtd.h"

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
			xml::Document* document = NULL;
			document = parseXML(vm["xml"].as<string>().c_str());
			// TODO do something with document
			cout << *document << "\n" << endl;
			delete document;
		}
		if (vm.count("dtd"))
		{
			parseDTD(vm["dtd"].as<string>().c_str());
		}
	
	} catch(exception& e) {
        cerr << "error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
    
}
