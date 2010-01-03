#ifndef STATSGRAPH_H
#define STATSGRAPH_H

#include "../../gui/panel.h"
#include "../../utils/statsbuffer.h"

using namespace std;

class Statsgraph : public Panel
{
	public:
		Statsgraph();
		~Statsgraph();

		void draw();

	private:
		Statsbuffer* statsBuffer;
};

#endif
