#include "Attribute.hpp"

std::ostream& operator<<(std::ostream& out, dtd::Attribute* a) {
	return a->put(out);
}

std::ostream& operator<<(std::ostream& out, dtd::AttDef* d) {
	return d->put(out);
}

namespace dtd {

	std::ostream& Attribute::put(std::ostream& out) {
		std::list<AttDef*>::iterator it;
		out << "<!ATTLIST " << name;
		
		for(it=attDefs.begin(); it != attDefs.end(); it++) {
			out << "\n" << *it;
		}
		
		out << ">";
	}
	
	std::ostream& AttDef::put(std::ostream& out) {
		out << name << " CDATA #IMPLIED";
	}
}
