#include "Content.hpp"
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

	// TODO
	if (!comments.empty())
	{
		for (list<Comment*>::iterator it = comments.begin();
			it != comments.end();
			it++)
		{
			delete *it;
		}
	}
	
}

xml::Content* xml::Document::getRoot() {
	return root;
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

	// TODO affichage des commentaires
	if (!comments.empty())
	{
		for (list<Comment*>::iterator it = comments.begin();
			it != comments.end();
			++it)
		{
			stream << *it << endl;
		}
	}

	return stream;
}

ostream& operator<< (ostream& stream, xml::Document& doc)
{
	return doc.toString(stream);
}
