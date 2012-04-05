# include "Document.hpp"

xml::Document::~Document()
{
	if(xmlProlog)
	{
		delete xmlProlog;
		xmlProlog = 0;
	}

	if(root)
	{
		delete root;
		root = 0;
	}
}

ostream& xml::Document::toString(ostream& stream)
{
	stream << doctype << "\n";
	if (xmlProlog)
	{
		stream << xmlProlog << "\n";	
	}
	if (root)
	{
		stream << root;
	}
	return stream;
}

ostream& operator<< (ostream& stream, xml::Document& doc)
{
	return doc.toString(stream);
}
