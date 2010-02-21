#include "genotype.h"

Genotype::Genotype()
{
	bodyArch = new BodyArch();
	brainzArch = new BrainzArch();

	count = 0;
	adamdist = 0;
}

void Genotype::registerBrainInputOutputs()
{

// BRAIN INPUTS

	// touching food
		brainzArch->registerInput( 10000 );


	// touching critter
		brainzArch->registerInput( 10001 );

	// canprocreate
		brainzArch->registerInput( 20000 );

	// energy state
		for ( unsigned int i=0; i < 10; i++ )
			brainzArch->registerInput( 30000+i );
	// age state
		for ( unsigned int i=0; i < 10; i++ )
			brainzArch->registerInput( 40000+i );

	// vision retina number of items
		unsigned int items = bodyArch->retinasize * bodyArch->retinasize * 4;
		for ( unsigned int i=0; i < items; i++ )
			brainzArch->registerInput( 50000+i );

	// register constraint angles outputs as brain inputs, take constraint_id1 for ease
		for ( unsigned int i=0; i < bodyArch->archConstraints.size(); i++ )
			brainzArch->registerInput( bodyArch->archConstraints[i].constraint_id1 );

// BRAIN OUTPUTS

	// register constraints's inputs as brain outputs
		for ( unsigned int i=0; i < bodyArch->archConstraints.size(); i++ )
		{
			brainzArch->registerOutput( bodyArch->archConstraints[i].constraint_id1 );
			brainzArch->registerOutput( bodyArch->archConstraints[i].constraint_id2 );
		}

	// eat
		brainzArch->registerOutput( 100000 );

	// procreate
		brainzArch->registerOutput( 100001 );
}

string Genotype::saveGenotype()
{
	stringstream buf;
// 	buf << "color=" << color[0] << "," << color[1] << "," << color[2] << ";\n";
	buf << "adamdist=" << adamdist << ";\n";
// 	buf << "retinasize=" << retinasize << ";\n";

	string* bodyarch = bodyArch->getArch();
	string* brainarch = brainzArch->getArch();
	buf << *bodyarch;
	buf << *brainarch;
	//cout << *arch << endl;

	return buf.str();
}

Genotype::~Genotype()
{
	delete bodyArch;
	delete brainzArch;
}


