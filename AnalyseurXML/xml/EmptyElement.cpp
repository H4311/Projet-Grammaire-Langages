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