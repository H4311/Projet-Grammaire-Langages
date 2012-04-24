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
	if (!doctype.empty())
	{
		stream 	<< "<!DOCTYPE " << rootName << " SYSTEM \""
			<< doctype << "\">\n";
	}

	if (xmlProlog)
	{
		stream << xmlProlog << "\n";	
	}

	if (root)
	{
		stream << root;
	}

	if (!comments->empty())
	{
		for (list<Comment*>::iterator it = comments->begin();
			it != comments->end();
			it++)
		{
			delete *it;
		}
		delete comments;
	}
	return stream;
}

ostream& operator<< (ostream& stream, xml::Document& doc)
{
	return doc.toString(stream);
}
