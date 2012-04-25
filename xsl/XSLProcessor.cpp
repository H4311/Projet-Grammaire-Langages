#include <iostream>

/**
* @file XSLProcessor.cpp
* @brief Implementation - XSL processing functions
* Contains the implementation of the XSL Processor class, and thus the functions to validate a XSL stylesheet and parse XML files into HTML using it.
* @author Daniel BAUDRY & Benjamin Bill PLANCHE (Aldream)
*/
#include "XSLProcessor.hpp"
#include "xml_processor.h"
#include "Element.hpp"
#include "EmptyElement.hpp"
#include "Document.hpp"
#include "basics.h"
 
using namespace std;

xsl::XSLProcessor::XSLProcessor() {
	xslDTDdoc = NULL;
	xslDoc = NULL;

}

void xsl::XSLProcessor::processXslDTDFile(string name) {
	// --- Analyse the syntax of the XSL DTD file. If OK, continue.
	/** @todo Analyse the XSL DTD file. If OK, continue. */
	xml::Document* newXslDTDdoc;
	
	// --- Analyse the syntax of the HTML DTD file. The link to this DTD can be found into the attribute xmlns:xsl of the element xsl:stylesheet.
	/** @todo Analyse the syntax of the HTML DTD file. */
	xml::Element* rootXSLDTD = dynamic_cast<xml::Element*>(newXslDTDdoc->getRoot());
	if (rootXSLDTD == NULL) {
		return false; // <Error> Invalid or empty XSL DTD document.
	
	
	// --- Everything is OK with the new DTD : we delete the ancient one and replace by the new.
	delete xslDTDdoc;
	xslDTDdoc = newXslDTDdoc;
	return true;
}


bool xsl::XSLProcessor::processXslFile(string xslFileName) {
	
	xml::Document* newXsldoc;
	
	// --- Analyse the syntax of the XSL file. If OK, continue.
	/** @todo Analyse the syntax of the XSL file. If OK, continue. */
	
		
	// --- Analyse the syntax of the HTML DTD file. The link to this DTD can be found into the attribute xmlns:xsl of the element xsl:stylesheet.
	/** @todo Analyse the syntax of the HTML DTD file. */
	
	// --------- Finding the path to the HTML DTD, contained by the attribut "xmlns:xsl" of the element "xsl:stylesheet" :
	xml::Element* rootXSL = dynamic_cast<xml::Element*>(xslDoc->getRoot());
	if (rootXSL == NULL) {
		return false; // <Error> Invalid or empty XSL document.
	}
	
	list<xml::Content*>::iterator itelementXSL = rootXSL->getChildren().begin();
	xml::EmptyElement* elStylesheet;
	while  (itelementXSL != rootXSL->getChildren().end()) {
		xml::EmptyElement* elXSL = dynamic_cast<xml::Element*>(*itelementXSL);
		if ( (elXSL != NULL) && (elXSL->getName() == "xsl:stylesheet") ) {
			elStylesheet = elXSL;
			break;
		 }
		itelementXSL++;
	}
	if (itelementXSL == rootXSL->getChildren().end()) {
		return false; // <Error> Unfound elementcontaining the path to HTML DTD file.
	}	
	
	string attrXMLNS = elStylesheet->GetAttributeValue("xmlns:xsl");
	if (attrXMLNS.empty()) {
		return false; // <Error> Unfound "xmlns:xsl" attribute.
	}		
	
	// --------- Opening, validating ant getting the structure of the HTML DTD file :
	xml::Document * htmlDTDdoc;
	/** @todo : Document * htmlDTDdoc = DTDValidator.parse(attrXMLNS.second); */
	if (htmlDTDdoc == NULL) {
		return false; // <Error> Invalid or unfound HTML DTD file.
	}
	
	xml::Element* rootHTMLDTD = dynamic_cast<xml::Element*>(htmlDTDdoc->getRoot());
	if (rootHTMLDTD == NULL) {
		return false; // <Error> Invalid HTML DTD File - Invalid root.
	}
	
	// --- Fusion the XSL DTD and the HTML DTD into a new DTD (only valid used for this XSL)
	Document* xslhtmlDTDdoc = new Document();
	/** @todo : Copy xslDTDdoc into xslhtmlDTDdoc */
	xml::Element* rootXSLHTMLDTD = dynamic_cast<xml::Element*>(xslhtmlDTDdoc->getRoot());
	list<xml::Content*> xslDTDelements = rootXSLHTMLDTD->getChildren();
	for( list<xml::Content*>::const_iterator it = rootHTMLDTD->getChildren().begin();  it != rootHTMLDTD->getChildren().end(); it++) {
		xslDTDelements.push_back(*it);
	}
	rootXSLHTMLDTD->SetChildren(&xslDTDelements);
	
	// Semantic analysis :
	bool semanticCorrectness = true;
	/** @todo Analyse the semantic correctness of the XSL file :  semanticCorrectness = DTDValidator.validate(xslDoc, xslDTDdoc); */
	if (!semanticCorrectness) {
		return false; // if false : <Error> Invalid XSL file : doesn't respect the given DTD.
	}
	
	// --- Everything is OK with the new XSL : we delete the ancient one and replace by the new.
	delete xslDoc;
	xslDoc = newXsldoc;
	
	delete xslhtmlDTDdoc;
	
	return true;
}

bool xsl::XSLProcessor::generateHtmlFile(string xmlFileName, string htmlOutputFile) {

	// Checking if an valid XSL file as already been processed :
	if (xslDoc == NULL) { return false; }

	Document* xmlDoc;
	Document htmlDoc;
	
	// Loading the XML File
	File xmlFile = fopen(xmlFileName, "r");
	
	// Analyse the syntax of the XML file
	xmlDoc = parseXML(xmlFile);
	/** @todo Processing the return. */
	
	/** @todo Verifying its semantic correctness */
	
	
	
	
	
	/** @todo
	 * - Load the XML file
	 * - Analyse the syntax of the XML file & verify its semantic correctness
	 * - Save the file structure into xmlDoc
	 * - For each tp xsl:template element into  xslDoc, do : (�)
	 *		- name <- tp["match"];
			- For each el XML element having its name == name
				- For each hel HTML element of tp
					- if (hel.name == "apply-template"), then apply recursively the process since the symbol �
					- htmlDoc.insert(content);
	 */
	
	return true;
}


Element* xsl::XSLProcessor::conversionHTML( Element* XMLElement, Element* HTMLElement ){
	
	Element* XSLTemplate = findTemplate( XMLElement.getName() );
	
	if( XSLTemplate == NULL ){
		list<Content*> contentsXML = XMLElement->getRoot()->getChildren();
	
		for(list<Content*>::iterator itHtml = contentsHtml->begin();
				itHtml != contentsHtml->end(); itHtml++)
		{
			//Test si Data ou pas
			Element* rootXMLCopy = dynamic_cast<Data*>(XMLCopy->getChildren());
			if( XMLCopy != NULL ) {
				HTMLElement.append( XMLCopy );
			}else{
				conversionHTML( currentElement, HTMLElement);
			}
		}
		
	}else{
		applyTemplate( XMLElement, XSLTemplate );
		// HTMLElement doit changer
	}
}


Element* findTemplate( string XMLElementName ){
	
	list<Content*> contentsXsl = xslDoc->getChildren();
	
	for(list<Content*>::iterator itXsl = contentsXsl->begin();
			itXsl != contentsXsl->end(); itXsl++)
	{
		xml::Content* currentElement = dynamic_cast<xml::Content*>(*itXsl);
		/** @todo Comment */
		if( currentElement != NULL &&
			currentElement->getName() == "template"  &&
			currentElement->GetAttributeValue("match") == XMLElementName ){
				
				return *currentElement;
		}
	}
	return NULL;
}


void applyTemplate( Element* XMLElement, Element* XSLTemplate ) {
	
	// Dynamic_cast de XSLTemplate->getRoot() en Element*
	list<Content*> contentsHtml = XSLTemplate->getRoot()->getChildren();
	list<Content*> contentsXML = XMLElement->getRoot()->getChildren();
	
	for(list<Content*>::iterator itHtml = contentsHtml->begin();
			itHtml != contentsHtml->end(); itHtml++)
	{
		currentElement = (*itHtml);
		if( currentElement->getName() == "value-of" ){
			string htmlTag = currentElement->GetAttributeValue("value-of");
			
			// Find the value in the xml file
			
			// Replace the value in the html file
		}
	}
}
