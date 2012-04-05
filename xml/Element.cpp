# include "Element.hpp"

namespace xml {

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
		delete *it;
	}
}

ostream& Element::toString(ostream& stream, int depth)
{
	ostream & current = EmptyElement::toString(stream, depth);
	current << endl;

	for (list<Content*>::iterator it = childs.begin();
		it != childs.end();
		++it)
	{
		Content* currentContent = *it;
		currentContent->toString(current, depth+1);
		current << endl;
	}
	
	printTabs(stream, depth);
	current << "</";
	if (!name.first.empty())
	{
		current << name.first << ":";
	} 
	current << name.second << ">";
	return current;	
}

}
