#include "Validateur.hpp"
#include <boost/regex.hpp>

bool Validateur::validationNode(std::string dtdNode, std::string xmlChildren) {
    boost::regex reg(dtdNode.c_str());
	
	if (regex_match(xmlChildren.c_str(), reg)) 
	{
		return true;
	}
	else
	{
		return false;
	}
    
}

bool Validateur::validationDocument(xml::Document xml, dtd::Document dtd) {
	//TODO: parcourir tout l'arbre xml
	//pour chacun des noeuds xml
	//Faire un getRegex sur l'élément de la dtd correspondant
	//Faire la chaine XML
	//appeller validationNode et stopped si ça retourne false
}
