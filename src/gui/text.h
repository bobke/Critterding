#ifndef TEXT_H
#define TEXT_H

#include "widget.h"

using namespace std;

class Text : public Widget
{
	public:
		Text();
		~Text();
		void		set(const string& n_string);
		void		draw();
		string		v_string;
		Vector2i	dimensions;
	protected:
	private:
};

#endif
