
#include "Declaration.hpp"

std::ostream& operator<<(std::ostream& out, dtd::Declaration* d) {
	return d->put(out);
}

namespace dtd {

	// ------------------------------------------------------ Class Declaration
	
	Declaration::~Declaration() {}

}
