// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include<oXu/game.hpp>
#include<oXu/core/status.hpp>

/*
Variables prefixes:
	p_ - pointer
	c_ - from the same compilation unit
	m_ - member variable
Variable suffixes:
	_p - parameter
*/

int main(void)
{
	if(oxu::init())
	{
		oxu::start();
	}

	oxu::clean();

	return oxu::Status::code;
}
