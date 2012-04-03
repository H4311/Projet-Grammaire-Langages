#ifndef __XML_ELEMENT_H__
#define __XML_ELEMENT_H__

# include "EmptyElement.h"

# include <list>
using namespace std;

namespace Xml {
	class Element : public EmptyElement {
	private:
		list<Content*> childs;
		string endCharacter();

		// Copy and affectation operators are forbidden.
		Element(Element& copied);
		Element& operator= (Element& affected);
	public:
		Element(string _ns, string _name) : EmptyElement(_ns, _name) { } // empty 
		Element(string _name) : EmptyElement(_name) { } // empty
		~Element();

		void AddChild(Content* _content);
		virtual ostream& toString(ostream& stream);
	};
}
#endif
