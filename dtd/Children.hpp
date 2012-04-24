#ifndef DTD_CHILDREN_H
#define DTD_CHILDREN_H

#include<string>
#include<iostream>

#include "ContentSpec.hpp"

namespace dtd {
	class Children : public ContentSpec {
		public:
			Children(char _card = 0);
			virtual ~Children();
			virtual std::ostream& put(std::ostream& out) = 0;
			virtual std::string getRegex() = 0;
		
		protected:
			char card;
	};
}

#endif
