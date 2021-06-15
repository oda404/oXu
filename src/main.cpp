// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#if defined(__linux__)
#define USERNAME_MAX_LEN 50
#include<unistd.h>
#include<pwd.h>
#elif defined(_WIN32)
bruh moment #2
#endif //__linux__

#include<iostream>
#include<cctype>
#include<oxu/game.hpp>
#include<oxu/core/status.hpp>
#include<oxu/core/logger.hpp>
#include<oxu/utils/vector2.hpp>
#include<argx/argx.h>

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

static oxu::Vector2<std::uint16_t>
parse_window_size_arg(const std::string &arg)
{
	std::size_t split_i = arg.find("x");
	if(split_i == std::string::npos)
		return DEFAULT_WINDOW_SIZE;
	
	oxu::Vector2<std::uint16_t> ret;

	const std::string x = arg.substr(0, split_i).c_str();
	const std::string y = arg.substr(split_i + 1).c_str();

	try
	{
		ret.x = std::stoul(x);
		ret.y = std::stoul(y);
	}
	catch(...)
	{
		return DEFAULT_WINDOW_SIZE;
	}

	return ret;
}


int main(int argc, char **argv)
{
	Argx argx;
	argx_init(&argx);

	argx_arg_add("help", "-h", "--help", "Show this message and exit.", true, &argx);
	argx_arg_add("config-dir-path", "-c", "--config-dir-path", "Path to the oxu config directory.", false, &argx);
	argx_arg_add("window-size", "-w", "--window-size", "Window size in the format of <width>x<height>.", false, &argx);
	argx_help_msg_gen("Usage: oxu [options]", "Starts the oxu client.", &argx);

	argx_args_parse(argv, argc, &argx);

	if(argx_arg_present("help", &argx))
	{
		std::cout << argx_help_msg_get(&argx);
		argx_destroy(&argx);
		return 0;
	}

	oxu::Config config;
	size_t arg_len = 0;
	char *arg_str = nullptr;

	if(argx_arg_get_str_len("window-size", &arg_len, &argx) == ARGX_GET_OK)
	{
		arg_str = new char[arg_len + 1];
		argx_arg_get_str("window-size", arg_str, &argx);
		config.screenSize = parse_window_size_arg(arg_str);
		delete[] arg_str;
	}
	else
	{
		config.screenSize = DEFAULT_WINDOW_SIZE;
	}

	if(argx_arg_get_str_len("config-dir-path", &arg_len, &argx) == ARGX_GET_OK)
	{
		arg_str = new char[arg_len + 1];
		argx_arg_get_str("config-dir-path", arg_str, &argx);
		config.configDirPath = arg_str;
		delete[] arg_str;
	}
	else
	{
		config.configDirPath = DEFAULT_CONFIG_DIR_PATH;
	}

	argx_destroy(&argx);

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
