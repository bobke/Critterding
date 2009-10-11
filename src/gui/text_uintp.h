#ifndef TEXT_UINTP_H
#define TEXT_UINTP_H

#include "widget.h"

using namespace std;

class Text_uintp : public Widget
{
	public:
		Text_uintp();
		~Text_uintp();
		void		draw();
		const unsigned int*	content;
	protected:
	private:
};

#endif
