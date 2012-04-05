#ifndef __XML_ELEMENT_H__
#define __XML_ELEMENT_H__

# include "EmptyElement.hpp"

# include <list>
using namespace std;

namespace xml {
	class Element : public EmptyElement {
	private:
		list<Content*> childs;
		string endCharacter();

		// Copy and affectation operators are forbidden.
		Element(Element& copied);
		Element& operator= (Element& affected);
	public:
		Element(Attribut _a) : EmptyElement(_a) { /* empty */ }
		~Element();

		void AddChild(Content* _content);
		virtual ostream& toString(ostream& stream, int depth);
	};
}
#endif
