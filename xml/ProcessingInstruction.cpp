# include "ProcessingInstruction.hpp"

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

