#ifndef __XML_EMPTY_ELEMENT_H__
#define __XML_EMPTY_ELEMENT_H__

# include "Content.hpp"
# include "../commun.h"

# include <string>
#include <functional>

using namespace std;

namespace xml {
	
	struct AttributName: public std::binary_function< Attribut, string, bool > {
		// Adaptable binary predicate to find an attribute using its name :
		bool operator () ( const Attribut &att, const string &name ) const {
			return att.first == name;
		}
	};

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

		void AddAttribute(Attribut _a);
		
		Attribut FindAttribute(string name);
		virtual ostream& toString(ostream& stream, int depth);
	};
}

#endif
