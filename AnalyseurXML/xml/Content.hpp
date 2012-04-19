#ifndef __XML_CONTENT_H__
#define __XML_CONTENT_H__

# include <iostream>
using namespace std;

namespace xml {
	class Content {
	protected:
		void printTabs(ostream& stream, int depth);

	public:
		virtual ostream& toString(ostream& stream, int depth) = 0;
		virtual ~Content() {}
	};
}

ostream& operator<<(ostream& stream, xml::Content* content);
#endif
