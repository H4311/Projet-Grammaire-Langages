#include "Choice.hpp"

namespace dtd {

	// ----------------------------------------------------------- Class Choice
	
	Choice::Choice(std::list<Children*> _children, char card)
		: ChoiceSeq(_children, card) {}
	
	Choice::~Choice() {}
	
	char Choice::getSep() {
		return '|';
	}
	
	char Choice::getRegexSep() {
		return '|';
	}

}
