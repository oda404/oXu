// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include<iostream>
#include<oxu/game.hpp>
#include<oxu/game_config.hpp>
#include<oxu/framework/status.hpp>
#include<oxu/framework/logger.hpp>
#include<oxu/framework/utils/vector2.hpp>
#include<oxu/framework/fs.hpp>
#include<argx/argx.hpp>

static oxu::framework::Vector2<std::uint16_t>
parse_window_size_arg(const std::string &arg)
{
	std::size_t split_i = arg.find("x");
	if(split_i == std::string::npos)
		return oxu::GameConfig::default_window_size;
	
	oxu::framework::Vector2<std::uint16_t> ret;

	const std::string x = arg.substr(0, split_i);
	const std::string y = arg.substr(split_i + 1);

	try
	{
		ret.x = std::stoul(x);
		ret.y = std::stoul(y);
	}
	catch(...)
	{
		return oxu::GameConfig::default_window_size;
	}

	return ret;
}

int main(int argc, char **argv)
{
	argx::Argx argx;

	argx.arg_add("help",        "-h", "--help",        "Show this message and exit.", true);
	argx.arg_add("res-dir",     "-r", "--res-dir",     "Resources directory path.", false);
	argx.arg_add("songs-dir",   "-S", "--songs-dir",   "Beatmaps directory path.", false);
	argx.arg_add("skins-dir",   "-s", "--skins-dir",   "Skins directory path.", false);
	argx.arg_add("window-size", "-w", "--window-size", "Window size in the format of <width>x<height>.", false);
	argx.help_msg_gen(
		"Usage: oxu [options]", 
		"Starts the oxu client.\n\nOptions:"
	);

	argx.args_parse(argv, argc);

	if(argx.arg_present("help"))
	{
		std::cout << argx.help_msg_get();
		return 0;
	}

	oxu::GameConfig config;
	std::string tmp;

	argx.arg_val_get("window-size", tmp);
	config.window_size = parse_window_size_arg(tmp);

	if(argx.arg_val_get("res-dir", config.res_dir) != 0)
	{
		config.res_dir = oxu::GameConfig::default_res_dir;
	}

	if(argx.arg_val_get("songs-dir", config.songs_dir) != 0)
	{
		config.songs_dir = oxu::GameConfig::default_songs_dir;
	}

	if(argx.arg_val_get("skins-dir", config.skins_dir) != 0)
	{
		config.skins_dir = oxu::GameConfig::default_skins_dir;
	}

	namespace oxufs = oxu::framework::fs;
	config.res_dir   = oxufs::canonical(config.res_dir);
	config.songs_dir = oxufs::canonical(config.songs_dir);
	config.skins_dir = oxufs::canonical(config.skins_dir);

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
