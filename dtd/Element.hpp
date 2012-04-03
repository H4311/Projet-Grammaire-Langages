#ifndef DTD_ELEMENT_H
#define DTD_ELEMENT_H

#include<string>
#include<list>
#include<iostream>

namespace dtd {
	class ContentSpec;

	class Element {
		public:
			std::ostream& put(std::ostream& out);

		protected:
			std::string name;
			ContentSpec* content;
	};
	
	class ContentSpec {
		public:
			virtual std::ostream& put(std::ostream& out) = 0;
	};
	
	class Children : public ContentSpec {
		public:
			virtual std::ostream& put(std::ostream& out) = 0;
		
		protected:
			char card;
	};
	
	class Choice : public Children {
		public:
			std::ostream& put(std::ostream& out);
		
		protected:
			std::list<Children*> choices;
	};
	
	class Seq : public Children {
		public:
			std::ostream& put(std::ostream& out);
		
		protected:
			std::list<Children*> seq;
	};
	
	class Name : public Children {
		public:
			std::ostream& put(std::ostream& out);
		
		protected:
			std::string name;
	};
}

#endif
