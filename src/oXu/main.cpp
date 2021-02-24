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
#include<oXu/game.hpp>
#include<oXu/core/status.hpp>
#include<oXu/core/logger.hpp>
#include<oXu/utils/vector2.hpp>
#include<argparser/argparser.h>

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

static void print_help()
{
std::cout << "\n\
Usage:\n\
  oXu [options]\n\
\n\
Start oXu.\n\
\n\
Options:\n\
  -h, --help                          Show this message and exit.\n\
  -c, --config-dir-path <path>        Change the config dir path (beatmaps, skins, shaders). Default is /home/$USER/.config/oxu\n\
  -w, --window-size <width>x<height>  Change the initial window size. Default is 800x600.\n\
";
}

static bool is_number(const std::string &str)
{
	for(const char &c: str)
	{
		if(!isdigit(c))
		{
			return false;
		}
	}

	return true;
}

static bool is_window_size_arg_valid(const std::string &arg)
{
	std::size_t split_i = arg.find("x");
	if(split_i == std::string::npos)
		return false;

	if(
		!is_number(arg.substr(0, split_i)) || 
		!is_number(arg.substr(split_i + 1))
	)
		return false;

	return true;
}

static oxu::Vector2<std::uint16_t>
parse_window_size_arg(const std::string &arg)
{
	std::size_t split_i = arg.find("x");
	oxu::Vector2<std::uint16_t> out;

	out.x = atoi(arg.substr(0, split_i).c_str());
	out.y = atoi(arg.substr(split_i + 1).c_str());

	return out;
}

#define DEFAULT_CONFIG_DIR_PATH "/home/" + get_user_name() + "/.config/oxu"
#define DEFAULT_WINDOW_SIZE oxu::Vector2<std::uint16_t>({ 800, 600 })

int main(int argc, char **argv)
{
	Args args;
	args_init(&args);

	args_add("help", "-h", "--help", true, &args);
	args_add("config-dir-path", "-c", "--config-dir-path", false, &args);
	args_add("window-size", "-w", "--window-size", false, &args);

	args_parse(argc, argv, &args);

	if(args_get_bool("help", &args))
	{
		print_help();
		args_free(&args);
		return 0;
	}

	oxu::Config config;
	char *tmp;

	if(args_out_str("config-dir-path", &tmp, &args) == ARG_OK)
		config.configDirPath = tmp;
	else
		config.configDirPath = DEFAULT_CONFIG_DIR_PATH;

	if(
		args_out_str("window-size", &tmp, &args) == ARG_OK &&
		is_window_size_arg_valid(tmp)
	)
		config.screenSize = parse_window_size_arg(tmp);
	else
		config.screenSize = DEFAULT_WINDOW_SIZE;

	args_free(&args);

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
