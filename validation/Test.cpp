#include "Validateur.hpp"
#include "../dtd/Document.hpp"
#include "../dtd/Element.hpp"
#include "../dtd/Attribute.hpp"
#include "../dtd/AttributeList.hpp"
#include "../dtd/Name.hpp"
#include "../dtd/Choice.hpp"
#include "../dtd/Seq.hpp"

#include "../xml/Content.hpp"
#include "../xml/Element.hpp"
#include "../xml/Data.hpp"
#include "../xml/Comment.hpp"
#include "../xml/ProcessingInstruction.hpp"
#include "../xml/Document.hpp"

// Pour parser les xml et dtd
#include "../xml/xml_processor.h"
#include "../dtd/dtd.h"

#include <iostream>
#include <list>

#include "../tests/TestFramework.hpp"

// Doc XML
xml::Document* dXML;

// Doc DTD
dtd::Document* dDTD;

struct TestValidationChildren : public TestCase
{
	TestValidationChildren() : TestCase("Vérifie que ValidationChildren fonctionne correctement.") {}
	bool operator()()
	{
		return Validateur::validationChild(
			"((titre,)(auteur,)+(resume,)(chapitre,)+)", 
			"titre,auteur,resume,chapitre,");
	}
};

struct TestValidationSansErreur : public TestCase
{
	TestValidationSansErreur() : TestCase("Vérifie qu'une validation de doc conforme au dtd réussit.") {}
	bool operator()()
	{
		dXML = parseXML("../tests/rap1.xml");
		dDTD = parseDTD("../tests/rap1.dtd");
		bool result = Validateur::validationDocument(*dDTD, *dXML);
		delete dXML;
		delete dDTD;
		return result;
	}
};

struct TestValidationAvecErreur : public TestCase
{
	TestValidationAvecErreur() : TestCase("Vérifie que la validation du doc échoue conformément à la DTD.") {}
	bool operator()()
	{
		dXML = parseXML("../tests/rap2.xml");
		dDTD = parseDTD("../tests/rap2.dtd");
		bool result = Validateur::validationDocument(*dDTD, *dXML);
		delete dXML;
		delete dDTD;
		return !result;
	}
};

struct TestValidationSansErreur2 : public TestCase
{
	TestValidationSansErreur2() : TestCase("Vérifie que la validation de doc échoue car balise <strong> non définie dans la DTD.") {}
	bool operator()()
	{
		dDTD = parseDTD("../tests/rap3.dtd");
		dXML = parseXML("../tests/rap3.xml");
		bool result = Validateur::validationDocument(*dDTD, *dXML);
		delete dXML;
		delete dDTD;
		return !result;
	}
};

int main(int argc, char** argv) {
	
	TestSuite t;
	t.add(new TestValidationChildren);
	t.add(new TestValidationSansErreur);
	t.add(new TestValidationAvecErreur);
	t.add(new TestValidationSansErreur2);
	t.launch();
	
	return 0;
}
