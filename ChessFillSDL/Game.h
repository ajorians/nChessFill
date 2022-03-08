#ifndef GAME_H
#define GAME_H

#include <ChessFillLib/ChessFillLib.h>
#include <SDL/SDL.h>
//#include "Config.h"
//#include "Metrics.h"
//#include "Piece.h"
//#include "Selector.h"
#include "UsedPieceIndicator.h"
#include "Font.h"

struct Game
{
   struct ChessFillLib* m_Chess;
   //struct Config* m_pConfig;//Does not own
   enum GameStatus m_eGameStatus;
   //struct Metrics* m_pMetrics;
   //struct Piece* m_apPieces;
   //struct Selector* m_pSelector;
   struct UsedPieceIndicator* m_pUsedPieceIndicator;
   int m_bShouldQuit;
   //struct SDL_Surface* m_pYouWinGraphic;
   struct SDL_Surface* m_pScreen;//Does not own
   //struct Background* m_pBackground;
   Font *m_pFont;
   int m_nX;
   int m_nY;
};

void CreateGame(struct Game** ppGame/*, struct Config* pConfig*/, struct SDL_Surface* pScreen);
void FreeGame(struct Game** ppGame);
int GameLoop(struct Game* pGame);
void RestartGame( struct Game* pGame );
int GameShouldQuit(struct Game* pMenu);

#endif
