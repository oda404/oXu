cmake_minimum_required(VERSION 3.2)

project(oxu)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR src)
set(INCLUDE_DIR include)

set(CMAKE_CXX_FLAGS_RELEASE 
    "-O2 -D_FORTIFY_SOURCE=2 -DOXU_RELEASE"
)
set(CMAKE_CXX_FLAGS_DEBUG 
    "-g -DOXU_DEBUG"
)

set(CXX_WARNINGS
    "-Wall -Wextra -Wformat-security"
)

set(CMAKE_CXX_FLAGS 
    "${CXX_WARNINGS} \
    -fstack-protector-strong"
)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/argx)

set(OXU_HEADERS
    ${INCLUDE_DIR}/oxu/game_config.hpp
    ${INCLUDE_DIR}/oxu/game.hpp

    ${INCLUDE_DIR}/oxu/framework/framework.hpp
    ${INCLUDE_DIR}/oxu/framework/status.hpp
    ${INCLUDE_DIR}/oxu/framework/logger.hpp
    ${INCLUDE_DIR}/oxu/framework/window.hpp

    #core/threading/
    ${INCLUDE_DIR}/oxu/framework/threading/thread.hpp

    ${INCLUDE_DIR}/oxu/framework/threading/request.hpp
    ${INCLUDE_DIR}/oxu/framework/threading/pipeline.hpp

    #graphics/
    ${INCLUDE_DIR}/oxu/framework/graphics/handler.hpp
    ${INCLUDE_DIR}/oxu/framework/graphics/renderer.hpp
    ${INCLUDE_DIR}/oxu/framework/graphics/texture.hpp
    ${INCLUDE_DIR}/oxu/framework/graphics/genericBackend.hpp
    ${INCLUDE_DIR}/oxu/framework/graphics/png.hpp

    #graphics/opengl/
    ${INCLUDE_DIR}/oxu/framework/graphics/opengl/core.hpp
    ${INCLUDE_DIR}/oxu/framework/graphics/opengl/backend.hpp
    ${INCLUDE_DIR}/oxu/framework/graphics/opengl/shader.hpp
    ${INCLUDE_DIR}/oxu/framework/graphics/opengl/vertexBuffer.hpp
    ${INCLUDE_DIR}/oxu/framework/graphics/opengl/indexBuffer.hpp
    ${INCLUDE_DIR}/oxu/framework/graphics/opengl/vertexArrayObject.hpp
    ${INCLUDE_DIR}/oxu/framework/graphics/opengl/vertexLayout.hpp
    ${INCLUDE_DIR}/oxu/framework/graphics/opengl/texture.hpp

    #audio/
    ${INCLUDE_DIR}/oxu/framework/audio/handler.hpp

    #input/
    ${INCLUDE_DIR}/oxu/input/handler.hpp

    #utils/
    ${INCLUDE_DIR}/oxu/framework/utils/timer.hpp
    ${INCLUDE_DIR}/oxu/framework/utils/vector2.hpp

    #beatmap/
    ${INCLUDE_DIR}/oxu/beatmap/beatmap.hpp
    ${INCLUDE_DIR}/oxu/beatmap/beatmapParser.hpp
    ${INCLUDE_DIR}/oxu/beatmap/song.hpp
    ${INCLUDE_DIR}/oxu/beatmap/songManager.hpp

    #beatmap/components/
    ${INCLUDE_DIR}/oxu/beatmap/components/hitObject.hpp
    ${INCLUDE_DIR}/oxu/beatmap/components/hitCircle.hpp
    ${INCLUDE_DIR}/oxu/beatmap/components/slider.hpp
    ${INCLUDE_DIR}/oxu/beatmap/components/playField.hpp

    #beatmap/sections/
    ${INCLUDE_DIR}/oxu/beatmap/sections/color.hpp
    ${INCLUDE_DIR}/oxu/beatmap/sections/difficulty.hpp
    ${INCLUDE_DIR}/oxu/beatmap/sections/editor.hpp
    ${INCLUDE_DIR}/oxu/beatmap/sections/events.hpp
    ${INCLUDE_DIR}/oxu/beatmap/sections/general.hpp
    ${INCLUDE_DIR}/oxu/beatmap/sections/metadata.hpp
    ${INCLUDE_DIR}/oxu/beatmap/sections/timingPoint.hpp

    #skin/
    ${INCLUDE_DIR}/oxu/skin/skin.hpp
    ${INCLUDE_DIR}/oxu/skin/skinManager.hpp
    ${INCLUDE_DIR}/oxu/skin/config.hpp
)

set(OXU_SRC
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/game.cpp

    #core/
    ${SRC_DIR}/framework/framework.cpp
    ${SRC_DIR}/framework/status.cpp
    ${SRC_DIR}/framework/logger.cpp
    ${SRC_DIR}/framework/window.cpp

    #framework/threading/
    ${SRC_DIR}/framework/threading/thread.cpp

    ${SRC_DIR}/framework/threading/request.cpp
    ${SRC_DIR}/framework/threading/pipeline.cpp

    # framework/graphics/
    ${SRC_DIR}/framework/graphics/handler.cpp
    ${SRC_DIR}/framework/graphics/renderer.cpp
    ${SRC_DIR}/framework/graphics/texture.cpp
    ${SRC_DIR}/framework/graphics/png.cpp

    #framework/graphics/opengl/
    ${SRC_DIR}/framework/graphics/opengl/core.cpp
    ${SRC_DIR}/framework/graphics/opengl/backend.cpp
    ${SRC_DIR}/framework/graphics/opengl/shader.cpp
    ${SRC_DIR}/framework/graphics/opengl/vertexBuffer.cpp
    ${SRC_DIR}/framework/graphics/opengl/indexBuffer.cpp
    ${SRC_DIR}/framework/graphics/opengl/vertexArrayObject.cpp
    ${SRC_DIR}/framework/graphics/opengl/vertexLayout.cpp
    ${SRC_DIR}/framework/graphics/opengl/texture.cpp

    #framework/audio/
    ${SRC_DIR}/framework/audio/handler.cpp

    #input/
    ${SRC_DIR}/input/handler.cpp

    #framework/utils/
    ${SRC_DIR}/framework/utils/timer.cpp

    #beatmap/
    ${SRC_DIR}/beatmap/beatmap.cpp
    ${SRC_DIR}/beatmap/beatmapParser.cpp
    ${SRC_DIR}/beatmap/song.cpp
    ${SRC_DIR}/beatmap/songManager.cpp

    #beatmap/components/
    ${SRC_DIR}/beatmap/components/hitObject.cpp
    ${SRC_DIR}/beatmap/components/hitCircle.cpp
    ${SRC_DIR}/beatmap/components/slider.cpp
    ${SRC_DIR}/beatmap/components/playField.cpp

    #skin/
    ${SRC_DIR}/skin/skin.cpp
    ${SRC_DIR}/skin/skinManager.cpp
    ${SRC_DIR}/skin/config.cpp
)

add_executable(${PROJECT_NAME}
    ${OXU_HEADERS}
    ${OXU_SRC}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    spdlog
    argx
    glad
    png
    SDL2
    ${CMAKE_DL_LIBS}
)
