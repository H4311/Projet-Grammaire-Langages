# include <iostream>

# include "XSLProcessor.hpp"
# include "xml/xml_processor.h"

using namespace std;

xsl::XSLProcessor::XSLProcessor() : xslDoc() { /* empty */ }

void xsl::XSLProcessor::setXslDTDFileName(string name) {
	xslDTDFileName = name;
}


bool xsl::XSLProcessor::processXslFile(string xslFileName) {
	/** TO DO :
	 * - Analyse the syntax of the XSL file, and of the XSL DTD file. If OK, continue.
	 * - Verify the semantic correctness of the XSL elements, using the XSL DTD
	 * - Analyse the syntax of the HTML DTD file. The link to this DTD can be found into the attribute xmlns:xsl of the element xsl:stylesheet.
	 * - Verify the semantic correctness of the HTML elements, using the HTML DTD
	 * - Save the file structure into xslDoc and return the boolean.
	 */
	 
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
	 * - For each tp xsl:template element into  xslDoc, do : (�)
	 *		- name <- tp["match"];
			- For each el XML element having its name == name
				- For each hel HTML element of tp
					- if (hel.name == "apply-template"), then apply recursively the process since the symbol �
					- htmlDoc.insert(content);
	 */
	
	
	
	return true;
}

