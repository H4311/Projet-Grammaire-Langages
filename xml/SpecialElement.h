#ifndef __XML_SPECIAL_ELEMENT_H__
#define __XML_SPECIAL_ELEMENT_H__

# include "EmptyElement.h"

# include <list>
using namespace std;

namespace Xml {
	class SpecialElement : public EmptyElement {
	private:
		string beginCharacter();
		string endCharacter();

	public:
		SpecialElement(string _ns, string _name) : EmptyElement(_ns, _name) { } // empty 
		SpecialElement(string _name) : EmptyElement(_name) { } // empty
	};
}
#endif
