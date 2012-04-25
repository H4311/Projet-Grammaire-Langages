#include "Choice.hpp"

namespace dtd {

	// ----------------------------------------------------------- Class Choice
	
	Choice::Choice(std::list<Children*> _children)
		: ChoiceSeq(_children) {}
	
	Choice::~Choice() {}
	
	char Choice::getSep() {
		return '|';
	}
	
	char Choice::getRegexSep() {
		return '|';
	}

}
