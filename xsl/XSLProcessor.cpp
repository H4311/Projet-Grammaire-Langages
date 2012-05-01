/**
* @file XSLProcessor.cpp
* @brief Implementation - XSL processing functions
* 
* Contains the implementation of the XSL Processor class, and thus the functions to validate a XSL stylesheet and parse XML files into HTML using it.
* 
* @author Daniel BAUDRY & Benjamin Bill PLANCHE (Aldream)
*/

#include "XSLProcessor.hpp"

#include "../xml/basics.h"
#include "../xml/xml_processor.h"
#include "../xml/Element.hpp"
#include "../xml/Data.hpp"
#include "../xml/EmptyElement.hpp"
#include "../xml/Document.hpp"

#include "../dtd/Document.hpp"
#include "../dtd/Declaration.hpp"
#include "../dtd/dtd.h"

#include "../validation/Validateur.hpp"

#include "../xpath/XPath.hpp"
 
using namespace std;

const string xsl::XSLProcessor::ERROR_NO_DTD("No DTD. Please process a XSL DTD first.");
const string xsl::XSLProcessor::ERROR_NO_XSL("No XSL. Please process a XSL stylesheet first.");
const string xsl::XSLProcessor::ERROR_INVALID_XSL("Invalid or empty XSL document.");
const string xsl::XSLProcessor::ERROR_NO_STYLESHEET("Unfound element containing the path to HTML DTD file.");
const string xsl::XSLProcessor::ERROR_NO_XMLNS("Unfound \"xmlns:xsl\" attribute.");
const string xsl::XSLProcessor::ERROR_INVALID_HTML_DTD("Syntax Error - Invalid, empty or unfound HTML DTD document.");
const string xsl::XSLProcessor::ERROR_INVALID_XSL_SEMANTIC("Semantic Error - Invalid XSL file : doesn't respect the given DTD.");

xsl::XSLProcessor::XSLProcessor() {
	xslDTDdoc = NULL;
	xslDoc = NULL;

}

xsl::XSLProcessor::~XSLProcessor() {
	if(xslDTDdoc)
	{
		delete xslDTDdoc;
		xslDTDdoc = NULL;
	}
}

void xsl::XSLProcessor::setXslDTD(dtd::Document* newXslDTDdoc) {
	delete xslDTDdoc;
	xslDTDdoc = newXslDTDdoc;
}


void xsl::XSLProcessor::processXslFile(xml::Document* newXslDoc) throw (string) {

	// --- Checking if a DTD has been processed
	if (xslDTDdoc == NULL) {
		throw(ERROR_NO_DTD);
	}

	// --- Analyse the syntax of the HTML DTD file. The link to this DTD can be found into the attribute xmlns:xsl of the element xsl:stylesheet of the XSL.
	
	// --------- Finding the path to the HTML DTD, contained by the attribut "xmlns:xsl" of the element "xsl:stylesheet" :
	xml::Element* rootXSL = dynamic_cast<xml::Element*>(newXslDoc->getRoot());
	if (rootXSL == NULL) {
		throw(ERROR_INVALID_XSL);
	}
	
	string attrXMLNS = rootXSL->getAttributeValue("xmlns:xsl");
	if (attrXMLNS.empty()) {
		throw(ERROR_NO_XMLNS);
	}	
	
	// --------- Building a full path, by prepending the path to the folder of the XSL file to the path to the HTML DTD file (without this, if the program is running in a different folder than the XSL file, it won't be able to find the HTML DTD with the relative path of the XSL) 
	string xslPath = newXslDoc->getFilePath();
	string fullHtmlDtdPath = attrXMLNS;
	if (attrXMLNS[0] != '/') {
		string xslFolder = xslPath.substr(0, xslPath.find_last_of("/\\"));
		fullHtmlDtdPath = xslFolder + "/" + attrXMLNS;
	}
	cout << fullHtmlDtdPath;	
	// --------- Opening, validating ant getting the structure of the HTML DTD file :
	dtd::Document * htmlDTDdoc = parseDTD(fullHtmlDtdPath.c_str());
	if (htmlDTDdoc == NULL) {
		throw(ERROR_INVALID_HTML_DTD);
	}	

	// --- Fusion the XSL DTD and the HTML DTD into a new DTD (only valid used for this XSL) : we copy the XSL DTD into the HTML one.
	list<dtd::Declaration*>* htmlDeclarationsCopy =  new list<dtd::Declaration*>(*htmlDTDdoc->getDeclarations()); // We keep a copy of the original HTML declarations list.
	list<dtd::Declaration*>* htmlDeclarations =  htmlDTDdoc->getDeclarations();
	list<dtd::Declaration*>* xslDeclarations =  xslDTDdoc->getDeclarations();
	for( list<dtd::Declaration*>::iterator it = xslDeclarations->begin();  it != xslDeclarations->end(); ++it) {
		htmlDeclarations->push_back(*it);
	}

	// --- Semantic analysis :
	if (!Validateur::validationDocument(*htmlDTDdoc, *newXslDoc)) {
		htmlDTDdoc->setDeclarations(htmlDeclarationsCopy);
		delete htmlDTDdoc;
		throw(ERROR_INVALID_XSL_SEMANTIC);
	}

	// --- Everything is OK with the new XSL : we delete the ancient one and replace by the new.
	delete xslDoc;
	xslDoc = newXslDoc;
	
	htmlDTDdoc->setDeclarations(htmlDeclarationsCopy); // We restore the original list, so when deleting the HTML DTD and its list of declarations, we won't destroy the XSL declarations (the XSL DTD can be reused).
	delete htmlDTDdoc;

	return;
}


xml::Document* xsl::XSLProcessor::generateHtmlFile(xml::Document* xmlDoc) {
	// --- Checking if a XSL has been processed
	if (xslDoc == NULL) {
		throw(ERROR_NO_XSL);
	}
	xml::EmptyElement* rootXML = dynamic_cast<xml::EmptyElement*>(xmlDoc->getRoot());
	xml::Element* xslNode;
	if (rootXML != NULL) { // If it's an empty element or element, we try to find a template to apply :
		xslNode = findTemplate(rootXML->getName());
	}
	list<xml::Content*> listHTMLElements = generateHtmlElement(xslNode, xmlDoc->getRoot(), NULL);
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

list<xml::Content*> xsl::XSLProcessor::generateHtmlElement(xml::Element* xslNode, xml::Content* xmlNode, xml::Element* htmlNode) {

	list<xml::Content*> htmlNodeChildren;

	if (xslNode != NULL) { // We apply this template :
		list<xml::Content*> xslNodeChildren = xslNode->getChildren();
		for(list<xml::Content*>::const_iterator itXSL = xslNodeChildren.begin(); itXSL != xslNodeChildren.end(); itXSL++) {
			xml::Content* htmlChild;
			xml::EmptyElement* itXSLEmp = dynamic_cast<xml::EmptyElement*>(*itXSL);
			if (itXSLEmp != NULL) { // If it's an element 
				if (itXSLEmp->getNamespace() != "xsl") { // If it's HTML :
					xml::Element* itXSLEle = dynamic_cast<xml::Element*>(*itXSL);
					if (itXSLEle == NULL) {  // If it's an empty element 
						htmlChild = new xml::EmptyElement();
						((xml::EmptyElement*)htmlChild)->setName(ElementName(itXSLEmp->getNamespace(), itXSLEmp->getName()));
						((xml::EmptyElement*)htmlChild)->setAttList(itXSLEmp->getAttList());
					}
					else {
						htmlChild = new xml::Element();
						((xml::Element*)htmlChild)->setName(ElementName(itXSLEle->getNamespace(), itXSLEle->getName()));
						((xml::Element*)htmlChild)->setAttList(itXSLEle->getAttList());
						((xml::Element*)htmlChild)->appendChildren(generateHtmlElement(itXSLEle, xmlNode, ((xml::Element*)htmlChild)));
					}
					htmlNodeChildren.push_back(htmlChild);
				}
				else if (itXSLEmp->getName() == "apply-templates") {
					// For each child of the current XML node, we try to apply another template :
					xml::Element* xmlEle = dynamic_cast<xml::Element*>(xmlNode);
					if (xmlEle != NULL) { // If it's an element 
						for(list<xml::Content*>::const_iterator itXML = xmlEle->getChildren().begin(); itXML != xmlEle->getChildren().end(); itXML++) {
							xml::Element* xslNodeChild = NULL;
							xml::EmptyElement* itXMLEmp = dynamic_cast<xml::EmptyElement*>(*itXML);
							if (itXMLEmp != NULL) { // If it's an empty element or element, we try to find a template to apply :
								xslNodeChild = findTemplate(itXMLEmp->getName());
							}
							list<xml::Content*> applyChildren = generateHtmlElement(xslNodeChild, *itXML, ((xml::Element*)htmlChild));
							htmlNodeChildren.splice(htmlNodeChildren.end(), applyChildren); // recursivity
						}
					}
				}
				else if (itXSLEmp->getName() == "value-of") {
					// We'd like to get the value of an XPATH value :
					xml::EmptyElement *elem = dynamic_cast<xml::EmptyElement*>(xmlNode);
					if(elem != NULL) {
						string select = itXSLEmp->getAttributeValue("select");
						string xPathResult = xpath::find(elem, select);
						
						// Create the data content that contains the xpath result
						htmlChild = new xml::Data(xPathResult);
					}
					htmlNodeChildren.push_back(htmlChild);
				}
				else if (itXSLEmp->getName() == "attribute") {
					xml::Element* itXSLEle = dynamic_cast<xml::Element*>(*itXSL);
					if (itXSLEle != NULL) {  // If it's an empty element 
						// Processing the data inside this XSL element :
						list<xml::Content*> contentChildren = generateHtmlElement(itXSLEle, xmlNode, htmlNode);
						// Getting its textual value :
						string data;
						for(list<xml::Content*>::const_iterator itHTML = contentChildren.begin(); itHTML != contentChildren.end(); itHTML++) {
							xml::Data* htmlData = dynamic_cast<xml::Data*>(*itHTML);
							if (htmlData != NULL) {
								data += htmlData->getData();
							}
							delete *itHTML;
						}
						// Adding it as an attribute into the current HTML node :
						htmlNode->addAttribute(Attribut(itXSLEle->getAttributeValue("name"), data));
					}
				}					
			}
			else {
				xml::Data* itXSLDat = dynamic_cast<xml::Data*>(*itXSL);
				if (itXSLDat != NULL) {  // If it's an empty element 
					htmlChild = new xml::Data(itXSLDat->getData());
				}
				htmlNodeChildren.push_back(htmlChild);
			}

			
		}
	}
	else { // If we didn't find a template, we only past the inner data, try to apply other templates to the elements children
		xml::Element* xmlElement = dynamic_cast<xml::Element*>(xmlNode);
		if (xmlElement != NULL) {
			for(list<xml::Content*>::const_iterator itXML = xmlElement->getChildren().begin(); itXML != xmlElement->getChildren().end(); itXML++) {
				xml::Data* itXMLDat = dynamic_cast<xml::Data*>(*itXML);
				if (itXMLDat != NULL) {  // If it's data, we past it into the html doc :
					htmlNodeChildren.push_back(itXMLDat);
				}
				else {
					xml::EmptyElement* itXMLEmp = dynamic_cast<xml::EmptyElement*>(*itXML);
					if (itXMLEmp != NULL) {  // If it's an element (empty or not), we process it :
						xml::Element* xslNodeChild = findTemplate(itXMLEmp->getName());
						list<xml::Content*> contentChildren = generateHtmlElement(xslNodeChild, itXMLEmp, htmlNode); // recursivity
						for(list<xml::Content*>::const_iterator itHTML = contentChildren.begin(); itHTML != contentChildren.end(); itHTML++) {
							htmlNodeChildren.push_back(*itHTML);
						}
					}
				}

			}
		}
	}

	return htmlNodeChildren;
}

xml::Element* xsl::XSLProcessor::findTemplate( string xmlElementName ) {
	
	list<xml::Content*> contentsXsl = ((xml::Element*)(xslDoc->getRoot()))->getChildren();
	
	for(list<xml::Content*>::iterator itXsl = contentsXsl.begin(); itXsl != contentsXsl.end(); itXsl++)
	{
		xml::Element* currentElement = dynamic_cast<xml::Element*>(*itXsl);
		/** If it's a template element, and its "match" attribute has the same value than the name of the XML element, we return it */
		if ( currentElement != NULL &&
			currentElement->getName() == "template"  &&
			currentElement->getAttributeValue("match") == xmlElementName ){
				
				return currentElement;
		}
	}
	return NULL;
}
