#ifndef DTD_ATTRIBUTE_H
#define DTD_ATTRIBUTE_H

#include<string>
#include<list>
#include<iostream>

#include "Document.hpp"

namespace dtd {
	class Attribute {
		public:
			Attribute(std::string _name = "",
				std::list<std::string> _type = NULL,
				std::string _defaultDecl = "",
				std::string _attValue = "");
			virtual ~Attribute();
			virtual std::ostream& put(std::ostream& out);

		protected:
			std::string name;
			std::list<std::string> type;
			std::string defaultDecl;
			std::string attValue;
	};
}

std::ostream& operator<<(std::ostream& out, dtd::Attribute* a);

#endif
