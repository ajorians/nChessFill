#ifdef _TINSPIRE
#include <os.h>
#include <libndls.h>
#endif
#include "UsedPieceIndicator.h"
#include "Replacements.h"

void CreateUsedPieceIndicator(struct UsedPieceIndicator** ppUsedPieceIndicator, struct ChessFillLib* chess, struct Metrics* pMetrics)
{
   *ppUsedPieceIndicator = malloc(sizeof(struct UsedPieceIndicator));
   struct UsedPieceIndicator* pUsedPieceIndicator = *ppUsedPieceIndicator;
   pUsedPieceIndicator->m_Chess = chess;
   pUsedPieceIndicator->m_pMetrics = pMetrics;
   pUsedPieceIndicator->m_pFont = LoadFont("ARIAL.TTF", NSDL_FONT_THIN, 255/*R*/, 0/*G*/, 0/*B*/, 12);
}

void FreeUsedPieceIndicator(struct UsedPieceIndicator** ppUsedPieceIndicator)
{
   struct UsedPieceIndicator* pUsedPieceIndicator = *ppUsedPieceIndicator;

   pUsedPieceIndicator->m_Chess = NULL;
   pUsedPieceIndicator->m_pMetrics = NULL;

   FreeFont(pUsedPieceIndicator->m_pFont);

   free(pUsedPieceIndicator);
   *ppUsedPieceIndicator = NULL;
}

void DrawUsedPieceIndicator( struct UsedPieceIndicator* pUsedPieceIndicator, struct SDL_Surface* pScreen )
{
   int usedPieceIndicatorY = GetUsedPieceIndicatorY( pUsedPieceIndicator->m_pMetrics );

   for ( int i = 0; i < 8; i++ )
   {
      DrawText( pScreen, pUsedPieceIndicator->m_pFont, i * 20, usedPieceIndicatorY, "P", 0, 0, 255);
      enum PlayStatus playStatus = GetPiecePlayStatus( pUsedPieceIndicator->m_Chess, Pawn, i );
      if ( playStatus == PieceWasPlayed )
      {
         SDL_Rect r = { i * 20, 120, 10, 10 };
         SDL_FillRect( pScreen, &r, SDL_MapRGB( pScreen->format, 0, 0, 0 ) );
      }
   }

   int secondRowUsedPieceIndicator = usedPieceIndicatorY + 20;
   DrawText( pScreen, pUsedPieceIndicator->m_pFont, 0 * 20, secondRowUsedPieceIndicator, "R", 0, 0, 255);
   DrawText( pScreen, pUsedPieceIndicator->m_pFont, 1 * 20, secondRowUsedPieceIndicator, "k", 0, 0, 255);
   DrawText( pScreen, pUsedPieceIndicator->m_pFont, 2 * 20, secondRowUsedPieceIndicator, "B", 0, 0, 255);
   DrawText( pScreen, pUsedPieceIndicator->m_pFont, 3 * 20, secondRowUsedPieceIndicator, "Q", 0, 0, 255);
   DrawText( pScreen, pUsedPieceIndicator->m_pFont, 4 * 20, secondRowUsedPieceIndicator, "K", 0, 0, 255);
   DrawText( pScreen, pUsedPieceIndicator->m_pFont, 5 * 20, secondRowUsedPieceIndicator, "B", 0, 0, 255);
   DrawText( pScreen, pUsedPieceIndicator->m_pFont, 6 * 20, secondRowUsedPieceIndicator, "k", 0, 0, 255);
   DrawText( pScreen, pUsedPieceIndicator->m_pFont, 7 * 20, secondRowUsedPieceIndicator, "R", 0, 0, 255);
}

