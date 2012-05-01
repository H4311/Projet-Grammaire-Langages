#include <boost/program_options.hpp>
#include <iostream>
#include <iterator>
#include <string>
#include <fstream>

#include "xml/xml_processor.h"
#include "dtd/dtd.h"
#include "validation/Validateur.hpp"

#include "xsl/XSLProcessor.hpp"

using namespace std;
namespace po = boost::program_options;

int main(int ac, char * av[])
{
	try {
		po::options_description desc("Allowed options");
		desc.add_options()
			("help", "produce help message")
			("xml", po::value<string>(), "Set xml file to parse")
			("xsl", po::value<string>(), "Set xsl file to parse")
			("dtdxml", po::value<string>(), "Set xml dtd file to parse")
			("dtdxsl", po::value<string>(), "Set xml dtd file to parse")
			("validate", "Validates the xml and/or xsl file with the dtd files.")
			("showxml", "Shows the content of the xml file, if one is given.")
			("showdtdxml", "Shows the content of the xml dtd file, if one is given.")
			("showdtdxsl", "Shows the content of the xsl dtd file, if one is given.")
			("showxsl", "Shows the content of the xsl file, if one is given.")
			("showhtml", "Shows the content of the generated html file, if a xsl and xml files are given.")
		;

		po::variables_map vm;
		po::store(po::parse_command_line(ac, av, desc), vm);
		po::notify(vm);    

		bool atLeastOneOption = false;
		bool hasXml = false, hasDtd = false, hasXsl = false, hasXslDtd = false;
		bool xslProcessorOwnsXslDtd = false;

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
		if (vm.count("dtdxml"))
		{
			dtdDoc = parseDTD(vm["dtdxml"].as<string>().c_str());
			if (dtdDoc != NULL)
			{
				hasDtd = true;
				if (vm.count("showdtdxml")) cout << dtdDoc << "\n" << endl;
			}
			atLeastOneOption = true;
		}

		xml::Document* xslDoc = NULL;
		if (vm.count("xsl")) {
			xslDoc = parseXML(vm["xsl"].as<string>().c_str());
			if (xslDoc!= NULL)
			{
				hasXsl = true;
				if (vm.count("showxsl")) cout << *xslDoc << "\n" << endl;
			}
			atLeastOneOption = true;
		}

		dtd::Document* xslDtdDoc = NULL;
		if (vm.count("dtdxsl"))
		{
			xslDtdDoc = parseDTD(vm["dtdxsl"].as<string>().c_str());
			if (xslDtdDoc != NULL)
			{
				hasXslDtd = true;
				if (vm.count("showdtdxsl")) cout << xslDtdDoc << "\n" << endl;
			}
			atLeastOneOption = true;
		}

		xsl::XSLProcessor xslProcessor = xsl::XSLProcessor();
		bool xslValidated = false;
		if (vm.count("validate"))
		{
			if (hasXml && hasDtd)
			{
				if (Validateur::validationDocument(*dtdDoc, *xmlDoc))
				{
					cout << "The XML file is conform to the XML-DTD file." << endl;
				} else {
					cout << "Error : the XML file is not conform to the DTD file." << endl;
				}
			} 
			else if (hasXsl && hasXslDtd) {
				try{
					xslProcessor.setXslDTD(xslDtdDoc);
					xslProcessorOwnsXslDtd = true;
					xslProcessor.processXslFile(xslDoc);
					cout << "The XSL file is conform to the XSL-DTD file." << endl;
					xslValidated = true;
				}catch(string s){
					cout << "Error : the XSL file is not conform to the XSL-DTD file. The error is :" << endl;
					cout << s << endl;
				}				
			}
			else {
				cout << "There is either no dtd or xml/xsl file. Please retry." << endl;
			}
			atLeastOneOption = true;
		}

		if (vm.count("showhtml"))
		{
			if (hasXml && hasXsl && hasXslDtd)
			{
				if (xslValidated) {
					xml::Document* documentHTML = xslProcessor.generateHtmlFile(xmlDoc);
					cout << *documentHTML << endl;	
					delete documentHTML;
				}
				else {
					try{
						xslProcessor.setXslDTD(xslDtdDoc);
						xslProcessorOwnsXslDtd = true;
						xslProcessor.processXslFile(xslDoc);
						xml::Document* documentHTML = xslProcessor.generateHtmlFile(xmlDoc);
						cout << *documentHTML << endl;
						delete documentHTML;
					}catch(string s){
						cout << "Error : the XSL file is not conform to the XSL-DTD file. The error is :" << endl;
						cout << s << endl;
					}

				}			
			}
			else {
				cout << "There is either no xsl-dtd or xml or xsl file. Please retry." << endl;
			}
			atLeastOneOption = true;
		}		

		if (hasXml) delete xmlDoc;
		if (hasDtd) delete dtdDoc;
		if (hasXsl) delete xslDoc;
		if (hasXslDtd && !xslProcessorOwnsXslDtd)  delete xslDtdDoc;

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
