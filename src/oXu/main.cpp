// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include<oXu/core/oXu.hpp>
#include<oXu/core/status.hpp>

int main()
{
	oxu::oXu game;
	
	game.init();

	game.update();

	return oxu::Status::code;
}
