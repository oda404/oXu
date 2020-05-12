// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"core/game.hpp"

int main(int argc, char **argv)
{
	if(!oxu::Game::getInstance().init())
	{
		oxu::Game::getInstance().clean();
		return INIT_FAILURE;
	}

	oxu::Game::getInstance().loop();

	oxu::Game::getInstance().clean();

	return GOOD_EXIT;
}
