cmake_minimum_required(VERSION 3.16)
project(WWPuzzleReplicate)

set(CMAKE_CXX_STANDARD 20)

# Add your source files
set(SOURCES
    main.cpp
    Cards.cpp
    GameLogic.cpp
)

# Add the executable
add_executable(WWPuzzleReplicate ${SOURCES})

# Link the GDI+ library
target_link_libraries(WWPuzzleReplicate PRIVATE gdiplus)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")