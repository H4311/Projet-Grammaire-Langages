#ifndef DTD_ELEMENT_H
#define DTD_ELEMENT_H

#include<string>
#include<list>
#include<iostream>

#include "Document.hpp"
#include "ContentSpec.hpp"

namespace dtd {
	class Element : public Declaration {
		public:
			Element(std::string _name = "", ContentSpec* _content = NULL);
			virtual ~Element();
			virtual std::ostream& put(std::ostream& out);
			virtual std::string getRegex();
			std::string getName();

		protected:
			std::string name;
			ContentSpec* content;
	};
}

#endif
