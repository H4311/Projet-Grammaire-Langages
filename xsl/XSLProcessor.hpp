# ifndef __XSLPROCESSOR_H__
# define __XSLPROCESSOR_H__

#include "Document.hpp"

# include <string>
using namespace std;

namespace xsl {

	class XSLProcessor 
	{
		private:
			xml::Document* xslDoc; // Structure of the processed XSL file

			string xslDTDFileName; // Name of the XSL DTD file to use to validate the XSL docs.

		public:
			// Getters and accessors
			void setXslDTDFileName(string name);			

			/**
			 *	Validate and process the given XSL file.
			 *	Return true if the XSL is conformed to the given XSL and HTML DTD, and save the document structure for the next HTML generation.
			 */
			bool processXslFile(string xslFileName);

			/**
			 *	Validate the given XML file and generate the HTML document using the previously processed XSL file.
			 *	Return true if the XML is conformed, and save the HTML document to the given place.
			 */
			bool generateHtmlFile(string xmlFileName, string htmlOutputFile);

			~XSLProcessor();
			XSLProcessor();

	};

}

# endif
