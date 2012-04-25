#ifndef DTD_CHOICE_H
#define DTD_CHOICE_H

#include<string>
#include<list>
#include<iostream>

#include "ChoiceSeq.hpp"

namespace dtd {
	class Choice : public ChoiceSeq {
		public:
			// Choice(std::list<Children*> _children = NULL, char card = 0);
			Choice(std::list<Children*> _children = NULL);
			virtual ~Choice();
			char getSep();
			char getRegexSep();
	};
}

#endif
