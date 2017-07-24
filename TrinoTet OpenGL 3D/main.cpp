
#include "src/Game.h"

int main()
{
	Game trinoTet = Game();
	trinoTet.Initialize();
	trinoTet.Load();
	std::cout << "Break" << std::endl;
	trinoTet.Loop();
	trinoTet.Close();

	return 0;
}