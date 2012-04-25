# ifndef __XSLPROCESSOR_H__
# define __XSLPROCESSOR_H__

/**
 * @file XSLProcessor.hpp
 * @brief Definition - XSL processing functions
 * Contains the functions to validate a XSL stylesheet and parse XML files into HTML using it.
 * @author Daniel BAUDRY & Benjamin Bill PLANCHE (ALdream)
 */

# include "Content.hpp"
# include <string>
#include "Document.hpp"

# include <string>
using namespace std;

/**
 * @namespace xsl
 * Contains all classes and elements processing XSL
 */
namespace xsl {
	
	/**
	 * @class XSLProcessor
	 * @brief XSL processing functions
	 * Object which contains the functions to validate a XSL stylesheet and parse XML files into HTML using it.
	 */
	class XSLProcessor 
	{
		private:
			xml::Document* xslDoc; /** < Structure of the processed XSL file, which will be used to process the XML files. */
			
			xml::Document* xslDTDdoc; /** < Structure of the processed XSL DTD file, which will be used to validate the XSL files. */

		public:
			// Getters and setters
			
			/**
			 * @brief Setter - XSL DTD
			 * Validate and process the given DTD file, and set the XSL DTD attribute.
			 * If the given DTD is invalid, the previous one will be kept as attribute.
			 * @author Benjamin Bill PLANCHE (ALdream)
			 * @param name Path to the XSL DTD to use.
			 * @return true if the change has been made.
			 */
			bool processXslDTDFile(string name);			

			/**
			 * @brief XSL Validator
			 * Validate and process the given XSL file using the previously processed DTD file, and set the XSL attribute.
			 * If the given document is invalid, or the HTML DTD it uses, the previous one will be kept as attribute.
			 * @return true if the XSL is conformed to the given XSL and HTML DTD, and save the document structure for the next HTML generation.
			 * @param xslFileName Path to the xsl file to evaluate.
			 */
			bool processXslFile(string xslFileName);

			/**
			 * @brief Setter - XML to HTML Processor
			 * Validate the given XML file and generate the HTML document using the previously processed XSL file.
			 * @author Daniel BAUDRY & Benjamin Bill PLANCHE (ALdream)
			 * @return true if the XML is conformed, and save the HTML document to the given place.
			 * @param xmlFileName Path to the xml file to evaluate.
			 * @param htmlOutputFile Path to the file which will contain the HTML file.
			 */
			bool generateHtmlFile(string xmlFileName, string htmlOutputFile);

			~XSLProcessor();
			XSLProcessor();

	};

}

# endif
