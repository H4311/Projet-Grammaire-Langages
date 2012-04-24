#ifndef __XML_ELEMENT_H__
#define __XML_ELEMENT_H__

# include "EmptyElement.hpp"

# include <list>
using namespace std;

namespace xml {
	class Element : public EmptyElement {
	private:
		list<Content*> children;
		string endCharacter();

		// Copy and affectation operators are forbidden.
		Element(Element& copied);
		Element& operator= (Element& affected);
	public:
		Element(ElementName _n) : EmptyElement(_n) { /* empty */ }
		Element() {}

		~Element();
		
		void Setchildren(list<Content*> * _children) { children = *_children; }

		void AddChild(Content* _content);
		virtual ostream& toString(ostream& stream, int depth);
	};
}
#endif
