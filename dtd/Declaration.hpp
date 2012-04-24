#ifndef DTD_DECLARATION_H
#define DTD_DECLARATION_H

#include<iostream>

namespace dtd {
	class Declaration {
		public:
			virtual ~Declaration();
			virtual std::ostream& put(std::ostream& out) = 0;
	};
}

std::ostream& operator<<(std::ostream& out, dtd::Declaration* d);

#endif
