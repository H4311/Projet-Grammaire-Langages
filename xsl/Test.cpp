

/**
 * @file Test.hpp
 * @brief Tests - XSL
 * 
 * Contains the test functions for the XSL processor and HTML generator.
 * 
 * @author Benjamin PLANCHE
 */

# include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "XSLProcessor.hpp"
#include "../xml/xml_processor.h"
#include "../dtd/dtd.h"

using namespace xsl;

# include "../tests/TestFramework.hpp"

bool validationHumaineContenu() {
	string input = "";
	while (true) {
	   	cout << "--------- Validez-vous ce contenu généré ? (o/n)" << endl;
	   	getline(cin, input);
	   	stringstream myStream(input);
		char c = 0;
		myStream >> c;
	  	if (c == 'o' || c == 'O'  || c == 'y' || c == 'Y') {
			return true;
		}
		else if (c == 'n' || c == 'N') {
	     		return false;
		}
	   	cout << "Réponse invalide, veuillez recommencer svp." << endl;
	}
}

struct XSLProcessTest_NoXSLDTD : public TestCase
{
	XSLProcessTest_NoXSLDTD() : TestCase("<fr> Vérifier que le traitement s'arrête en l'absence de DTD XSL") {}
	bool operator()()
	{
		xml::Document* document ;
		try{
			document = parseXML("testSimple.xsl");
			XSLProcessor xslProcessor = XSLProcessor();
			xslProcessor.processXslFile(document);
		}catch(string s){
			delete document;
			if( s == XSLProcessor::ERROR_NO_DTD){
				return true;
			}else{
				return false;
			}
		}
		delete document;
		return false;
	}
};

struct XSLProcessTest_NoHTMLDTD : public TestCase
{
	XSLProcessTest_NoHTMLDTD() : TestCase("<fr> Vérifier que le traitement s'arrête en l'absence de DTD HTML") {}
	bool operator()()
	{
		xml::Document* document = NULL;
		dtd::Document* docDtd;
		
		docDtd = parseDTD("tests/html.dtd");
		document = parseXML("tests/testNoHTMLDTD.xsl");
		XSLProcessor xslProcessor = XSLProcessor();
		try{
			xslProcessor.setXslDTD(docDtd);
			xslProcessor.processXslFile(document);
		}catch(string s){
			delete document;
			if( s == XSLProcessor::ERROR_NO_XMLNS){
				return true;
			}else{
				return false;
			}
		}
		delete document;
		return false;
	}
};

struct XSLProcessTest_InvalidHTMLDTD : public TestCase
{
	XSLProcessTest_InvalidHTMLDTD () : TestCase("<fr> Vérifier que le traitement s'arrête si la DTD HTML est invalide") {}
	bool operator()()
	{
		xml::Document* docXml;
		dtd::Document* docDtd;
		XSLProcessor proc = XSLProcessor();
		
		docXml = parseXML("./tests/testHtmlDtdInvalid.xsl");
		docDtd = parseDTD("./tests/xsl.dtd");
		
		try {
			proc.setXslDTD(docDtd);
			proc.processXslFile(docXml);
		} catch(std::string s) {
			if (s == XSLProcessor::ERROR_INVALID_HTML_DTD) {
				delete docXml;
				return true;
			}
		}
		delete docXml;
		return false;
	}
};


struct XSLProcessTest_InvalidSemanticXSL : public TestCase
{
	XSLProcessTest_InvalidSemanticXSL() : TestCase("<fr> Vérifier que le traitement s'arrête si le XSL est invalide sémantiquement") {}
	bool operator()()
	{
		xml::Document* documentXSL = NULL;
		documentXSL = parseXML("./tests/rapportSemanticXSL.xsl");
		dtd::Document* documentDTD = NULL;
		documentDTD = parseDTD("./tests/xsl.dtd");
		
		try{
			XSLProcessor xslProcessor = XSLProcessor();
			xslProcessor.setXslDTD(documentDTD);
			xslProcessor.processXslFile(documentXSL);
		} catch(string s) {
			if( s == XSLProcessor::ERROR_INVALID_XSL_SEMANTIC ){
				delete documentXSL;
				return true;
			}
		}
		delete documentXSL;
		return false;
	}
	

};

struct XSLProcessTest_InvalidSemanticHTML : public TestCase
{
	XSLProcessTest_InvalidSemanticHTML() : TestCase("<fr> Vérifier que le traitement s'arrête si le HTML est invalide sémantiquement") {}
	bool operator()()
	{
		xml::Document* documentXSL = NULL;
		documentXSL = parseXML("./tests/rapportSemanticHTML.xsl");
		dtd::Document* documentDTD = NULL;
		documentDTD = parseDTD("./tests/xsl.dtd");

		try{
			XSLProcessor xslProcessor = XSLProcessor();
			xslProcessor.setXslDTD(documentDTD);
			xslProcessor.processXslFile(documentXSL);
		}catch(string s){
		
			if( s == XSLProcessor::ERROR_INVALID_XSL_SEMANTIC ){
				delete documentXSL;
				return true;
			}
		}
		delete documentXSL;
		return false;
	}
};

struct XSLProcessTest_OK : public TestCase
{
	XSLProcessTest_OK() : TestCase("<fr> Vérifier que la structure XSL générée correspond au document donné") {}
	bool operator()()
	{
		xml::Document* docXml;
		dtd::Document* docDtd;
		xsl::XSLProcessor proc;
		
		docXml = parseXML("./tests/testSimple.xsl");
		docDtd = parseDTD("./tests/xsl.dtd");
		
		try {
			proc.setXslDTD(docDtd);
			proc.processXslFile(docXml);
		} catch(string s) {
			cout << s << endl;
			delete docXml;
			return false;
		}
		
		delete docXml;
		return true;
	}
};

struct HTMLGenerationTest_NoXSL : public TestCase
{
	HTMLGenerationTest_NoXSL() : TestCase("<fr> Vérifier que la génération HTML s'arrête en l'absence de XSL") {}
	bool operator()()
	{
		xml::Document* documentXML = NULL;
		documentXML = parseXML("./tests/undefined.xml");
		try{
			XSLProcessor xslProcessor = XSLProcessor();
			xslProcessor.generateHtmlFile(documentXML);
		}catch(string s){
			if( s == XSLProcessor::ERROR_NO_XSL ){
				delete documentXML;
				return true;
			}
		}
		delete documentXML;
		return false;
	}
};

struct HTMLGenerationTest_Simple : public TestCase
{
	HTMLGenerationTest_Simple() : TestCase("<fr> Vérifier le HTML généré, avec des documents XSL et XML simples") {}
	bool operator()()
	{
		dtd::Document* dtdXSL = NULL;
		xml::Document* documentXSL = NULL;
		xml::Document* documentXML = NULL;
		xml::Document* documentHTML = NULL;
		try{
			dtdXSL = parseDTD("./tests/xsl.dtd");
			xsl::XSLProcessor xslProcessor = XSLProcessor();
			xslProcessor.setXslDTD(dtdXSL);
			documentXSL = parseXML("./tests/testSimple.xsl");
			xslProcessor.processXslFile(documentXSL);
			documentXML = parseXML("./tests/testSimple.xml");
			documentHTML = xslProcessor.generateHtmlFile(documentXML);
		}catch(string s){
			cout << s << endl;
			delete documentXSL;
			delete documentXML;
			delete documentHTML;
			return false;
		}
		// Validation Humaine
		cout << *documentHTML << endl;
		cout << "--------- Ce document est valide s'il contient du HTML simple avec du contenu sans rapport avec le XML (\"Hello World !\", ...)" << endl;
		bool ok = validationHumaineContenu();
		delete documentXSL;
		delete documentXML;
		delete documentHTML;

		return ok;
	}
};

struct HTMLGenerationTest_ApplyTemplates : public TestCase
{
	HTMLGenerationTest_ApplyTemplates() : TestCase("<fr> Vérifier le HTML généré, avec un XSL contenant des noeuds apply-templates") {}
	bool operator()()
	{
		dtd::Document* dtdXSL = NULL;
		xml::Document* documentXSL = NULL;
		xml::Document* documentXML = NULL;
		xml::Document* documentHTML = NULL;
		try{
			dtdXSL = parseDTD("./tests/xsl.dtd");
			xsl::XSLProcessor xslProcessor = XSLProcessor();
			xslProcessor.setXslDTD(dtdXSL);
			documentXSL = parseXML("./tests/testApplyTemplates.xsl");
			xslProcessor.processXslFile(documentXSL);
			documentXML = parseXML("./tests/testComplex.xml");
			documentHTML = xslProcessor.generateHtmlFile(documentXML);
		}catch(string s){
			cout << s << endl;
			delete documentXSL;
			delete documentXML;
			delete documentHTML;
			return false;
		}
		bool validation = false;
		try {
			xml::Element * root = static_cast<xml::Element*>(documentHTML->getRoot());
			if (root == NULL) return false;
			xml::Element * body = static_cast<xml::Element*>( *(++root->getChildren().begin()) );
			if (body == NULL) return false;
			list<xml::Content*>::iterator h2Content = ++body->getChildren().begin();
			h2Content = ++h2Content;
			xml::Element * h2El = static_cast<xml::Element*>(*h2Content);
			if ((h2El != NULL) && (h2El->getName() == "h2")) {
				cout << *documentHTML << endl;
				cout << "--------- Ce document est valide s'il contient des noeuds générés par d'autres templates que celui de la racine. Il doit donc contenir ici des noeuds de type <h2>, <p>, ..." << endl;
				validation = validationHumaineContenu();

			}
		} catch(exception e){}		
		delete documentXSL;
		delete documentXML;
		delete documentHTML;

		return validation;
	}
};

struct HTMLGenerationTest_Attribute : public TestCase
{
	HTMLGenerationTest_Attribute() : TestCase("<fr> Vérifier le HTML généré, avec un XSL contenant des noeuds attribute") {}
	bool operator()()
	{
		dtd::Document* dtdXSL = NULL;
		xml::Document* documentXSL = NULL;
		xml::Document* documentXML = NULL;
		xml::Document* documentHTML = NULL;
		try{
			dtdXSL = parseDTD("./tests/xsl.dtd");
			xsl::XSLProcessor xslProcessor = XSLProcessor();
			xslProcessor.setXslDTD(dtdXSL);
			documentXSL = parseXML("./tests/testAttribute.xsl");
			xslProcessor.processXslFile(documentXSL);
			documentXML = parseXML("./tests/testComplex.xml");
			documentHTML = xslProcessor.generateHtmlFile(documentXML);
		}catch(string s){
			cout << s << endl;
			delete documentXSL;
			delete documentXML;
			delete documentHTML;
			return false;
		}
		bool validation = false;
		try {
			xml::Element * root = static_cast<xml::Element*>(documentHTML->getRoot());
			if (root == NULL) return false;
			xml::Element * body = static_cast<xml::Element*>( *(++root->getChildren().begin()) );
			if (body == NULL) return false;
			xml::EmptyElement * img = static_cast<xml::EmptyElement*>( *(++body->getChildren().begin()) );
			if ((img != NULL) && (img->getAttributeValue("src") == "http://google.fr/img") && (img->getAttributeValue("title") == "Test !")) {
				validation = true;

			}
		} catch(exception e){}		
		delete documentXSL;
		delete documentXML;
		delete documentHTML;

		return validation;

	}
};


struct HTMLGenerationTest_ValueOf : public TestCase
{
	HTMLGenerationTest_ValueOf() : TestCase("<fr> Vérifier le HTML généré, avec un XSL contenant des noeuds value-of") {}
	bool operator()()
	{
		dtd::Document* dtdXSL = NULL;
		xml::Document* documentXSL = NULL;
		xml::Document* documentXML = NULL;
		xml::Document* documentHTML = NULL;
		try{
			dtdXSL = parseDTD("./tests/xsl.dtd");
			xsl::XSLProcessor xslProcessor = XSLProcessor();
			xslProcessor.setXslDTD(dtdXSL);
			documentXSL = parseXML("./tests/testValueOf.xsl");
			xslProcessor.processXslFile(documentXSL);
			documentXML = parseXML("./tests/testComplex.xml");
			documentHTML = xslProcessor.generateHtmlFile(documentXML);
		}catch(string s){
			delete documentXSL;
			delete documentXML;
			delete documentHTML;
			return false;
		}
		// Validation Humaine
		cout << "--------- Ce document est valide s'il contient du HTML complexe, dont le contenu couvre l'intégralité du XML donné." << endl;
		cout << *documentHTML << endl;
		delete documentXSL;
		delete documentXML;
		delete documentHTML;
		return true;
	}
};



struct HTMLGenerationTest_Complex : public TestCase
{
	HTMLGenerationTest_Complex() : TestCase("<fr> Vérifier le HTML généré, avec des documents XSL et XML plus complexes") {}
	bool operator()()
	{
		dtd::Document* dtdXSL = NULL;
		xml::Document* documentXSL = NULL;
		xml::Document* documentXML = NULL;
		xml::Document* documentHTML = NULL;
		try{
			dtdXSL = parseDTD("./tests/xsl.dtd");
			xsl::XSLProcessor xslProcessor = XSLProcessor();
			xslProcessor.setXslDTD(dtdXSL);
			documentXSL = parseXML("./tests/testComplex.xsl");
			xslProcessor.processXslFile(documentXSL);
			documentXML = parseXML("./tests/testComplex.xml");
			documentHTML = xslProcessor.generateHtmlFile(documentXML);
		}catch(string s){
			cout << s << endl;
			delete documentXSL;
			delete documentXML;
			delete documentHTML;
			return false;
		}
		// Validation Humaine
		bool ok = false;
		cout << "--------- Ce document est valide s'il contient du HTML complexe, dont le contenu couvre l'intégralité du XML donné." << endl;
		cout << *documentHTML << endl;
		ok = validationHumaineContenu();
		delete documentXSL;
		delete documentXML;
		delete documentHTML;
		return ok;
	}
};

struct HTMLGenerationTest_NoRoot : public TestCase
{
	HTMLGenerationTest_NoRoot() : TestCase("<fr> Vérifier le HTML généré, avec un XSL n'ayant pas de template pour la racine XML") {}
	bool operator()()
	{
		dtd::Document* dtdXSL = NULL;
		xml::Document* documentXSL = NULL;
		xml::Document* documentXML = NULL;
		xml::Document* documentHTML = NULL;
		try{
			dtdXSL = parseDTD("./tests/xsl.dtd");
			xsl::XSLProcessor xslProcessor = XSLProcessor();
			xslProcessor.setXslDTD(dtdXSL);
			documentXSL = parseXML("tests/testNoRoot.xsl");
			xslProcessor.processXslFile(documentXSL);
			documentXML = parseXML("tests/testComplex.xml");
			documentHTML = xslProcessor.generateHtmlFile(documentXML);
		}catch(string s){
			delete documentXSL;
			delete documentXML;
			delete documentHTML;
			return false;
		}
		bool ok = false;
		// On test si root == "null"
		xml::Element* elRoot = dynamic_cast<xml::Element*>(documentHTML->getRoot());
		if ((elRoot != NULL)  || (elRoot->getName() == "null")) {
	  		cout << *documentHTML << endl;
			cout << "--------- Ce document est valide s'il contient une racine de type <null>, contenant les éléments fils." << endl;
			ok = validationHumaineContenu();
		}

		delete documentXSL;
		delete documentXML;
		delete documentHTML;
		return ok;
	}
};

int main(int argc, char** argv)
{
	TestSuite suite;
	
	suite.add(new XSLProcessTest_NoXSLDTD);

	suite.add(new XSLProcessTest_NoHTMLDTD);

	suite.add(new XSLProcessTest_InvalidHTMLDTD);
	
	suite.add(new XSLProcessTest_InvalidSemanticXSL);

	suite.add(new XSLProcessTest_InvalidSemanticHTML);

	suite.add(new XSLProcessTest_OK);

	suite.add(new HTMLGenerationTest_NoXSL);

	suite.add(new HTMLGenerationTest_Simple);

	suite.add(new HTMLGenerationTest_ApplyTemplates);

	suite.add(new HTMLGenerationTest_Attribute);

	suite.add(new HTMLGenerationTest_ValueOf);

	suite.add(new HTMLGenerationTest_NoRoot);

	suite.add(new HTMLGenerationTest_Complex);
	
	suite.launch();
}

