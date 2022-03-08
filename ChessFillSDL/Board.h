#ifndef BOARD_H
#define BOARD_H

#include <ChessFillLib/ChessFillLib.h>
#include <SDL/SDL.h>
#include "Font.h"

struct Board
{
   struct ChessFillLib* m_Chess;//Does not own
   Font *m_pFont;
};

void CreateBoard(struct Board** ppBoard, struct ChessFillLib* chess );
void FreeBoard(struct Board** ppBoard);
void DrawBoard( struct Board* pBoard, struct SDL_Surface* pScreen );

#endif
