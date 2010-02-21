#include "settingsbodypanel.h"

Settingsbodypanel::Settingsbodypanel()
{
	v_width = 490;
	v_height = 255;

	isMovable = true;

	position.x = 50;
	position.y = 35;

	mutatorcol2 = 350;
	mutatorcol3 = 430;

	unsigned int vint = 12;
	hspace = 10;
	vspace = vint; addSettingmutator("body_maxbodyparts", hspace, vspace);
	vspace += vint; addSettingmutator("body_maxbodypartsatbuildtime", hspace, vspace);
	vspace += vint; addSettingmutator("body_minbodypartsize", hspace, vspace);
	vspace += vint; addSettingmutator("body_maxbodypartsize", hspace, vspace);
	vspace += vint; addSettingmutator("body_minheadsize", hspace, vspace);
	vspace += vint; addSettingmutator("body_maxheadsize", hspace, vspace);
	vspace += vint; addSettingmutator("body_percentmutateeffectchangecolor", hspace, vspace);
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

Settingsbodypanel::~Settingsbodypanel()
{
}
