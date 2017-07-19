
#include "src/Game.h"

int main()
{
	Game trinoTet = Game();
	trinoTet.Initialize();
	trinoTet.Load();
	trinoTet.Loop();

	return 0;
}