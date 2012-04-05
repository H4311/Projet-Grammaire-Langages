# include "EmptyElement.hpp"

namespace xml
{

EmptyElement::EmptyElement(string _ns, string _name)
{
	name = Attribut(_ns, _name); 		
}

EmptyElement::EmptyElement(string _name)
{
	name = Attribut("", _name);
}

string EmptyElement::endCharacter()
{
	return "/>";
}

string EmptyElement::beginCharacter()
{
	return "<";
}

void EmptyElement::AddAttribute(string _name, string _value)
{
	attributes.push_back(Attribut(_name, _value));
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
