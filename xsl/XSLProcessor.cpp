# include <iostream>

# include "XSLProcessor.hpp"
# include "xml_processor.h"

using namespace std;

xsl::XSLProcessor::XSLProcessor() : xslDoc() { /* empty */ }

void xsl::XSLProcessor::setXslDTDFileName(string name) {
	xslDTDFileName = name;
}


bool xsl::XSLProcessor::processXslFile(string xslFileName) {
	
	delete *xsldoc;
	xsldoc = null;
	
	// --- Analyse the syntax of the XSL file, and of the XSL DTD file. If OK, continue.
	/** TO DO */
	Document* xslDTDdoc;
	
	// --- Analyse the syntax of the HTML DTD file. The link to this DTD can be found into the attribute xmlns:xsl of the element xsl:stylesheet.
	/** TO DO */
	Element* rootXSLDTD = dynamic_cast<Element*>(xslDTDdoc->getRoot());
	if (rootXSLDTD == NULL) {
		return false; // <Error> Invalid or empty XSL DTD document.
	}
	
	// --------- Finding the path to the HTML DTD, contained by the attribut "xmlns:xsl" of the element "xsl:stylesheet" :
	Element* rootXSL = dynamic_cast<Element*>(xslDoc->getRoot());
	if (rootXSL == NULL) {
		return false; // <Error> Invalid or empty XSL document.
	}
	
	list<Content*>::iterator itelementXSL = rootXSL->getChildren()->begin();
	while  ( (itelementXSL != rootXSL->getChilds()->end())  && (itelementXSL->getName() != "xsl:stylesheet") ) { itelementXSL++; }
	if (itelementXSL == rootXSL->getChilds()->end()) {
		return false; // <Error> Unfound elementcontaining the path to HTML DTD file.
	}
	
	Element* elementStylesheet = dynamic_cast<Element*>(&(*itelementXSL));
	if (elementStylesheet == NULL) {
		return false; // <Error> Invalid "xsl:stylecheet" element.
	}	
	
	Attribut attrXMLNS = elementStylesheet->FindAttribute("xmlns:xsl");
	if (attrXMLNS == NULL) {
		return false; // <Error> Unfound "xmlns:xsl" attribute.
	}		
	
	// --------- Opening, validating ant getting the structure of the HTML DTD file :
	Document * htmlDTDdoc;
	/** TO DO : Document * htmlDTDdoc = DTDValidator.parse(attrXMLNS.second); */
	if (htmlDTDdoc == NULL) {
		return false; // <Error> Invalid or unfound HTML DTD file.
	}
	
	// --- Fusion the XSL DTD and the HTML DTD.
	list<Content*> xslDTDelements = rootXSLDTD->getChildren();
	for( list<Content*>::const_iterator it = htmlDTDdoc->getRoot()->getChildren().begin(),  it != htmlDTDdoc->getRoot()->getChildren().end(); it++) {
		xslDTDelements.push_back(*it);
	}
	rootXSLDTD->SetChildren(xslDTDelements);
	
	return true; /** TO DO : return DTDValidator.validate(xslDoc, xslDTDdoc); */) // if false : <Error> Invalid XSL file : doesn't respect the given DTD.
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
	//cout << *document << "\n" << endl;
	
	//TODO: Verifying its semantic correctness
	
	//
	list<Content*> contentsXsl = xslDoc->getChildren();
	list<Content*> contentsXml = xmlDoc->getChildren();
	list<Content*>::iterator itXml = contentsXsl->begin();
	
	for(list<Content*>::iterator itXsl = contentsXsl->begin();
			itXsl != contentsXsl->end();
			itXsl++)
	{
		if( itXsl.getName() == "template" ){
			AttList attXsl = itXsl.getAttributes();
			
			if( ){
				
			}
			
		}
		
	}
	
	/** TO DO :
	 * - Load the XML file
	 * - Analyse the syntax of the XML file & verify its semantic correctness
	 * - Save the file structure into xmlDoc
	 * - For each tp xsl:template element into  xslDoc, do : (§)
	 *		- name <- tp["match"];
			- For each el XML element having its name == name
				- For each hel HTML element of tp
					- if (hel.name == "apply-template"), then apply recursively the process since the symbol §
					- htmlDoc.insert(content);
	 */
	
	
	
	return true;
}

