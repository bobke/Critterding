#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include "../../utils/logbuffer.h"
#include "../../gui/panel.h"

using namespace std;

class Textmessage : public Panel
{
	public:
		Textmessage();
		~Textmessage();

		void		draw();
	private:

		int		vpadding;
		int		hpadding;
};

#endif
