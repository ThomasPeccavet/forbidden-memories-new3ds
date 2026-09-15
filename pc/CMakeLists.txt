cmake_minimum_required(VERSION 3.20)
project(forbidden_memories_fr C CXX)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(PSXRECOMP_ROOT "" CACHE PATH "Pinned psxrecomp checkout")
set(FM_GENERATED_DIR "" CACHE PATH "French generated directory from bootstrap_pc.py")
set(FM_GAME_CONFIG "" CACHE FILEPATH "French game.toml from bootstrap_pc.py")
if(NOT EXISTS "${PSXRECOMP_ROOT}/runtime/runtime.cmake")
  message(FATAL_ERROR "Set PSXRECOMP_ROOT to the pinned framework checkout")
endif()
file(GLOB FM_SHARDS CONFIGURE_DEPENDS "${FM_GENERATED_DIR}/SLES_039.48_full_*.c")
if(NOT FM_SHARDS OR NOT EXISTS "${FM_GENERATED_DIR}/SLES_039.48_dispatch.c")
  message(FATAL_ERROR "Run tools/bootstrap_pc.py --exe first, then set FM_GENERATED_DIR")
endif()
if(NOT EXISTS "${FM_GAME_CONFIG}")
  message(FATAL_ERROR "Set FM_GAME_CONFIG to the generated game.toml")
endif()
if(NOT EXISTS "${PSXRECOMP_ROOT}/lib/recomp-net/include/recomp_net/auth.h")
  message(FATAL_ERROR "Run git -C <framework> submodule update --init lib/recomp-net; the pinned main.cpp includes auth.h even with netplay disabled")
endif()
set(PSX_RECOMP_UI OFF CACHE BOOL "No launcher for the French diagnostic build")
set(PSX_ENABLE_VULKAN OFF CACHE BOOL "Use software/OpenGL during initial bring-up")
set(PSX_REWIND OFF CACHE BOOL "No optional rewind backend for initial bring-up")
include("${PSXRECOMP_ROOT}/runtime/runtime.cmake")
psxrecomp_add_runtime_target(fm-pc
  GAME_GENERATED_FULL_C ${FM_SHARDS}
  GAME_GENERATED_DISPATCH_C "${FM_GENERATED_DIR}/SLES_039.48_dispatch.c"
  DEFAULT_GAME_CONFIG_PATH "${FM_GAME_CONFIG}"
  WINDOW_TITLE "Forbidden Memories FR - experimental PC runtime"
  EXE_NAME "fm-pc"
  PRELOADED_MODS_DIR NONE
)
# Required by an unconditional include in the pinned main.cpp. This does
# not enable netplay or link its implementation.
target_include_directories(fm-pc PRIVATE "${PSXRECOMP_ROOT}/lib/recomp-net/include")
