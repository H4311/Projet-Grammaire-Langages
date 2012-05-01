
#include "Document.hpp"

std::ostream& operator<<(std::ostream& out, dtd::Document* d) {
	return d->put(out);
}

namespace dtd {

	// --------------------------------------------------------- Class Document

	Document::Document(std::list<Declaration*>* _declarations)
		: declarations(_declarations) {}
	
	Document::~Document() {
		if (declarations == NULL)
			return;

		std::list<Declaration*>::iterator it;
		for(it=declarations->begin(); it!=declarations->end(); ++it) {
			if (*it != NULL)
			{
				delete *it;
				*it = NULL;
			}
		}
		delete declarations;
	}
	
	std::ostream& Document::put(std::ostream& out) {
		std::list<Declaration*>::iterator it;
		for(it=declarations->begin(); it!=declarations->end(); ++it) {
			out << *it << std::endl;
		}
		return out;
	}
	
	std::list<Declaration*>* Document::getDeclarations() {
		return declarations;
	}

	void Document::setDeclarations(std::list<Declaration*>* dec) {
		delete declarations;
		declarations = dec;
	}
}
