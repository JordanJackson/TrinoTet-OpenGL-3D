
#include "src/Game.h"

int main()
{
	Game trinoTet = Game();
	trinoTet.Initialize();
	trinoTet.Load();
	trinoTet.Loop();
	trinoTet.Close();

	return 0;
}