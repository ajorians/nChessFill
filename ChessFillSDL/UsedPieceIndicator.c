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
   pUsedPieceIndicator->m_pFont = LoadFont("arial.ttf", NSDL_FONT_THIN, 255/*R*/, 0/*G*/, 0/*B*/, 12);
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

void DrawPieceUsed( struct UsedPieceIndicator* pUsedPieceIndicator, struct SDL_Surface* pScreen, int row, int col )
{
   int usedPieceIndicatorX = GetUsedPieceIndicatorX( pUsedPieceIndicator->m_pMetrics );
   int usedPieceIndicatorY = GetUsedPieceIndicatorY( pUsedPieceIndicator->m_pMetrics );
   
   int piecePosX = usedPieceIndicatorX + col * 20;
   int piecePosY = usedPieceIndicatorY + row * 20;

   SDL_Rect r = { piecePosX, piecePosY, 10, 10 };
   SDL_FillRect( pScreen, &r, SDL_MapRGB( pScreen->format, 0, 0, 0 ) );
}

void DrawPiece( struct UsedPieceIndicator* pUsedPieceIndicator, struct SDL_Surface* pScreen, enum PieceType pieceType, int pieceIndex, int row, int col )
{
   int usedPieceIndicatorX = GetUsedPieceIndicatorX( pUsedPieceIndicator->m_pMetrics );
   int usedPieceIndicatorY = GetUsedPieceIndicatorY( pUsedPieceIndicator->m_pMetrics );

   int piecePosX = usedPieceIndicatorX + col * 20;
   int piecePosY = usedPieceIndicatorY + row * 20;

   char buffer[2];
   switch ( pieceType )
   {
      case Empty:
         strcpy( buffer, "X" );
         break;
      case Pawn:
         strcpy( buffer, "P" );
         break;
      case Rook:
         strcpy( buffer, "R" );
         break;
      case Knight:
         strcpy( buffer, "k" );
         break;
      case Bishop:
         strcpy( buffer, "B" );
         break;
      case Queen:
         strcpy( buffer, "Q" );
         break;
      case King:
         strcpy( buffer, "K" );
         break;
   }

   DrawText( pScreen, pUsedPieceIndicator->m_pFont, piecePosX, piecePosY, buffer, 0, 0, 255);

    enum PiecePlayedStatus playStatus = GetPiecePlayStatus( pUsedPieceIndicator->m_Chess, pieceType, pieceIndex );
   if ( playStatus == PieceWasPlayed )
   {
      DrawPieceUsed( pUsedPieceIndicator, pScreen, row, col );
   }
}

void DrawUsedPieceIndicator( struct UsedPieceIndicator* pUsedPieceIndicator, struct SDL_Surface* pScreen )
{
   for ( int i = 0; i < 8; i++ )
   {
      DrawPiece( pUsedPieceIndicator, pScreen, Pawn, i, 0, i );
   }

   DrawPiece( pUsedPieceIndicator, pScreen, Rook, 0, 1, 0 );
   DrawPiece( pUsedPieceIndicator, pScreen, Knight, 0, 1, 1 );
   DrawPiece( pUsedPieceIndicator, pScreen, Bishop, 0, 1, 2 );
   DrawPiece( pUsedPieceIndicator, pScreen, Queen, 0, 1, 3 );
   DrawPiece( pUsedPieceIndicator, pScreen, King, 0, 1, 4 );
   DrawPiece( pUsedPieceIndicator, pScreen, Bishop, 1, 1, 5 );
   DrawPiece( pUsedPieceIndicator, pScreen, Knight, 1, 1, 6 );
   DrawPiece( pUsedPieceIndicator, pScreen, Rook, 1, 1, 7 );
}

