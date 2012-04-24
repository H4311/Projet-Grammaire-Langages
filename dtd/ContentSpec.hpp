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
	
	class Any : public ContentSpec {
		public:
			virtual ~Any();
			virtual std::ostream& put(std::ostream& out);
			virtual std::string getRegex();
	};
	
	class Empty : public ContentSpec {
		public:
			virtual ~Empty();
			virtual std::ostream& put(std::ostream& out);
			virtual std::string getRegex();
	};
}

std::ostream& operator<<(std::ostream& out, dtd::ContentSpec* c);

#endif
