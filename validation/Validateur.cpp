#include "validateur.hpp"

bool Validateur::validationNode(std::string dtdNode, std::string xmlChildren) {
    //TODO: check boost entre dtdNode (regex) et xmlChildren (text)
}

bool Validateur::validationDocument(xml::Document xml, dtd::Document dtd) {
	//TODO: parcourir tout l'arbre xml
	//pour chacun des noeuds xml
	//Faire un getRegex sur l'élément de la dtd correspondant
	//Faire la chaine XML
	//appeller validationNode et stopped si ça retourne false
}
