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
#include<oxu/game.hpp>
#include<oxu/framework/status.hpp>
#include<oxu/framework/logger.hpp>
#include<oxu/framework/utils/vector2.hpp>
#include<argx/argx.hpp>

static oxu::framework::Vector2<std::uint16_t>
parse_window_size_arg(const std::string &arg)
{
	std::size_t split_i = arg.find("x");
	if(split_i == std::string::npos)
		return DEFAULT_WINDOW_SIZE;
	
	oxu::framework::Vector2<std::uint16_t> ret;

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
	argx::Argx argx;

	argx.arg_add("help",        "-h", "--help",        "Show this message and exit.", true);
	argx.arg_add("res-dir",     "-r", "--res-dir",     "Resources directory path.", false);
	argx.arg_add("songs-dir",   "-S", "--songs-dir",   "Beatmaps directory path", false);
	argx.arg_add("skins-dir",   "-s", "--skins-dir",   "Skins directory path.", false);
	argx.arg_add("window-size", "-w", "--window-size", "Window size in the format of <width>x<height>", false);
	argx.help_msg_gen(
		"Usage: oxu [options]", 
		"Starts the oxu client."
	);

	argx.args_parse(argv, argc);

	if(argx.arg_present("help"))
	{
		std::cout << argx.help_msg_get();
		return 0;
	}

	oxu::Config config;
	std::string tmp;

	argx.arg_val_get("window-size", tmp);
	config.window_size = parse_window_size_arg(tmp);

	if(argx.arg_val_get("res-dir", config.resources_dir_path) != 0)
	{
		config.resources_dir_path = DEFAULT_RES_DIR;
	}

	if(argx.arg_val_get("songs-dir", config.songs_dir_path) != 0)
	{
		config.songs_dir_path = DEFAULT_SONGS_DIR;
	}

	if(argx.arg_val_get("skins-dir", config.skins_dir_path) != 0)
	{
		config.skins_dir_path = DEFAULT_SKINS_DIR;
	}

	oxu::init(config);

	if(oxu::framework::status::get() == oxu::framework::status::OK)
	{
		OXU_LOG_INFO("Exiting gracefully.");
	}
	else
	{
		OXU_LOG_INFO("Multiple memory leaks probably happened. exit code is {}", oxu::framework::status::get());
	}

	return oxu::framework::status::get();
}
