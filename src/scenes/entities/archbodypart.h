#ifndef ARCHBODYPART_H
#define ARCHBODYPART_H

using namespace std;

class archBodypart
{
	public:
		archBodypart();
		~archBodypart();

		unsigned int type;
		unsigned int id;
		float x;
		float y;
		float z;
		unsigned int materialID;

	private:
};

#endif
