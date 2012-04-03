# include "Element.h"

namespace Xml {

void Element::AddChild(Content* _content)
{
	childs.push_back(_content);
}

string Element::endCharacter()
{
	return ">";
}

Element::~Element()
{
	for (list<Content*>::iterator it = childs.begin();
		it != childs.end();
		++it)
	{
		cout << "Un élément de supprimé !" << endl;
		delete *it;
	}
}

ostream& Element::toString(ostream& stream)
{
	ostream & current = EmptyElement::toString(stream);
	for (list<Content*>::iterator it = childs.begin();
		it != childs.end();
		++it)
	{
		Content* currentContent = *it;
		currentContent->toString(current);
		current << endl;
	}
	current << "</";
	if (!name.first.empty())
	{
		current << name.first << ":";
	} 
	current << name.second << ">";
	return current;	
}

}
