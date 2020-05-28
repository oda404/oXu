// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include<oXu/core/game.hpp>

int main(int argc, char **argv)
{
	if(!oxu::Game::getInstance().init())
	{
		oxu::Game::getInstance().clean();
		return oxu::StatusCodes::statusCode;
	}

	oxu::Game::getInstance().loop();

	oxu::Game::getInstance().clean();

	return oxu::StatusCodes::statusCode;
}
