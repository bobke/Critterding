#ifndef SPECIESVIEW_H
#define SPECIESVIEW_H

#include "../../gui/panel.h"
#include "../entities/genotypes.h"
#include "../../math/vector2f.h"

# include <vector>

using namespace std;

class Speciesview : public Panel
{
	public:
		Speciesview();
		~Speciesview();

		void draw();
	private:
		Genotypes* genotypes;

};

#endif
