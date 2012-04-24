#ifndef DTD_CONTENTSPEC_H
#define DTD_CONTENTSPEC_H

#include<string>
#include<iostream>

namespace dtd {
	class ContentSpec {
		public:
			virtual ~ContentSpec();
			virtual std::ostream& put(std::ostream& out) = 0;
			virtual std::string getRegex() = 0;
	};
}

std::ostream& operator<<(std::ostream& out, dtd::ContentSpec* c);

#endif
