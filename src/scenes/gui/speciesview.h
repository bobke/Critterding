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

		int titlebar;
		int v_space;
		int rowspacer;
		int qwidth;
		int qheight;
		
		string titlePos;
		string titleColor;
		string titleNum;
		string titleAd;
		string titleNeurons;
		string titleSynapses;
		string titleBodyparts;
		
		int titlePosW;
		int titleColorW;
		int titleNumW;
		int titleAdW;
		int titleNeuronsW;
		int titleSynapsesW;
		int titleBodypartsW;
		
		const unsigned int*	colormode;
};

#endif
