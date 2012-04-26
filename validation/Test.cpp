#include "Validateur.hpp"
#include "../dtd/Document.hpp"
#include "../dtd/Element.hpp"
#include "../dtd/Attribute.hpp"
#include "../dtd/AttributeList.hpp"
#include "../dtd/Name.hpp"
#include "../dtd/Choice.hpp"
#include "../dtd/Seq.hpp"

#include "../xml/Content.hpp"
#include "../xml/Element.hpp"
#include "../xml/Data.hpp"
#include "../xml/Comment.hpp"
#include "../xml/ProcessingInstruction.hpp"
#include "../xml/Document.hpp"

// Pour parser les xml et dtd
#include "../xml/xml_processor.h"
#include "../dtd/dtd.h"

#include <iostream>
#include <list>


// Doc XML
xml::Document* dXML;

// Doc DTD
dtd::Document* dDTD;

int main(int argc, char** argv) {
	
	
	dXML = parseXML("../tests/rap1.xml");
	dDTD = parseDTD("../tests/rap1.dtd");
	
	//cout << dDTD << endl;
	
	cout << "==== Test 1 validationDocument ====" << endl;
	
	if(Validateur::validationDocument(*dDTD, *dXML)) {
		cout << "Document 1 validé" << endl;
	} else {
		cout << "Document 1 non validé" << endl;
	}
	
	dXML = parseXML("../tests/rap2.xml");
	dDTD = parseDTD("../tests/rap2.dtd");
	
	//cout << dDTD << endl;
	
	cout << "==== Test 2 validationDocument ====" << endl;
	
	if(Validateur::validationDocument(*dDTD, *dXML)) {
		cout << "Document 2 validé" << endl;
	} else {
		cout << "Document 2 non validé" << endl;
	}
	
	dXML = parseXML("../tests/rap3.xml");
	dDTD = parseDTD("../tests/rap3.dtd");
	
	//cout << dDTD << endl;
	
	cout << "==== Test 3 validationDocument ====" << endl;
	
	if(Validateur::validationDocument(*dDTD, *dXML)) {
		cout << "Document 3 validé" << endl;
	} else {
		cout << "Document 3 non validé" << endl;
	}
	
	delete dXML;
	delete dDTD;
	
	return 0;
}
