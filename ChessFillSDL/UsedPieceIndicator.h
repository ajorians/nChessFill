#ifndef USEDPIECEINDICATOR_H
#define USEDPIECEINDICATOR_H

#include <ChessFillLib/ChessFillLib.h>
#include <SDL/SDL.h>
#include "Font.h"
#include "Metrics.h"

struct UsedPieceIndicator
{
   struct ChessFillLib* m_Chess;//Does not own
   struct Metrics* m_pMetrics;//Does not own
   Font *m_pFont;
};

void CreateUsedPieceIndicator(struct UsedPieceIndicator** ppUsedPieceIndicator, struct ChessFillLib* chess, struct Metrics* pMetrics );
void FreeUsedPieceIndicator(struct UsedPieceIndicator** ppUsedPieceIndicator);
void DrawUsedPieceIndicator( struct UsedPieceIndicator* pUsedPieceIndicator, struct SDL_Surface* pScreen );

#endif
