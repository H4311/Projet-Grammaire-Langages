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
			xml::Document* xslDoc; /** < Structure of the processed XSL file */

			string xslDTDFileName; /** < Name of the XSL DTD file to use to validate the XSL docs. */

		public:
			// Getters and setters
			
			/**
			 * @brief Setter - XSL DTD file path
			 * Sets the XSL DTD file path attribute
			 * @author Benjamin Bill PLANCHE (ALdream)
			 * @param name New path.
			 */
			void setXslDTDFileName(string name);			

			/**
			 * @brief Setter - XSL Validator
			 * Validate and process the given XSL file.
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
