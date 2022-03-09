PROJECT(nChessFill)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

FILE(GLOB HEADERS *.h)
FILE(GLOB SOURCE_FILES *.c)

SET(HEADERS
        Board.h
        Font.h
        Game.h
        Help.h
        MainMenu.h
        Metrics.h
        Replacements.h
        Selector.h
        UsedPieceIndicator.h)
SET(SOURCE_FILES
        Board.c
        Font.c
        Game.c
        Help.c
        MainMenu.c
        Metrics.c
        Replacements.c
        Selector.c
        UsedPieceIndicator.c
        main.c)

ADD_EXECUTABLE(nChessFill ${SOURCE_FILES} ${HEADERS} )

FIND_PACKAGE(SDL REQUIRED)
FIND_PACKAGE(SDL_gfx REQUIRED)
FIND_PACKAGE(SDL_ttf REQUIRED)

TARGET_LINK_LIBRARIES(nChessFill ChessFillLib ${SDL_LIBRARY} ${SDLGFX_LIBRARY} ${SDLTTF_LIBRARY})
INCLUDE_DIRECTORIES(nChessFill ../ChessFillLib/Include ${SDL_INCLUDE_DIRS})