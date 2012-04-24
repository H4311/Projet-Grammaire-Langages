# ifndef __DOCUMENT_H__
# define __DOCUMENT_H__

# include "ProcessingInstruction.hpp"
# include "Content.hpp"
# include "Comment.hpp"

# include <string>
using namespace std;

namespace xml {

class Document 
{
	private:
		string rootName;
		string doctype;

		ProcessingInstruction *xmlProlog;
		Content *root;
		list<Comment*> comments;

		// Copy ctr and affectation are forbidden
		Document(Document& copied);
		Document& operator=(Document& affected);

	public:
		// Gettors and mutators 
		void setDoctype(Doctype * _d) { doctype = _d->first; rootName = _d->second; delete _d;}
		void setXmlProlog(ProcessingInstruction *_xml) { xmlProlog = _xml; }
		void setRoot(Content* _root) { root = _root; }
		void setComments(list<Comment*> * _c) { comments = *_c; delete _c; }

		~Document();
		Document() : doctype(""), xmlProlog(0), root(0) { /* empty */ }

		ostream& toString(ostream& stream);
};

}

ostream& operator<< (ostream& stream, xml::Document& doc);

# endif
