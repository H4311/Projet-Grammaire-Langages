# include "EmptyElement.hpp"

namespace xml
{

string EmptyElement::endCharacter()
{
	return "/>";
}

string EmptyElement::beginCharacter()
{
	return "<";
}

void EmptyElement::AddAttribute(Attribut _a)
{
	attributes.push_back(_a);
}

Attribut EmptyElement::FindAttribute(string name)
{
	list<Attribut>::iterator attr = attributes.begin();
	attr = find_if( attr, attributes.end(), bind2nd( AttributName(), name ) );
	if (attr == books.end()) { return null; }
	else return *attr;
}

ostream& EmptyElement::toString(ostream& stream, int depth)
{
	printTabs(stream, depth);
	stream << beginCharacter(); 
	if (!name.first.empty())
	{
		stream << name.first << ":";
	}

	stream << name.second;
	for(AttList::iterator it = attributes.begin();
		it != attributes.end();
		++it)
	{
		stream << " " << it->first << "=\"" << it->second << "\"";
	}
	stream << endCharacter(); 
	return stream;
}

}
