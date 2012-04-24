#ifndef DTD_SEQ_H
#define DTD_SEQ_H

#include<string>
#include<list>
#include<iostream>

#include "ChoiceSeq.hpp"

namespace dtd {
	class Seq : public ChoiceSeq {
		public:
			Seq(std::list<Children*> _children = NULL, char card = 0);
			virtual ~Seq();
			char getSep();
			char getRegexSep();
	};
}

#endif
