#ifndef __XML_CONTENT_H__
#define __XML_CONTENT_H__

# include <iostream>
using namespace std;

namespace Xml {
	class Content {

	public:
		virtual ostream& toString(ostream& stream) = 0;
		virtual ~Content() {}
	};
}

ostream& operator<<(ostream& stream, Xml::Content* content);
#endif
