#ifndef DTD_CHILDREN_H
#define DTD_CHILDREN_H

#include<string>
#include<iostream>

#include "ContentSpec.hpp"

namespace dtd {
	class Children : public ContentSpec {
		public:
			Children();
			void SetCard(char _c) { card = _c; }
			virtual ~Children();
			virtual std::ostream& put(std::ostream& out) = 0;
			virtual std::string getRegex() = 0;
		
		protected:
			char card;
	};
}

#endif
