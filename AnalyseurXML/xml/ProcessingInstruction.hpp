#ifndef __XML_PROC_INSTRUCTION_H__
#define __XML_PROC_INSTRUCTION_H__

#include "EmptyElement.hpp"
#include <string>
using namespace std;

namespace xml {
	class ProcessingInstruction : public EmptyElement {
	private:
		string beginCharacter();
		string endCharacter();

	public:
		ProcessingInstruction(ElementName _name) : EmptyElement(_name) { /* empty */ }
	};
}
#endif
