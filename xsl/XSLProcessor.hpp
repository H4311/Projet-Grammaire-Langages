# ifndef __XSLPROCESSOR_H__
# define __XSLPROCESSOR_H__

/**
 * @file XSLProcessor.hpp
 * @brief Definition - XSL processing functions
 * 
 * Contains the functions to validate a XSL stylesheet and parse XML files into HTML using it.
 * 
 * @author Daniel BAUDRY & Benjamin Bill PLANCHE (ALdream)
 */

# include <string>

# include "xml/Content.hpp"
# include "xml/Document.hpp"
# include "xml/Element.hpp"

# include "dtd/Document.hpp"


using namespace std;

/**
 * @namespace xsl
 * Contains all classes and elements processing XSL
 */
namespace xsl {
	
	/**
	 * @class XSLProcessor
	 * @brief XSL processing functions
	 * 
	 * Object which contains the functions to validate a XSL stylesheet and parse XML files into HTML using it.
	 */
	class XSLProcessor 
	{
		private:
			xml::Document* xslDoc; /** < Structure of the processed XSL file, which will be used to process the XML files. */
			
			dtd::Document* xslDTDdoc; /** < Structure of the processed XSL DTD file, which will be used to validate the XSL files. */

		public:
			// Getters and setters
			
			/**
			 * @brief Setter - XSL DTD
			 * 
			 * Set the XSL DTD attribute, with an already-processed (and validated) DTD structure.
			 * 
			 * @param newXslDTDdoc New DTD structure.
			 */
			void setXslDTD(dtd::Document* newXslDTDdoc);			

			/**
			 * @brief XSL Validator
			 * 
			 * Validate and process the given XSL file using the previously processed DTD file, and set the XSL attribute.
			 * If the given document is invalid, or the HTML DTD it uses, the previous one will be kept as attribute.
			 *
			 * @param xslDoc XSL document to evaluate.
			 */
			void processXslFile(xml::Document* xslDoc) throw (string);

			/**
			 * @brief Setter - XML to HTML Processor
			 * 
			 * Generate the HTML document from a XML one using the previously processed XSL file.
			 * 
			 * @author Daniel BAUDRY & Benjamin Bill PLANCHE (ALdream)
			 * @return the structure of the HTML document.
			 * @param xmlDoc Processed XML document.
			 */
			xml::Document* generateHtmlFile(xml::Document* xmlDoc);

			~XSLProcessor();
			XSLProcessor();
		private :

			/**
			 * @brief Recursive XML to HTML Processor
			 * 
			 * Recursively apply the XSL templates to the XML elements, generating the HTML document.
			 * If no template is given, it only pasts the inner data and tries to apply other templates to the elements children.
			 *
			 * @return the list of generated HTML elements
			 * @param xslNode Template to apply.
			 * @param xmlNode XML element to process.
			 * @param htmlNode HTML element which is being generated (used for the XSL "attribute" element).
			 */			
			list<xml::Content*> generateHtmlElement(xml::Element* xslNode, xml::Content* xmlNode, xml::Element* htmlNode);

			/**
			 * @brief XSL Template Finder
			 * 
			 * Find the template which has the same value for the "match" attribute than the given element's name.
			 *
			 * @return the first XSL template element if found, or NULL.
			 * @param xmlElementName Name of the element for which we want to find a template.
			 */
			xml::Element* findTemplate( string xmlElementName );

	};

}

# endif
