#ifndef __XML_DATA_H__
#define __XML_DATA_H__

# include "Content.h"
# include <string>
using namespace std;

namespace Xml {
	class Data : public Content {
	private:
		string data;

	public:
		Data(string _d) : data(_d) { /* empty */ } 
		
		virtual ostream& toString(ostream& stream);
	};
}
#endif
