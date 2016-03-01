#include "ROAllFiles.h"

using namespace std;


int main(int argc, char**argv)
{
	/* ------------------------------------------------------------------
	/*	                RO_V0.02_Case_05
	   -----------------------------------------------------------------*/


	for(int i = 4; i < 9; i++ )
	{
		ROModel model;

		ROVar X(-5, 9, "X"), U(1, 10, "U");

		model.add(ROMinimize(X));

		model.add(U == 9);
		model.add( ROSq(X, i, 0.5) <= U);
	
		model.solve();

		//model.exportModel();

		std::cout << "N = " << i << std::endl;

		std::cout << "Value X = " << model.getVarValue(X) << std::endl;
	}


	return 0;
}