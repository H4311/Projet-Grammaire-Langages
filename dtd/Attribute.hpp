#include<string>
#include<list>
#include<iostream>

namespace dtd {
	class AttDef;

	class Attribute {
		public:
			virtual std::ostream& put(std::ostream& out);

		protected:
			std::string name;
			std::list<AttDef*> attDefs;
	};
	
	class AttDef {
		public:
			std::ostream& put(std::ostream& out);

		protected:
			std::string name;
	};
}
