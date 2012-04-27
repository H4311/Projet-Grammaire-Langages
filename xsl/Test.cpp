

/**
 * @file Test.hpp
 * @brief Tests - XSL
 * 
 * Contains the test functions for the XSL processor and HTML generator.
 * 
 * @author Benjamin PLANCHE
 */

# include <iostream>

using namespace std;

#include "XSLProcessor.hpp"
#include "../xml/xml_processor.h"
#include "../dtd/dtd.h"

using namespace xsl;

# include "../tests/TestFramework.hpp"

struct XSLProcessTest_NoXSLDTD : public TestCase
{
	XSLProcessTest_NoXSLDTD() : TestCase("<fr> Vérifier que le traitement s'arrête en l'absence de DTD XSL") {}
	bool operator()()
	{
		xml::Document* document ;
		try{
			document = NULL;
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
			delete docDtd;
			if( s == XSLProcessor::ERROR_NO_XMLNS){
				return true;
			}else{
				return false;
			}
		}
		delete docDtd;
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
				delete docDtd;
				delete docXml;
				return true;
			}
		}
		delete docDtd;
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
		dtd::Document* dtdHTML = parseDTD("./tests/xsl.dtd");
		
		try{
			
			XSLProcessor xslProcessor = XSLProcessor();
			xslProcessor.setXslDTD(documentDTD);
			xslProcessor.processXslFile(documentXSL);
		}catch(string s) {
			if( s == XSLProcessor::ERROR_INVALID_XSL_SEMANTIC ){
				delete documentXSL;
				delete documentDTD;
				return true;
			}
		}
		delete documentXSL;
		delete documentDTD;
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
				delete documentDTD;
				return true;
			}
		}
		delete documentXSL;
		delete documentDTD;
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
		
		docXml = parseXML("./tests/rapport.xsl");
		docDtd = parseDTD("./tests/xsl.dtd");
		
		try {
			proc.setXslDTD(docDtd);
			proc.processXslFile(docXml);
		} catch(string s) {
			cout << s;
			delete docXml;
			delete docDtd;
			return false;
		}
		
		delete docXml;
		delete docDtd;

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
			delete dtdXSL;
			delete documentXSL;
			delete documentXML;
			delete documentHTML;
			return false;
		}
		// Validation Humaine
		cout << *documentHTML << endl;
		delete dtdXSL;
		delete documentXSL;
		delete documentXML;
		delete documentHTML;

		return true;
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
			documentXML = parseXML("./tests/testApplyTemplates.xml");
			documentHTML = xslProcessor.generateHtmlFile(documentXML);
		}catch(string s){
			delete dtdXSL;
			delete documentXSL;
			delete documentXML;
			delete documentHTML;
			return false;
		}
		// Validation Humaine
		cout << documentHTML << endl;
		delete dtdXSL;
		delete documentXSL;
		delete documentXML;
		delete documentHTML;

		return true;
	}
};

struct HTMLGenerationTest_Attribute : public TestCase
{
	HTMLGenerationTest_Attribute() : TestCase("<fr> Vérifier le HTML généré, avec un XSL contenant des noeuds attributes") {}
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
			documentXML = parseXML("./tests/testAttribute.xml");
			documentHTML = xslProcessor.generateHtmlFile(documentXML);
		}catch(string s){
			delete dtdXSL;
			delete documentXSL;
			delete documentXML;
			delete documentHTML;
			return false;
		}
		// Validation Humaine
		cout << documentHTML << endl;
		delete dtdXSL;
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
			documentXSL = parseXML("testComplex.xsl");
			xslProcessor.processXslFile(documentXSL);
			documentXML = parseXML("testComplex.xml");
			documentHTML = xslProcessor.generateHtmlFile(documentXML);
		}catch(string s){
			delete documentXSL;
			delete documentXML;
			delete documentHTML;
			return false;
		}
		// Validation Humaine
		cout << documentHTML << endl;
		delete documentXSL;
		delete documentXML;
		delete documentHTML;
		return true;
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
			documentXSL = parseXML("testNoRoot.xsl");
			xslProcessor.processXslFile(documentXSL);
			documentXML = parseXML("testComplex.xml");
			documentHTML = xslProcessor.generateHtmlFile(documentXML);
		}catch(string s){
			delete documentXSL;
			delete documentXML;
			delete documentHTML;
			return false;
		}
		// On test si root == "null"
		xml::Element* elRoot = dynamic_cast<xml::Element*>(documentHTML->getRoot());
		if ((elRoot == NULL)  || (elRoot->getName() != "null")) {
			delete documentXSL;
			delete documentXSL;
			delete documentXML;
			delete documentHTML;
			return false;
		}
		// Validation Humaine
		cout << documentHTML << endl;
		delete documentXSL;
		delete documentXSL;
		delete documentXML;
		delete documentHTML;
		return true;
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

	suite.add(new HTMLGenerationTest_Complex);

	suite.add(new HTMLGenerationTest_ApplyTemplates);

	suite.add(new HTMLGenerationTest_Attribute);

	suite.add(new HTMLGenerationTest_NoRoot);
	
	suite.launch();
	
}



