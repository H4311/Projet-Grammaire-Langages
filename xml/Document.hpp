# ifndef __DOCUMENT_H__
# define __DOCUMENT_H__

# include "ProcessingInstruction.hpp"
# include "Content.hpp"

# include <string>
using namespace std;

namespace xml {

class Document 
{
	private:
		string doctype;
		ProcessingInstruction *xmlProlog;
		Content *root;

		// Copy ctr and affectation are forbidden
		Document(Document& copied);
		Document& operator=(Document& affected);

	public:
		// Gettors and accessors
		void setDoctype(string _d) { doctype = _d; }
		void setXmlProlog(ProcessingInstruction *_xml) { xmlProlog = _xml; }
		void setRoot(Content* _root) { root = _root; }

		~Document();
		Document() : doctype(""), xmlProlog(0), root(0) { /* empty */ }

		ostream& toString(ostream& stream);
};

}

ostream& operator<< (ostream& stream, xml::Document& doc);

# endif
