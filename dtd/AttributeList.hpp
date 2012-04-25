#ifndef DTD_ATTRIBUTELIST_H
#define DTD_ATTRIBUTELIST_H

#include<string>
#include<list>
#include<iostream>

#include "Document.hpp"

namespace dtd {
	class AttributeList : public Declaration {
		public:
			AttributeList(std::string _name = "", std::list<Attribute> _attDefs = NULL);
			virtual ~AttributeList();
			virtual std::ostream& put(std::ostream& out);

		protected:
			std::string name;
			std::list<Attribute> attDefs;
	};
}

#endif
