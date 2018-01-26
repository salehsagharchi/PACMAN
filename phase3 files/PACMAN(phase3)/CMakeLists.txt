cmake_minimum_required(VERSION 3.8.2)
project(PACMAN_phase3_)
set(CMAKE_C_STANDARD 99)

set(SDL2_GFX_INCLUDE_DIR "E:/sdl2/sdl2-gfx-include")
set(SDL2_GFX_LibDir "E:/sdl2/sdl2-gfx-lib")
set(SDL2_Flags "-mwindows -Wl,--no-undefined -static-libgcc")
set(SDL2_Includes "E:/sdl2/sdl2-include")
set(SDL2_LibDir   "E:/sdl2/sdl2-lib")
add_library(SDL2     STATIC IMPORTED)
add_library(SDL2main STATIC IMPORTED)
add_library(SDL2_GFX STATIC IMPORTED)
set_property(TARGET SDL2     PROPERTY IMPORTED_LOCATION "${SDL2_LibDir}/libSDL2.a")
set_property(TARGET SDL2main PROPERTY IMPORTED_LOCATION "${SDL2_LibDir}/libSDL2main.a")
set_property(TARGET SDL2_GFX PROPERTY IMPORTED_LOCATION "${SDL2_GFX_LibDir}/libsdl-gfx.a")
set(SDL2_Libs SDL2 SDL2main SDL2_GFX m dinput8 dxguid dxerr8 user32 gdi32 winmm imm32 ole32 oleaut32 shell32 version uuid)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ${SDL2_Flags}")




set(SOURCE src/main.c src/game.c src/physics.c)
add_executable(PACMAN_phase3_ ${SOURCE})

include_directories(src)

include_directories(${SDL2_Includes} ${SDL2_GFX_INCLUDE_DIR})



target_link_libraries(PACMAN_phase3_ ${SDL2_Libs})

