#ifndef __XML_EMPTY_ELEMENT_H__
#define __XML_EMPTY_ELEMENT_H__

# include "Content.hpp"
# include "basics.h"

# include <string>

using namespace std;

namespace xml {

	class EmptyElement : public Content {
	protected:
		AttList attributes;
		ElementName name;	

		// Represents the last character to print when calling toString.
		// Should be "/>" for EmptyElement and ">" for Element.
		virtual string endCharacter(); 
		virtual string beginCharacter();
	public:
		EmptyElement(ElementName _en) : name(_en) { /* empty */ }
		EmptyElement() {}

		void SetName(ElementName* _n) { name = *_n; }
		void SetAttList(AttList* _l) { attributes = *_l; }
		
		std::string GetName();

		string GetAttributeValue(string attributeName);
		virtual ostream& toString(ostream& stream, int depth);
	};
}

#endif
