cmake_minimum_required(VERSION 3.2)

project(oxu)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR src)
set(INCLUDE_DIR include)

set(CMAKE_CXX_FLAGS_RELEASE 
    "-O2 -DOXU_RELEASE"
)
set(CMAKE_CXX_FLAGS_DEBUG 
    "-g -DOXU_DEBUG"
)

set(CXX_WARNINGS
    "-Wall -Wextra -Wformat-security"
)

set(CMAKE_CXX_FLAGS 
    "${CXX_WARNINGS} \
    -D_FORTIFY_SOURCE=2 -fstack-protector-strong"
)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/argx)

set(OXU_HEADERS
    ${INCLUDE_DIR}/oxu/game.hpp

    #core/
    ${INCLUDE_DIR}/oxu/core/fs.hpp
    ${INCLUDE_DIR}/oxu/core/status.hpp
    ${INCLUDE_DIR}/oxu/core/logger.hpp
    ${INCLUDE_DIR}/oxu/core/window.hpp

    #core/threading/
    ${INCLUDE_DIR}/oxu/core/threading/thread.hpp

    ${INCLUDE_DIR}/oxu/core/threading/pipeline/request.hpp
    ${INCLUDE_DIR}/oxu/core/threading/pipeline/pipeline.hpp

    #graphics/
    ${INCLUDE_DIR}/oxu/graphics/handler.hpp
    ${INCLUDE_DIR}/oxu/graphics/renderer.hpp
    ${INCLUDE_DIR}/oxu/graphics/texture.hpp
    ${INCLUDE_DIR}/oxu/graphics/genericBackend.hpp

    #graphics/utils/
    ${INCLUDE_DIR}/oxu/graphics/utils/png.hpp

    #graphics/opengl/
    ${INCLUDE_DIR}/oxu/graphics/opengl/core.hpp
    ${INCLUDE_DIR}/oxu/graphics/opengl/backend.hpp
    ${INCLUDE_DIR}/oxu/graphics/opengl/shader.hpp
    ${INCLUDE_DIR}/oxu/graphics/opengl/vertexBuffer.hpp
    ${INCLUDE_DIR}/oxu/graphics/opengl/indexBuffer.hpp
    ${INCLUDE_DIR}/oxu/graphics/opengl/vertexArrayObject.hpp
    ${INCLUDE_DIR}/oxu/graphics/opengl/vertexLayout.hpp
    ${INCLUDE_DIR}/oxu/graphics/opengl/texture.hpp

    #audio/
    ${INCLUDE_DIR}/oxu/audio/handler.hpp
    ${INCLUDE_DIR}/oxu/audio/player.hpp
    ${INCLUDE_DIR}/oxu/audio/sound.hpp

    #input/
    ${INCLUDE_DIR}/oxu/input/handler.hpp

    #utils/
    ${INCLUDE_DIR}/oxu/utils/timer.hpp
    ${INCLUDE_DIR}/oxu/utils/vector2.hpp

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
    ${SRC_DIR}/core/status.cpp
    ${SRC_DIR}/core/fs.cpp
    ${SRC_DIR}/core/logger.cpp
    ${SRC_DIR}/core/window.cpp

    #core/threading/
    ${SRC_DIR}/core/threading/thread.cpp

    ${SRC_DIR}/core/threading/pipeline/request.cpp
    ${SRC_DIR}/core/threading/pipeline/pipeline.cpp

    # graphics/
    ${SRC_DIR}/graphics/handler.cpp
    ${SRC_DIR}/graphics/renderer.cpp
    ${SRC_DIR}/graphics/texture.cpp

    #graphics/utils/
    ${SRC_DIR}/graphics/utils/png.cpp

    #graphics/opengl/
    ${SRC_DIR}/graphics/opengl/core.cpp
    ${SRC_DIR}/graphics/opengl/backend.cpp
    ${SRC_DIR}/graphics/opengl/shader.cpp
    ${SRC_DIR}/graphics/opengl/vertexBuffer.cpp
    ${SRC_DIR}/graphics/opengl/indexBuffer.cpp
    ${SRC_DIR}/graphics/opengl/vertexArrayObject.cpp
    ${SRC_DIR}/graphics/opengl/vertexLayout.cpp
    ${SRC_DIR}/graphics/opengl/texture.cpp

    #audio/
    ${SRC_DIR}/audio/handler.cpp
    ${SRC_DIR}/audio/player.cpp
    ${SRC_DIR}/audio/sound.cpp

    #input/
    ${SRC_DIR}/input/handler.cpp

    #utils/
    ${SRC_DIR}/utils/timer.cpp

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
