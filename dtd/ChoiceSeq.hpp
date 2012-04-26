#ifndef DTD_CHOICESEQ_H
#define DTD_CHOICESEQ_H

#include<string>
#include<list>
#include<iostream>

#include "Children.hpp"

namespace dtd {
	class ChoiceSeq : public Children {
		public:
			//ChoiceSeq(std::list<Children*> _children = NULL, char card = 0);
			ChoiceSeq(std::list<Children*> _children = NULL);
			virtual ~ChoiceSeq();
			virtual std::ostream& put(std::ostream& out);
			virtual std::string getRegex();
			virtual char getSep() = 0;
			virtual char getRegexSep() = 0;

		protected:
			std::list<Children*> children;
	};
}

#endif
