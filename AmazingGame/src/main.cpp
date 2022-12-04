
#include "Framework.h"
#include "MyAmazingGame.h"

int main(void)
{
	sf::Framework< MyAmazingGame > framework = {};
	const bool ret = framework.init();
	if (!ret)
	{
		framework.terminate();
		return -1;
	}
	framework.loop();
	framework.terminate();
	return 0;
}
