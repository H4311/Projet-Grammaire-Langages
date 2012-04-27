#include <boost/program_options.hpp>
#include <iostream>
#include <iterator>
#include <string>
#include <fstream>

#include "xml/xml_processor.h"
#include "dtd/dtd.h"
#include "validation/Validateur.hpp"

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
			("validate", "Validates the xml file with the dtd file.")
			("showxml", "Shows the content of the xml file, if one is given.")
			("showdtd", "Shows the content of the dtd file, if one is given.")
		;

		po::variables_map vm;
		po::store(po::parse_command_line(ac, av, desc), vm);
		po::notify(vm);    

		bool atLeastOneOption = false;
		bool hasXml = false, hasDtd = false;

		xml::Document* xmlDoc = NULL;
		if (vm.count("xml")) {
			xmlDoc = parseXML(vm["xml"].as<string>().c_str());
			if (xmlDoc!= NULL)
			{
				hasXml = true;
				if (vm.count("showxml")) cout << *xmlDoc << "\n" << endl;
			}
			atLeastOneOption = true;
		}

		dtd::Document* dtdDoc = NULL;
		if (vm.count("dtd"))
		{
			dtdDoc = parseDTD(vm["dtd"].as<string>().c_str());
			if (dtdDoc != NULL)
			{
				hasDtd = true;
				if (vm.count("showdtd")) cout << dtdDoc << "\n" << endl;
			}
			atLeastOneOption = true;
		}

		if (vm.count("validate"))
		{
			if (hasXml && hasDtd)
			{
				if (Validateur::validationDocument(*dtdDoc, *xmlDoc))
				{
					cout << "The XML file is conform to the DTD file." << endl;
				} else {
					cout << "Error : the XML file is not conform to the DTD file." << endl;
				}
			} else {
				cout << "There is either no dtd or xml file. Please retry." << endl;
			}
			atLeastOneOption = true;
		}

		if (hasXml) delete xmlDoc;
		if (hasDtd) delete dtdDoc;

		if (vm.count("help") || !atLeastOneOption) {
			cout << desc << endl;
			return 1;
		}

	} catch(exception& e) {
        cerr << "error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
    
}
