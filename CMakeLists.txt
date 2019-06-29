cmake_minimum_required(VERSION 3.10)
project(OOP_indie_studio_2018)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/modules")
include(FindIrrlicht)
include(FindZip)
include_directories(${CMAKE_SOURCE_DIR}/include/Game)
ZIP_UNPACK_TARGET(splash "${CMAKE_CURRENT_LIST_DIR}/media/splash/" "${CMAKE_CURRENT_LIST_DIR}/media/splash/splash.zip")
set(SRC
        ${CMAKE_SOURCE_DIR}/src/main.cpp
        ${CMAKE_SOURCE_DIR}/src/map/map.cpp
        ${CMAKE_SOURCE_DIR}/src/map/generator.cpp
        ${CMAKE_SOURCE_DIR}/src/game/game.cpp
        ${CMAKE_SOURCE_DIR}/src/launcher/menu.cpp
        ${CMAKE_SOURCE_DIR}/src/bomb/bomb.cpp
		${CMAKE_SOURCE_DIR}/src/bomb/explosion.cpp
        ${CMAKE_SOURCE_DIR}/src/settings/settings.cpp
        ${CMAKE_SOURCE_DIR}/src/launcher/launcher.cpp
        ${CMAKE_SOURCE_DIR}/src/block/block.cpp
	    ${CMAKE_SOURCE_DIR}/src/event/EventReceiver.cpp
	    ${CMAKE_SOURCE_DIR}/src/player/BomberPlayer.cpp
        ${CMAKE_SOURCE_DIR}/src/player/BomberAI.cpp
        ${CMAKE_SOURCE_DIR}/src/player/PowerUp.cpp
        ${CMAKE_SOURCE_DIR}/src/overlay/overlay.cpp
        ${CMAKE_SOURCE_DIR}/src/figure/figure.cpp
        #[[${CMAKE_SOURCE_DIR}/src/timer/clock.cpp]] src/figure/figure.cpp src/game/pause.cpp)

if (UNIX)
    include_directories(${CMAKE_SOURCE_DIR}/include/Linux)
    set(CMAKE_SKIP_BUILD_RPATH_FALSE)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    set(CMAKE_INSTALL_RPATH "$ENV{HOME}/indie_studio")
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)
    set(IRRLICHT_LIBRARY
        -g
        -g3
        -L./lib/Linux
        -lIrrlicht
        -lGL
        -lGLU
        -lXext
        -lX11
        -lXxf86vm
        -lpthread
    )
    add_executable(bomberman ${SRC})
    add_dependencies(bomberman splash)
    find_package(SFML 2 COMPONENTS audio REQUIRED)
    target_link_libraries(bomberman ${IRRLICHT_LIBRARY} ${SFML_LIBRARIES})
    install(TARGETS bomberman DESTINATION "$ENV{HOME}/indie_studio")
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/media" DESTINATION "$ENV{HOME}/indie_studio")
elseif(WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/include/Windows)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
    add_executable(bomberman ${SRC})
    add_dependencies(bomberman splash)
    target_link_libraries(bomberman ${Irrlicht_LIBRARIES} sfml-audio-d.lib sfml-system-d.lib)
endif(UNIX)
