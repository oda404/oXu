// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"oxuCore/game.hpp"

#define INIT_FAILURE -1

int main()
{
	oxu::Game game;

	if(!game.w_init())
	{
		return INIT_FAILURE;
	}
	else
	{
		game.g_loop();
	}

	game.w_clean();

	return 0;
}
