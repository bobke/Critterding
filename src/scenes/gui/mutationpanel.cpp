#include "mutationpanel.h"

Mutationpanel::Mutationpanel()
{
	v_width = 340;
	v_height = 85;

	isMovable = true;

	position.x = 50;
	position.y = 35;

	unsigned int vint = 12;
	hspace = 10;
	vspace = vint; addSettingmutator("body_maxmutations", hspace, vspace);
	vspace += vint; addSettingmutator("body_mutationrate", hspace, vspace);

	vspace += vint;
	vspace += vint; addSettingmutator("brain_maxmutations", hspace, vspace);
	vspace += vint; addSettingmutator("brain_mutationrate", hspace, vspace);
}

Mutationpanel::~Mutationpanel()
{
}
