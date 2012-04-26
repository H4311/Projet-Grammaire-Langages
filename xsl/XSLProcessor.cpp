#include <iostream>

/**
* @file XSLProcessor.cpp
* @brief Implementation - XSL processing functions
* 
* Contains the implementation of the XSL Processor class, and thus the functions to validate a XSL stylesheet and parse XML files into HTML using it.
* 
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
	dtd::Document* newXslDTDdoc = dtd::parseDTD(name);
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
	xml::Document* newXsldoc = xml::parseXML(name);
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
	
	string attrXMLNS = elStylesheet->GetAttributeValue("xmlns:xsl");
	if (attrXMLNS.empty()) {
		return false; // <Error> Unfound "xmlns:xsl" attribute.
	}		
	
	// --------- Opening, validating ant getting the structure of the HTML DTD file :
	dtd::Document * htmlDTDdoc = dtd::parseDTD(name);
	if (htmlDTDdoc == NULL) {
		return false; // <Error> Syntax Error - Invalid, empty or unfound XSL document.
	}	

	// --- Fusion the XSL DTD and the HTML DTD into a new DTD (only valid used for this XSL) : we copy the XSL DTD into the HTML one.
	xml::Element* rootXSLDTD = dynamic_cast<xml::Element*>(newXslDTDdoc->getRoot());
	list<xml::Content*> xslDTDelements =  rootHTMLDTD->getChildren();
	for( list<xml::Content*>::const_iterator it = rootXSLDTD->getChildren().begin();  it != rootXSLDTD->getChildren().end(); it++) {
		xslDTDelements.push_back(*it);
	}
	rootHTMLDTD->SetChildren(&xslDTDelements);
	
	// Semantic analysis :
	bool semanticCorrectness = true;
	/** @todo Analyse the semantic correctness of the XSL file :  semanticCorrectness = DTDValidator.validate(xslDoc, xslDTDdoc); */
	if (!semanticCorrectness) {
		return false; // <Error> Invalid XSL file : doesn't respect the given DTD.
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
		return false; // <Error> No XSL. Please process a XSL stylesheet first.
	}

	xml::Document* xmlDoc = xml::parseXML(name);
	if (xmlDoc == NULL) {
		return false; // <Error> Syntax Error - Invalid, empty or unfound XML document.
	}
	
	xml::Element* xslNode = findTemplate(xmlDoc->getRoot());
	list<xml::Content*> listHTMLElements = generateHTML(xslNode, xmlDoc->getRoot());
	xml::Element* htmlRoot;
	if (listHTMLElements.length() > 1) { // No generated rooot, so we add one :
		htmlRoot = new Element();
		htmlRoot->setName("null");
		htmlRoot->setChildren(listHTMLElements);
	}
	else if (listHTMLElements.length() == 1) {
		htmlRoot = listHTMLElements[0];
	}
	
	xml::Document* docHTML = new xml::Document();
	docHTML->setRoot(htmlRoot);
	
	return docHTML;
}

list<xml::Element*> xsl::XSLProcessor::generateHtmlElement(xml::Element* xslNode, xml::Content* xmlNode) {

	list<xml::Element*> htmlNode;

	if (xslNode != NULL) // We apply this template :
		for(list<xml::Content*>::const_iterator itXSL = xslNode->getChildren()->begin(); itXSL != xslNode->getChildren()->end(); itXSL++) {
			xml::Content* htmlChild;
			xml::Element* itXSLEle = dynamic_cast<xml::Element*>(*itXSL);
			if (itXSLEle != NULL) { // If it's an element 
				htmlChild = new xml::Element();
				if (itXSLEle->getNamespace() != "xsl") { // If it's HTML :
					htmlChild->setName(itXSLEle->getName());
					htmlChild->setAttributes(itXSLEle->getAttributes());
					htmlChild->appendChild(generateHTML(itXSLEle, xmlNode));
				}
				else if (itXSLEle->getName() == "apply-templates") {
					// For each child of the current XML node, we try to apply another template :
					for(list<xml::Content*>::const_iterator itXML = xmlNode->getChildren()->begin(); itXML != xmlNode->getChildren()->end(); itXML++) {
						xml::Element* xslNodeChild = findTemplate(*itXML);
						generateHTML(xslNodeChild, *itXML); // recursivity
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
					htmlChild->setName(itXSLEmp->getName());
					htmlChild->setAttributes(itXSLEmp->getAttributes());
				}
				else {
					xml::EmptyElement* itXSLDat = dynamic_cast<xml::Data*>(*itXSL);
					if (itXSLDat != NULL) {  // If it's an empty element 
						htmlChild = new xml::Data();
						htmlChild->setData(itXSLDat->getData());
					}
				}
			}

			htmlNode.push_back(htmlChild);
		}
	}
	else { // If we didn't find a template, we only past the inner data, try to apply other templates to the children
		for(list<xml::Content*>::const_iterator itXML = xmlNode->getChildren()->begin(); itXML != xmlNode->getChildren()->end(); itXML++) {
			xml::Data* itXMLDat = dynamic_cast<xml::Data*>(*itXML);
			if (itXMLDat != NULL) {  // If it's data, we past it into the html doc :
				htmlNode.push_back(itXMLDat);
			}
			else {
				xml::Element* itXMLEle = dynamic_cast<xml::Element*>(*itXML);
				if (itXMLEle != NULL) {  // If it's an element, we process it :
					xml::Element* xslNodeChild = findTemplate(itXMLEle);
					generateHTML(xslNodeChild, itXMLEle); // recursivity
				}
			}

		}
	}

	return htmlNode;
}



/** @todo ALGO POTENTIELLEMENT VALIDE ET TOTAL, à implémenter et tester (NE PAS SUPPRIMER -> servira pour le CR Algo)
Document* generateHtmlFile(string xmlFileName)
DEBUT
	xmlDoc = parseXML(xmlFileName);
	Si xmlDoc nul
		return NULL;
	FinSi
	
	Element* XSLnode = findTemplate(xmlDoc->getRoot());
	Liste<Element*> listElementsHTML = generateHTML(XSLnodeChild, xmlDoc->getRoot());
	Element* racineHTML;
	Si listElementsHTML.length() > 1 // XSL n'ayant pas généré de racine, donc on en ajoute une
		racineHTML = new Element();
		racineHTML->setName("null");
		racineHTML->setChildren(listElementsHTML);
	SinonSi listElementsHTML.length() = 1
		racineHTML = listElementsHTML[0];
	FinSi
	
	Document* docHTML = newDocument();
	docHTML->setRoot(racineHTML);
	
	return docHTML;
FIN

Liste<Element*> generateHTMLElement(Element* XSLnode, Content* XMLnode)
DEBUT
	Liste<Element*> HTMLnode;
	Si XSLnode non-nul
		Pour chaque enfant de XSLnode
			Content* htmlChild = new Content();
			Si xslEl EmptyElement
				htmlChild->setName(xslEl->getName());
				htmlChild->setAttributes(xslEl->getAttributes());
			SinonSi xslEl Data
				htmlChild->setData(xslEl->getData());
			SinonSi xslEl Element
				Si xslEl est du HTML
					htmlChild->setName(xslEl->getName());
					htmlChild->setAttributes(xslEl->getAttributes());
					htmlChild->appendChild(generateHTML(xslEl, XMLnode);
				SinonSi xslEl apply-templates
					Si XMLnode Element
						Pour chaque enfant de XMLnode
							Element* XSLnodeChild = findTemplate(XMLnodeChild);
							generateHTML(XSLnodeChild, XMLnodeChild);
						FinPour
					FinSi
				FinSi
			FinSi
			HTMLnode.push_back(htmlChild);
		FinPour
	Sinon
		Pour chaque enfant de XMLnode
			Si XMLnodeChild Data // On ajoute sans modifier :
				HTMLnode.push_back(XMLnodeChild);
			SinonSi XMLnodeChild Element
				Element* XSLnodeChild = findTemplate(XMLnodeChild);
				generateHTML(XSLnodeChild, XMLnodeChild);
			FinSi
		FinPour
	FinSi
	return HTMLnode;
FIN
*/

bool xsl::XSLProcessor::generateHtmlFile(string xmlFileName, string htmlOutputFile) {


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
