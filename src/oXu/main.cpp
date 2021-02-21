// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include<oXu/game.hpp>
#include<oXu/core/status.hpp>
#include<oXu/core/logger.hpp>
#include<oXu/utils/vector2.hpp>

#if defined(__linux__)
#define USERNAME_MAX_LEN 50
#include<unistd.h>
#include<pwd.h>
#endif //__linux__

/*
Variables prefixes:
	p_ - pointer
	c_ - from the same compilation unit
	m_ - member variable
Variable suffixes:
	_p - parameter
*/

static std::string get_user_name()
{
	char buf[USERNAME_MAX_LEN];
	getlogin_r(buf, USERNAME_MAX_LEN);
	return std::string(buf);
}

#define DEFAULT_CONFIG_DIR_PATH "/home/" + get_user_name() + "/.config/oxu"
#define DEFAULT_WINDOW_SIZE oxu::Vector2<std::uint16_t>({ 800, 600 })

int main(int argc, char **argv)
{
	oxu::Config config;
	config.configDirPath = DEFAULT_CONFIG_DIR_PATH;
	config.screenSize = DEFAULT_WINDOW_SIZE;

	oxu::init(config);

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
