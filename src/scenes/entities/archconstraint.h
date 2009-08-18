#ifndef ARCHCONSTRAINT_H
#define ARCHCONSTRAINT_H

using namespace std;

class archConstraint
{
	public:
		archConstraint();
		~archConstraint();

		unsigned int type;

		unsigned int constraint_id1;
		unsigned int constraint_id2;

		bool isMouthConstraint;

		unsigned int XYZ;
		int sign;
		
		unsigned int id_1;
		unsigned int id_2;

		float rot_x_1;
		float rot_x_2;
		float rot_y_1;
		float rot_y_2;
		float rot_z_1;
		float rot_z_2;

		float pos_x_1;
		float pos_x_2;
		float pos_y_1;
		float pos_y_2;
		float pos_z_1;
		float pos_z_2;

		float limit_1;
		float limit_2;

	private:
};

#endif
