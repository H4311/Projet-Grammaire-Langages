
/**
* @file XSLProcessor.cpp
* @brief Implementation - XSL processing functions
* 
* Contains the implementation of the XSL Processor class, and thus the functions to validate a XSL stylesheet and parse XML files into HTML using it.
* 
* @author Daniel BAUDRY & Benjamin Bill PLANCHE (Aldream)
*/

#include <iostream>

#include "XSLProcessor.hpp"

#include "xml/basics.h"
#include "xml/xml_processor.h"
#include "xml/Element.hpp"
#include "xml/Data.hpp"
#include "xml/EmptyElement.hpp"
#include "xml/Document.hpp"

#include "dtd/Document.hpp"
#include "dtd/Declaration.hpp"
#include "dtd/dtd.h"

#include "validation/Validateur.cpp"

 
using namespace std;

xsl::XSLProcessor::XSLProcessor() {
	xslDTDdoc = NULL;
	xslDoc = NULL;

}

bool xsl::XSLProcessor::processXslDTDFile(string name) {
	// --- Analyse the syntax of the XSL DTD file. If OK, continue.
	dtd::Document* newXslDTDdoc = parseDTD(name.c_str());
	if (newXslDTDdoc == NULL) {
		return false; // <Error> Syntax Error - Invalid or empty XSL DTD document.
	}	

	// --- Everything is OK with the new DTD : we delete the ancient one and replace by the new.
	delete xslDTDdoc;
	xslDTDdoc = newXslDTDdoc;
	return true;
}


bool xsl::XSLProcessor::processXslFile(string xslFileName) {
	
	// --- Checking if a DTD has been processed
	if (xslDTDdoc == NULL) {
		return false; // <Error> No DTD. Please process a XSL DTD first.
	}
	// --- Analyse the syntax of the XSL file. If OK, continue.
	xml::Document* newXsldoc = parseXML(xslFileName.c_str());
	if (newXsldoc == NULL) {
		return false; // <Error> Syntax Error - Invalid or empty XSL document.
	}	
		
	// --- Analyse the syntax of the HTML DTD file. The link to this DTD can be found into the attribute xmlns:xsl of the element xsl:stylesheet.
	
	// --------- Finding the path to the HTML DTD, contained by the attribut "xmlns:xsl" of the element "xsl:stylesheet" :
	xml::Element* rootXSL = dynamic_cast<xml::Element*>(xslDoc->getRoot());
	if (rootXSL == NULL) {
		return false; // <Error> Invalid or empty XSL document.
	}
	
	list<xml::Content*>::iterator itelementXSL = rootXSL->getChildren().begin();
	xml::EmptyElement* elStylesheet;
	while  (itelementXSL != rootXSL->getChildren().end()) {
		xml::EmptyElement* elXSL = dynamic_cast<xml::Element*>(*itelementXSL);
		if ( (elXSL != NULL) && (elXSL->getName() == "stylesheet") ) {
			elStylesheet = elXSL;
			break;
		 }
		itelementXSL++;
	}
	if (itelementXSL == rootXSL->getChildren().end()) {
		return false; // <Error> Unfound elementcontaining the path to HTML DTD file.
	}	
	
	string attrXMLNS = elStylesheet->getAttributeValue("xmlns:xsl");
	if (attrXMLNS.empty()) {
		return false; // <Error> Unfound "xmlns:xsl" attribute.
	}		
	
	// --------- Opening, validating ant getting the structure of the HTML DTD file :
	dtd::Document * htmlDTDdoc = parseDTD(attrXMLNS.c_str());
	if (htmlDTDdoc == NULL) {
		return false; // <Error> Syntax Error - Invalid, empty or unfound XSL document.
	}	

	// --- Fusion the XSL DTD and the HTML DTD into a new DTD (only valid used for this XSL) : we copy the XSL DTD into the HTML one.
	list<dtd::Declaration*>* htmlDeclarations =  htmlDTDdoc->getDeclarations();
	list<dtd::Declaration*>* xslDeclarations =  xslDTDdoc->getDeclarations();
	for( list<dtd::Declaration*>::const_iterator it = xslDeclarations->begin();  it != xslDeclarations->end(); it++) {
		htmlDeclarations->push_back(*it);
	}
	htmlDTDdoc->setDeclarations(htmlDeclarations);
	
	// --- Semantic analysis :
	if (Validateur::validationDocument(*htmlDTDdoc, *xslDoc)) {
		return false; // <Error> Semantic Error - Invalid XSL file : doesn't respect the given DTD.
	}
	
	// --- Everything is OK with the new XSL : we delete the ancient one and replace by the new.
	delete xslDoc;
	xslDoc = newXsldoc;
	
	delete htmlDTDdoc;
	
	return true;
}


xml::Document* xsl::XSLProcessor::generateHtmlFile(string xmlFileName) {
	// Checking if an valid XSL file as already been processed :
	if (xslDoc == NULL) {
		return NULL; // <Error> No XSL. Please process a XSL stylesheet first.
	}

	//Processing and validating the XML file :
	xml::Document* xmlDoc = parseXML(xmlFileName.c_str());
	if (xmlDoc == NULL) {
		return NULL; // <Error> Syntax Error - Invalid, empty or unfound XML document.
	}
	/** @todo Analyse the semantic correctness of the XML file :  semanticCorrectness = DTDValidator.validate(xmlDoc, xmlDTDdoc); */
	xml::EmptyElement* rootXML = dynamic_cast<xml::EmptyElement*>(xmlDoc->getRoot());
	xml::Element* xslNode;
	if (rootXML != NULL) { // If it's an empty element or element, we try to find a template to apply :
		xslNode = findTemplate(rootXML->getName());
	}
	list<xml::Content*> listHTMLElements = generateHtmlElement(xslNode, xmlDoc->getRoot());
	xml::Document* docHTML = new xml::Document();
	if (listHTMLElements.size() > 1) { // No generated root, so we add one :
		xml::Element* htmlRoot = new xml::Element();
		htmlRoot->setName(ElementName("","null"));
		htmlRoot->setChildren(listHTMLElements);
		docHTML->setRoot(htmlRoot);
	}
	else if (listHTMLElements.size() == 1) {
		docHTML->setRoot(listHTMLElements.front());
	}
	
	return docHTML;
}

list<xml::Content*> xsl::XSLProcessor::generateHtmlElement(xml::Element* xslNode, xml::Content* xmlNode) {

	list<xml::Content*> htmlNode;

	if (xslNode != NULL) { // We apply this template :
		list<xml::Content*> xslNodeChildren = xslNode->getChildren();
		for(list<xml::Content*>::const_iterator itXSL = xslNodeChildren.begin(); itXSL != xslNodeChildren.end(); itXSL++) {
			xml::Content* htmlChild;
			xml::Element* itXSLEle = dynamic_cast<xml::Element*>(*itXSL);
			if (itXSLEle != NULL) { // If it's an element 
				htmlChild = new xml::Element();
				if (itXSLEle->getNamespace() != "xsl") { // If it's HTML :
					((xml::Element*)htmlChild)->setName(ElementName(itXSLEle->getNamespace(), itXSLEle->getName()));
					((xml::Element*)htmlChild)->setAttList(itXSLEle->getAttList());
					((xml::Element*)htmlChild)->appendChild(generateHtmlElement(itXSLEle, xmlNode));
				}
				else if (itXSLEle->getName() == "apply-templates") {
					// For each child of the current XML node, we try to apply another template :
					xml::Element* xmlEle = dynamic_cast<xml::Element*>(xmlNode);
					if (xmlEle != NULL) { // If it's an element 
						for(list<xml::Content*>::const_iterator itXML = xmlEle->getChildren().begin(); itXML != xmlEle->getChildren().end(); itXML++) {
							xml::Element* xslNodeChild = NULL;
							xml::EmptyElement* itXMLEmp = dynamic_cast<xml::EmptyElement*>(*itXML);
							if (itXMLEmp != NULL) { // If it's an empty element or element, we try to find a template to apply :
								xslNodeChild = findTemplate(itXMLEmp->getName());
							}
							generateHtmlElement(xslNodeChild, *itXML); // recursivity
						}
					}
				}
				else if (itXSLEle->getName() == "value-of") {
					/** @todo Process "value-of" element (overquality) */
				}
				else if (itXSLEle->getName() == "attribute") {
					/** @todo Process "attribute" element (overquality) */
				}					
			}
			else {
				xml::EmptyElement* itXSLEmp = dynamic_cast<xml::EmptyElement*>(*itXSL);
				if (itXSLEmp != NULL) {  // If it's an empty element 
					htmlChild = new xml::EmptyElement();
					((xml::EmptyElement*)htmlChild)->setName(ElementName(itXSLEle->getNamespace(), itXSLEle->getName()));
					((xml::EmptyElement*)htmlChild)->setAttList(itXSLEmp->getAttList());
				}
				else {
					xml::Data* itXSLDat = dynamic_cast<xml::Data*>(*itXSL);
					if (itXSLDat != NULL) {  // If it's an empty element 
						htmlChild = new xml::Data(itXSLDat->getData());
					}
				}
			}

			htmlNode.push_back(htmlChild);
		}
	}
	else { // If we didn't find a template, we only past the inner data, try to apply other templates to the elements children
		for(list<xml::Content*>::const_iterator itXML = xmlNode->getChildren()->begin(); itXML != xmlNode->getChildren()->end(); itXML++) {
			xml::Data* itXMLDat = dynamic_cast<xml::Data*>(*itXML);
			if (itXMLDat != NULL) {  // If it's data, we past it into the html doc :
				htmlNode.push_back(itXMLDat);
			}
			else {
				xml::EmptyElement* itXMLEmp = dynamic_cast<xml::EmptyElement*>(*itXML);
				if (itXMLEmp != NULL) {  // If it's an element (empty or not), we process it :
					xml::Element* xslNodeChild = findTemplate(itXMLEmp->getName());
					generateHTML(xslNodeChild, itXMLEmp); // recursivity
				}
			}

		}
	}

	return htmlNode;
}

xml::Element* xsl::XSLProcessor::findTemplate( string xmlElementName ) {
	
	list<xml::Content*> contentsXsl = xslDoc->getChildren();
	
	for(list<xml::Content*>::iterator itXsl = contentsXsl->begin();
			itXsl != contentsXsl->end(); itXsl++)
	{
		xml::Element* currentElement = dynamic_cast<xml::Element*>(*itXsl);
		/** If it's a template element, and its "match" attribute has the same value than the name of the XML element, we return it */
		if ( currentElement != NULL &&
			currentElement->getName() == "template"  &&
			currentElement->GetAttributeValue("match") == xmlElementName ){
				
				return *currentElement;
		}
	}
	return NULL;
}
