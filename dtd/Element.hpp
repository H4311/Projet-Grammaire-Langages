#ifndef DTD_ELEMENT_H
#define DTD_ELEMENT_H

#include<string>
#include<list>
#include<iostream>

namespace dtd {
	class ContentSpec;

	class Element {
		public:
			Element(std::string _name = "", ContentSpec* _content = NULL);
			virtual ~Element();
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
			Children(char _card = 0);
			virtual std::ostream& put(std::ostream& out) = 0;
		
		protected:
			char card;
	};
	
	class ChoiceSeq : public Children {
		public:
			ChoiceSeq(std::list<Children*> _children = NULL);
			virtual ~ChoiceSeq();
			std::ostream& put(std::ostream& out);
			virtual char getSep() = 0;
		
		protected:
			std::list<Children*> children;
	};
	
	class Choice : public Children {
		public:
			char getSep();
	};
	
	class Seq : public Children {
		public:
			char getSep();
	};
	
	class Name : public Children {
		public:
			Name(std::string _name = "");
			std::ostream& put(std::ostream& out);
		
		protected:
			std::string name;
	};
}

#endif
