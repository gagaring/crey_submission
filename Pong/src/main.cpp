
#include "Framework.h"
#include "pong/pong.h"

#include <exception>
#include <iostream>

int main(void)
{
	try {
		sf::Framework< pong::Pong > framework = {};
		const bool ret = framework.init();
		if (!ret)
		{
			framework.terminate();
			return -1;
		}
		framework.loop();
		framework.terminate();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}
