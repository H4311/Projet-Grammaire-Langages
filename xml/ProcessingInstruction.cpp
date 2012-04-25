/**
@file xml/ProcessingInstruction.cpp
Ce fichier contient la réalisation de la classe ProcessingInstruction.
@author Benjamin BOUVIER
*/

# include "ProcessingInstruction.hpp"
using namespace std;

namespace xml {

	string ProcessingInstruction::endCharacter()
	{
		return "?>";
	}

	string ProcessingInstruction::beginCharacter()
	{
		return "<?";
	}

}

