#include "settingsbrainpanel.h"

Settingsbrainpanel::Settingsbrainpanel()
{
	v_width = 490;
	v_height = 540;

	isMovable = true;

	position.x = 50;
	position.y = 35;

	unsigned int vint = 12;
	
	hspace = 10;
	vspace = vint;  addSettingmutator("brain_maxneurons", hspace, vspace);
	vspace += vint; addSettingmutator("brain_minsynapses", hspace, vspace);
	vspace += vint; addSettingmutator("brain_maxsynapses", hspace, vspace);
	vspace += vint; addSettingmutator("brain_minneuronsatbuildtime", hspace, vspace);
	vspace += vint; addSettingmutator("brain_maxneuronsatbuildtime", hspace, vspace);
	vspace += vint; addSettingmutator("brain_minsynapsesatbuildtime", hspace, vspace);
	vspace += vint; addSettingmutator("brain_maxsynapsesatbuildtime", hspace, vspace);
	vspace += vint; addSettingmutator("brain_percentchanceinhibitoryneuron", hspace, vspace);
	vspace += vint; addSettingmutator("brain_mutate_percentchanceinhibitoryneuron", hspace, vspace);
	vspace += vint; addSettingmutator("brain_percentchancemotorneuron", hspace, vspace);
	vspace += vint; addSettingmutator("brain_mutate_percentchancemotorneuron", hspace, vspace);
	vspace += vint; addSettingmutator("brain_percentchanceplasticneuron", hspace, vspace);
	vspace += vint; addSettingmutator("brain_mutate_percentchanceplasticneuron", hspace, vspace);
	vspace += vint; addSettingmutator("brain_minplasticitystrengthen", hspace, vspace);
	vspace += vint; addSettingmutator("brain_maxplasticitystrengthen", hspace, vspace);
	vspace += vint; addSettingmutator("brain_minplasticityweaken", hspace, vspace);
	vspace += vint; addSettingmutator("brain_maxplasticityweaken", hspace, vspace);
	vspace += vint; addSettingmutator("brain_mutate_plasticityfactors", hspace, vspace);
	vspace += vint; addSettingmutator("brain_minfiringthreshold", hspace, vspace);
	vspace += vint; addSettingmutator("brain_mutate_minfiringthreshold", hspace, vspace);
	vspace += vint; addSettingmutator("brain_maxfiringthreshold", hspace, vspace);
	vspace += vint; addSettingmutator("brain_mutate_maxfiringthreshold", hspace, vspace);
	vspace += vint; addSettingmutator("brain_maxdendridicbranches", hspace, vspace);
	vspace += vint; addSettingmutator("brain_mutate_maxdendridicbranches", hspace, vspace);
	vspace += vint; addSettingmutator("brain_percentchanceconsistentsynapses", hspace, vspace);
	vspace += vint; addSettingmutator("brain_mutate_percentchanceconsistentsynapses", hspace, vspace);
	vspace += vint; addSettingmutator("brain_percentchanceinhibitorysynapses", hspace, vspace);
	vspace += vint; addSettingmutator("brain_mutate_percentchanceinhibitorysynapses", hspace, vspace);
	vspace += vint; addSettingmutator("brain_percentchancesensorysynapse", hspace, vspace);
	vspace += vint; addSettingmutator("brain_mutate_percentchancesensorysynapse", hspace, vspace);
	vspace += vint; addSettingmutator("brain_percentmutateeffectaddneuron", hspace, vspace);
	vspace += vint; addSettingmutator("brain_percentmutateeffectremoveneuron", hspace, vspace);

	vspace += vint; addSettingmutator("brain_percentmutateeffectalterneuron", hspace, vspace);
	vspace += vint; addSettingmutator("brain_percentmutateeffectaddsynapse", hspace, vspace);
	vspace += vint; addSettingmutator("brain_percentmutateeffectremovesynapse", hspace, vspace);
	vspace += vint; addSettingmutator("brain_mutate_mutateeffects", hspace, vspace);
	
	vspace += vint; addSettingmutator("brain_percentmutateeffectaltermutable", hspace, vspace);
	vspace += vint; addSettingmutator("brain_costhavingneuron", hspace, vspace);
	vspace += vint; addSettingmutator("brain_costfiringneuron", hspace, vspace);
	vspace += vint; addSettingmutator("brain_costfiringmotorneuron", hspace, vspace);
	vspace += vint; addSettingmutator("brain_costhavingsynapse", hspace, vspace);
}

Settingsbrainpanel::~Settingsbrainpanel()
{
}
