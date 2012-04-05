
#include "Document.hpp"

std::ostream& operator<<(std::ostream& out, dtd::Document* d) {
	return d->put(out);
}

std::ostream& operator<<(std::ostream& out, dtd::Declaration* d) {
	return d->put(out);
}

namespace dtd {

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
	
	Declaration::~Declaration() {}

}
