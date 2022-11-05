#include "Game.h"
#include <windows.h>
int main()
{

	std::cout<< GetSystemMetrics(SM_CXSCREEN) << " " << GetSystemMetrics(SM_CYSCREEN) << std::endl;
    Game game(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), "BREAKER MASTER");
	game.Run();
    return 0;
}