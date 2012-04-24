#include "ContentSpec.hpp"

std::ostream& operator<<(std::ostream& out, dtd::ContentSpec* c) {
	return c->put(out);
}

namespace dtd {

	// ------------------------------------------------------ Class ContentSpec
	
	ContentSpec::~ContentSpec() {}

}
