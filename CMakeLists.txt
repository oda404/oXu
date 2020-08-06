cmake_minimum_required(VERSION 3.2)

project(oXu)

# use c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# append cmake/sdl2 to the module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)


set(OXU_SRC_DIR src/oXu)
set(OXU_INCLUDE_DIR src)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(spdlog REQUIRED)

set(OXU_HEADERS
	${OXU_SRC_DIR}/core/game.hpp
	${OXU_SRC_DIR}/core/scaling.hpp
	${OXU_SRC_DIR}/core/status.hpp

	${OXU_SRC_DIR}/core/threading/thread.hpp
	${OXU_SRC_DIR}/core/threading/threads.hpp

	${OXU_SRC_DIR}/handlers/graphics.hpp
	${OXU_SRC_DIR}/handlers/input.hpp
	${OXU_SRC_DIR}/handlers/sound.hpp

	${OXU_SRC_DIR}/components/text.hpp

	${OXU_SRC_DIR}/beatmap/beatmap.hpp
	${OXU_SRC_DIR}/beatmap/beatmapParser.hpp
	${OXU_SRC_DIR}/beatmap/song.hpp
	${OXU_SRC_DIR}/beatmap/songManager.hpp

	${OXU_SRC_DIR}/beatmap/components/hitObject.hpp
	${OXU_SRC_DIR}/beatmap/components/playField.hpp

	${OXU_SRC_DIR}/beatmap/sections/config.hpp
	${OXU_SRC_DIR}/beatmap/sections/color.hpp
	${OXU_SRC_DIR}/beatmap/sections/difficulty.hpp
	${OXU_SRC_DIR}/beatmap/sections/editor.hpp
	${OXU_SRC_DIR}/beatmap/sections/events.hpp
	${OXU_SRC_DIR}/beatmap/sections/general.hpp
	${OXU_SRC_DIR}/beatmap/sections/metadata.hpp
	${OXU_SRC_DIR}/beatmap/sections/timingPoint.hpp

	${OXU_SRC_DIR}/skin/skin.hpp
	${OXU_SRC_DIR}/skin/skinManager.hpp
	${OXU_SRC_DIR}/skin/config.hpp

	${OXU_SRC_DIR}/utils/logger.hpp
	${OXU_SRC_DIR}/utils/timer.hpp
	${OXU_SRC_DIR}/utils/vector2.hpp
)


add_executable(${PROJECT_NAME}
	${OXU_HEADERS}

	${OXU_SRC_DIR}/main.cpp

	${OXU_SRC_DIR}/core/game.cpp
	${OXU_SRC_DIR}/core/scaling.cpp
	${OXU_SRC_DIR}/core/status.cpp

	${OXU_SRC_DIR}/core/threading/thread.cpp
	${OXU_SRC_DIR}/core/threading/threads.cpp

	${OXU_SRC_DIR}/handlers/graphics.cpp
	${OXU_SRC_DIR}/handlers/input.cpp
	${OXU_SRC_DIR}/handlers/sound.cpp

	${OXU_SRC_DIR}/components/text.cpp

	${OXU_SRC_DIR}/beatmap/beatmap.cpp
	${OXU_SRC_DIR}/beatmap/beatmapParser.cpp
	${OXU_SRC_DIR}/beatmap/song.cpp
	${OXU_SRC_DIR}/beatmap/songManager.cpp

	${OXU_SRC_DIR}/beatmap/components/hitObject.cpp
	${OXU_SRC_DIR}/beatmap/components/playField.cpp

	${OXU_SRC_DIR}/beatmap/sections/config.cpp

	${OXU_SRC_DIR}/skin/skin.cpp
	${OXU_SRC_DIR}/skin/skinManager.cpp
	${OXU_SRC_DIR}/skin/config.cpp

	${OXU_SRC_DIR}/utils/logger.cpp
	${OXU_SRC_DIR}/utils/timer.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${OXU_INCLUDE_DIR}
)

# you may ask why i don't use spdlog::spdlog for linking since i call find_package(spdlog REQUIRED)
# as shown in the spdlog example, that's because if i link that way the game starts loding weird textures and takes unusually long to start up, why? I don't know but that's how it is
target_link_libraries(${PROJECT_NAME} PRIVATE
	spdlog
	SDL2::Main
	SDL2::Mixer
	SDL2::TTF
	SDL2::Image
)

