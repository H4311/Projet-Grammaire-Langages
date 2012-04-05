#ifndef DTD_ATTRIBUTE_H
#define DTD_ATTRIBUTE

#include<string>
#include<list>
#include<iostream>

namespace dtd {
	class AttDef;

	class Attribute {
		public:
			Attribute(std::string _name = "", std::list<std::string> _attDefs = NULL);
			std::ostream& put(std::ostream& out);

		protected:
			std::string name;
			std::list<std::string> attDefs;
	};
}

#endif
