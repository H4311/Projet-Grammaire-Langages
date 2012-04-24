# include <iostream>

# include "XSLProcessor.hpp"

using namespace std;

xsl::XSLProcessor::XSLProcessor() : xslDoc() { /* empty */ }

void xsl::XSLProcessor::setXslDTDFileName(string name) {
	xslDTDFileName = name;
}


bool xsl::XSLProcessor::processXslFile(string xslFileName) {
	/** TO DO :
	 * - Analyse the syntax of the XSL file, and of the XSL DTD file. If OK, continue.
	 * - Analyse the syntax of the HTML DTD file. The link to this DTD can be found into the attribute xmlns:xsl of the element xsl:stylesheet.
	 * - Fusion the XSL DTD and the HTML DTD.
	 * - Verify the semantic correctness of the XSL file, using the fusioned DTD
	 * - Save the file structure into xslDoc and return the boolean.
	 */
	
	// --- Analyse the syntax of the XSL file, and of the XSL DTD file. If OK, continue.
	Document* xslDTDdoc;
	// --- Analyse the syntax of the HTML DTD file. The link to this DTD can be found into the attribute xmlns:xsl of the element xsl:stylesheet.
	
	// --------- Finding the path to the HTML DTD, contained by the attribut "xmlns:xsl" of the element "xsl:stylesheet" :
	Element* rootXSL = dynamic_cast<Element*>(xslDoc->getRoot());
	if (rootXSL == null) {
		return false; // <Error> Invalid or empty XSL document.
	}
	
	list<Content*>::iterator itelementXSL = rootXSL->getChilds()->begin();
	while  ( (itelementXSL != rootXSL->getChilds()->end())  && (itelementXSL->getName() != "xsl:stylesheet") ) { itelementXSL++; }
	if (itelementXSL == rootXSL->getChilds()->end()) {
		return false; // <Error> Unfound elementcontaining the path to HTML DTD file.
	}
	
	Element* elementStylesheet = dynamic_cast<Element*>(&(*itelementXSL));
	if (elementStylesheet == null) {
		return false; // <Error> Invalid "xsl:stylecheet" element.
	}	
	
	Attribut attrXMLNS = elementStylesheet->FindAttribute("xmlns:xsl");
	if (attrXMLNS == null) {
		return false; // <Error> Unfound "xmlns:xsl" attribute.
	}		
	
	// --------- Opening, validating ant getting the structure of the HTML DTD file :
	Document * htmlDTDdoc; // TO DO : Document * htmlDTDdoc = DTDValidator.validate(attrXMLNS.second);
	if (htmlDTDdoc == null) {
		return false; // <Error> Invalid or unfound HTML DTD file.
	}
	
	// --- Fusion the XSL DTD and the HTML DTD.
	xslDTDdoc.
	
	
	
	return true;
}

bool xsl::XSLProcessor::generateHtmlFile(string xmlFileName, string htmlOutputFile) {

	// Checking if an valid XSL file as already been processed :
	if (xslDoc == null) { return false; }

	Document xmlDoc;
	Document htmlDoc;
	
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

