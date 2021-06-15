cmake_minimum_required(VERSION 3.2)

project(oxu)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR src/oXu)
set(INCLUDE_DIR src)

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
    ${SRC_DIR}/game.hpp

    #core/
    ${SRC_DIR}/core/fs.hpp
    ${SRC_DIR}/core/status.hpp
    ${SRC_DIR}/core/logger.hpp
    ${SRC_DIR}/core/window.hpp

    #core/threading/
    ${SRC_DIR}/core/threading/thread.hpp

    ${SRC_DIR}/core/threading/pipeline/request.hpp
    ${SRC_DIR}/core/threading/pipeline/pipeline.hpp

    #graphics/
    ${SRC_DIR}/graphics/handler.hpp
    ${SRC_DIR}/graphics/renderer.hpp
    ${SRC_DIR}/graphics/texture.hpp
    ${SRC_DIR}/graphics/genericBackend.hpp

    #graphics/utils/
    ${SRC_DIR}/graphics/utils/png.hpp

    #graphics/opengl/
    ${SRC_DIR}/graphics/opengl/core.hpp
    ${SRC_DIR}/graphics/opengl/backend.hpp
    ${SRC_DIR}/graphics/opengl/shader.hpp
    ${SRC_DIR}/graphics/opengl/vertexBuffer.hpp
    ${SRC_DIR}/graphics/opengl/indexBuffer.hpp
    ${SRC_DIR}/graphics/opengl/vertexArrayObject.hpp
    ${SRC_DIR}/graphics/opengl/vertexLayout.hpp
    ${SRC_DIR}/graphics/opengl/texture.hpp

    #audio/
    ${SRC_DIR}/audio/handler.hpp
    ${SRC_DIR}/audio/player.hpp
    ${SRC_DIR}/audio/sound.hpp

    #input/
    ${SRC_DIR}/input/handler.hpp

    #utils/
    ${SRC_DIR}/utils/timer.hpp
    ${SRC_DIR}/utils/vector2.hpp

    #beatmap/
    ${SRC_DIR}/beatmap/beatmap.hpp
    ${SRC_DIR}/beatmap/beatmapParser.hpp
    ${SRC_DIR}/beatmap/song.hpp
    ${SRC_DIR}/beatmap/songManager.hpp

    #beatmap/components/
    ${SRC_DIR}/beatmap/components/hitObject.hpp
    ${SRC_DIR}/beatmap/components/hitCircle.hpp
    ${SRC_DIR}/beatmap/components/slider.hpp
    ${SRC_DIR}/beatmap/components/playField.hpp

    #beatmap/sections/
    ${SRC_DIR}/beatmap/sections/color.hpp
    ${SRC_DIR}/beatmap/sections/difficulty.hpp
    ${SRC_DIR}/beatmap/sections/editor.hpp
    ${SRC_DIR}/beatmap/sections/events.hpp
    ${SRC_DIR}/beatmap/sections/general.hpp
    ${SRC_DIR}/beatmap/sections/metadata.hpp
    ${SRC_DIR}/beatmap/sections/timingPoint.hpp

    #skin/
    ${SRC_DIR}/skin/skin.hpp
    ${SRC_DIR}/skin/skinManager.hpp
    ${SRC_DIR}/skin/config.hpp
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
