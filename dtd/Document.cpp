
#include "Document.hpp"

std::ostream& operator<<(std::ostream& out, dtd::Document* d) {
	return d->put(out);
}

namespace dtd {

	// --------------------------------------------------------- Class Document

	Document::Document(std::list<Declaration*> _declarations)
		: declarations(_declarations) {}
	
	Document::~Document() {
		std::list<Declaration*>::iterator it;
		for(it=declarations.begin(); it!=declarations.end(); it++) {
			delete *it;
		}
	}
	
	std::ostream& Document::put(std::ostream& out) {
		std::list<Declaration*>::iterator it;
		for(it=declarations.begin(); it!=declarations.end(); it++) {
			out << *it << std::endl;
		}
		return out;
	}
	
	std::list<Declaration*> Document::getDeclarations() {
		return declarations;
	}

}
