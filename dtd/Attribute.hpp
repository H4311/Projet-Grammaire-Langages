#ifndef DTD_ATTRIBUTE_H
#define DTD_ATTRIBUTE_H

#include<string>
#include<list>
#include<iostream>

#include "Document.hpp"

namespace dtd {
	class AttDef;

	class Attribute : public Declaration {
		public:
			Attribute(std::string _name = "", std::list<std::string> _attDefs = NULL);
			virtual std::ostream& put(std::ostream& out);

		protected:
			std::string name;
			std::list<std::string> attDefs;
	};
}

#endif
