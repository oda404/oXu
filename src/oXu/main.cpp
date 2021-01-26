// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include<oXu/game.hpp>
#include<oXu/core/status.hpp>
#include<oXu/core/logger.hpp>

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
	if(oxu::init()) oxu::start();

	oxu::clean();

	if(oxu::status::get() == oxu::status::OK)
	{
		OXU_LOG_INFO("Exiting gracefully.");
	}
	else
	{
		OXU_LOG_INFO("Multiple memory leaks probably happened. exit code is {}", oxu::status::get());
	}

	return oxu::status::get();
}
