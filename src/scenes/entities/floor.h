#ifndef FLOOR_H
#define FLOOR_H

using namespace std;

class Floor
{
	public:
		Floor();
		~Floor();

		unsigned int		gridsizeX;
		unsigned int		gridsizeY;
		void			resize(unsigned int X, unsigned int Y);
	private:
};

#endif
