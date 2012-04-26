#ifndef DTD_NAME_H
#define DTD_NAME_H

#include<string>
#include<list>
#include<iostream>

#include "Children.hpp"

namespace dtd {
	class Name : public Children {
		public:
			Name(std::string _name = "");
			virtual ~Name();
			virtual std::ostream& put(std::ostream& out);
			virtual std::string getRegex();
		
		protected:
			std::string name;
	};
}

#endif
