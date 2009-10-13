#include "settingspanel.h"

Settingspanel::Settingspanel()
{
	v_width = 510;
	v_height = 470;

	isMovable = true;

	position.x = 50;
	position.y = 50;

	unsigned int vint = 6;
	hspace = 10;
	vspace = vint;
	addSettingmutator("mincritters", 10, vspace);
// 	vspace += vint; addSettingmutator("energy", hspace, vspace); // FIXME cannot compute

	vspace += vint;
	vspace += vint; addSettingmutator("critter_maxlifetime", hspace, vspace);
	vspace += vint; addSettingmutator("critter_maxenergy", hspace, vspace);
	vspace += vint; addSettingmutator("critter_startenergy", hspace, vspace);
	vspace += vint; addSettingmutator("critter_procinterval", hspace, vspace);
	vspace += vint; addSettingmutator("critter_minenergyproc", hspace, vspace);
	vspace += vint; addSettingmutator("critter_sightrange", hspace, vspace);
	vspace += vint; addSettingmutator("critter_autosaveinterval", hspace, vspace);
	vspace += vint; addSettingmutator("critter_killhalfat", hspace, vspace);
	vspace += vint; addSettingmutator("critter_enableomnivores", hspace, vspace);

	vspace += vint;
	vspace += vint; addSettingmutator("food_maxlifetime", hspace, vspace);
	vspace += vint; addSettingmutator("food_maxenergy", hspace, vspace);
	vspace += vint; addSettingmutator("food_size", hspace, vspace);

	vspace += vint;
	vspace += vint; addSettingmutator("body_maxmutations", hspace, vspace);
	vspace += vint; addSettingmutator("body_mutationrate", hspace, vspace);
	vspace += vint; addSettingmutator("body_maxbodyparts", hspace, vspace);
	vspace += vint; addSettingmutator("body_maxbodypartsatbuildtime", hspace, vspace);
	vspace += vint; addSettingmutator("body_minbodypartsize", hspace, vspace);
	vspace += vint; addSettingmutator("body_maxbodypartsize", hspace, vspace);
	vspace += vint; addSettingmutator("body_minheadsize", hspace, vspace);
	vspace += vint; addSettingmutator("body_maxheadsize", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectaddbodypart", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectremovebodypart", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectresizebodypart", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectresizebodypart_slightly", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectchangeconstraintlimits", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectchangeconstraintlimits_slightly", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectchangeconstraintangles", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectchangeconstraintangles_slightly", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectchangeconstraintposition", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectchangeconstraintposition_slightly", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectresizehead", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectresizehead_slightly", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectrepositionhead", hspace, vspace);
}

Settingspanel::~Settingspanel()
{
}
