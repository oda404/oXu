cmake_minimum_required(VERSION 3.2)

project(oXu)

# use c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OXU_SRC_DIR src/oXu)
set(OXU_INCLUDE_DIR src)

set(CMAKE_CXX_FLAGS "-O2 -Wall -Wextra")

add_subdirectory(vendor/glad)
add_subdirectory(vendor/spdlog)

set(OXU_HEADERS
    ${OXU_SRC_DIR}/game.hpp

    #core/
    ${OXU_SRC_DIR}/core/fs.hpp
    ${OXU_SRC_DIR}/core/status.hpp
    ${OXU_SRC_DIR}/core/logger.hpp
    ${OXU_SRC_DIR}/core/window.hpp

    #core/threading/
    ${OXU_SRC_DIR}/core/threading/thread.hpp

    ${OXU_SRC_DIR}/core/threading/pipeline/request.hpp
    ${OXU_SRC_DIR}/core/threading/pipeline/pipeline.hpp

    #graphics/
    ${OXU_SRC_DIR}/graphics/handler.hpp
    ${OXU_SRC_DIR}/graphics/renderer.hpp
    ${OXU_SRC_DIR}/graphics/texture.hpp
    ${OXU_SRC_DIR}/graphics/genericBackend.hpp

    #graphics/utils/
    ${OXU_SRC_DIR}/graphics/utils/img.hpp

    #graphics/opengl/
    ${OXU_SRC_DIR}/graphics/opengl/core.hpp
    ${OXU_SRC_DIR}/graphics/opengl/backend.hpp
    ${OXU_SRC_DIR}/graphics/opengl/shader.hpp
    ${OXU_SRC_DIR}/graphics/opengl/vertexBuffer.hpp
    ${OXU_SRC_DIR}/graphics/opengl/indexBuffer.hpp
    ${OXU_SRC_DIR}/graphics/opengl/vertexArrayObject.hpp
    ${OXU_SRC_DIR}/graphics/opengl/vertexLayout.hpp
    ${OXU_SRC_DIR}/graphics/opengl/vertexLayoutElement.hpp
    ${OXU_SRC_DIR}/graphics/opengl/texture.hpp

    #audio/
    ${OXU_SRC_DIR}/audio/handler.hpp
    ${OXU_SRC_DIR}/audio/player.hpp
    ${OXU_SRC_DIR}/audio/sound.hpp

    #input/
    ${OXU_SRC_DIR}/input/handler.hpp

    #utils/
    ${OXU_SRC_DIR}/utils/timer.hpp
    ${OXU_SRC_DIR}/utils/vector2.hpp

    #beatmap/
    ${OXU_SRC_DIR}/beatmap/beatmap.hpp
    ${OXU_SRC_DIR}/beatmap/beatmapParser.hpp
    ${OXU_SRC_DIR}/beatmap/song.hpp
    ${OXU_SRC_DIR}/beatmap/songManager.hpp

    #beatmap/components/
    ${OXU_SRC_DIR}/beatmap/components/hitObject.hpp
    ${OXU_SRC_DIR}/beatmap/components/hitCircle.hpp
    ${OXU_SRC_DIR}/beatmap/components/approachCircle.hpp
    ${OXU_SRC_DIR}/beatmap/components/slider.hpp
    ${OXU_SRC_DIR}/beatmap/components/playField.hpp

    #beatmap/sections/
    ${OXU_SRC_DIR}/beatmap/sections/config.hpp
    ${OXU_SRC_DIR}/beatmap/sections/color.hpp
    ${OXU_SRC_DIR}/beatmap/sections/difficulty.hpp
    ${OXU_SRC_DIR}/beatmap/sections/editor.hpp
    ${OXU_SRC_DIR}/beatmap/sections/events.hpp
    ${OXU_SRC_DIR}/beatmap/sections/general.hpp
    ${OXU_SRC_DIR}/beatmap/sections/metadata.hpp
    ${OXU_SRC_DIR}/beatmap/sections/timingPoint.hpp

    #skin/
    ${OXU_SRC_DIR}/skin/skin.hpp
    ${OXU_SRC_DIR}/skin/skinManager.hpp
    ${OXU_SRC_DIR}/skin/config.hpp
)

set(OXU_SRC
    ${OXU_SRC_DIR}/main.cpp
    ${OXU_SRC_DIR}/game.cpp

    #core/
    ${OXU_SRC_DIR}/core/status.cpp
    ${OXU_SRC_DIR}/core/fs.cpp
    ${OXU_SRC_DIR}/core/logger.cpp
    ${OXU_SRC_DIR}/core/window.cpp

    #core/threading/
    ${OXU_SRC_DIR}/core/threading/thread.cpp

    ${OXU_SRC_DIR}/core/threading/pipeline/request.cpp
    ${OXU_SRC_DIR}/core/threading/pipeline/pipeline.cpp

    # graphics/
    ${OXU_SRC_DIR}/graphics/handler.cpp
    ${OXU_SRC_DIR}/graphics/renderer.cpp
    ${OXU_SRC_DIR}/graphics/texture.cpp

    #graphics/utils/
    ${OXU_SRC_DIR}/graphics/utils/img.cpp

    #graphics/opengl/
    ${OXU_SRC_DIR}/graphics/opengl/core.cpp
    ${OXU_SRC_DIR}/graphics/opengl/backend.cpp
    ${OXU_SRC_DIR}/graphics/opengl/shader.cpp
    ${OXU_SRC_DIR}/graphics/opengl/vertexBuffer.cpp
    ${OXU_SRC_DIR}/graphics/opengl/indexBuffer.cpp
    ${OXU_SRC_DIR}/graphics/opengl/vertexArrayObject.cpp
    ${OXU_SRC_DIR}/graphics/opengl/vertexLayout.cpp
    ${OXU_SRC_DIR}/graphics/opengl/vertexLayoutElement.cpp
    ${OXU_SRC_DIR}/graphics/opengl/texture.cpp

    #audio/
    ${OXU_SRC_DIR}/audio/handler.cpp
    ${OXU_SRC_DIR}/audio/player.cpp
    ${OXU_SRC_DIR}/audio/sound.cpp

    #input/
    ${OXU_SRC_DIR}/input/handler.cpp

    #utils/
    ${OXU_SRC_DIR}/utils/timer.cpp

    #beatmap/
    ${OXU_SRC_DIR}/beatmap/beatmap.cpp
    ${OXU_SRC_DIR}/beatmap/beatmapParser.cpp
    ${OXU_SRC_DIR}/beatmap/song.cpp
    ${OXU_SRC_DIR}/beatmap/songManager.cpp

    #beatmap/components/
    ${OXU_SRC_DIR}/beatmap/components/hitObject.cpp
    ${OXU_SRC_DIR}/beatmap/components/hitCircle.cpp
    ${OXU_SRC_DIR}/beatmap/components/approachCircle.cpp
    ${OXU_SRC_DIR}/beatmap/components/slider.cpp
    ${OXU_SRC_DIR}/beatmap/components/playField.cpp

    #beatmap/sections
    ${OXU_SRC_DIR}/beatmap/sections/config.cpp

    #skin/
    ${OXU_SRC_DIR}/skin/skin.cpp
    ${OXU_SRC_DIR}/skin/skinManager.cpp
    ${OXU_SRC_DIR}/skin/config.cpp
)

add_executable(${PROJECT_NAME}
    ${OXU_HEADERS}
    ${OXU_SRC}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${OXU_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    spdlog
    glad
    png
    SDL2
    ${CMAKE_DL_LIBS}
)
