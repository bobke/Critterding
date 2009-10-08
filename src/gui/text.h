#ifndef TEXT_H
#define TEXT_H

#include "widget.h"

using namespace std;

class Text : public Widget
{
	public:
		Text();
		~Text();
		void		draw();
		string		v_string;
	protected:
	private:
};

#endif
