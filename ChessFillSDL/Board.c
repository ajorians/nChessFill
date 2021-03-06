#ifdef _TINSPIRE
#include <os.h>
#include <libndls.h>
#endif
#include "Board.h"
#include "Replacements.h"

void CreateBoard(struct Board** ppBoard, struct ChessFillLib* chess, struct Metrics* pMetrics )
{
   *ppBoard = malloc(sizeof(struct Board));
   struct Board* pBoard = *ppBoard;
   pBoard->m_Chess = chess;
   pBoard->m_pMetrics = pMetrics;
   pBoard->m_pFont = LoadFont("arial.ttf", NSDL_FONT_THIN, 255/*R*/, 0/*G*/, 0/*B*/, 12);
}

void FreeBoard(struct Board** ppBoard)
{
   struct Board* pBoard = *ppBoard;

   pBoard->m_Chess = NULL;
   pBoard->m_pMetrics = NULL;

   FreeFont(pBoard->m_pFont);

   free(pBoard);
   *ppBoard = NULL;
}

void DrawBoard( struct Board* pBoard, struct SDL_Surface* pScreen )
{
   int kludgeX = 7;
   int kludgeY = 3;//If using graphics can remove this later

   for ( int x = 0; x < 4; x++ )
   {
      for ( int y = 0; y < 4; y++ )
      {
         enum PieceType piece = GetPieceAt( pBoard->m_Chess, x, y );
         int pieceLeft = GetPieceLeft( pBoard->m_pMetrics, x, y );
         int pieceTop = GetPieceTop( pBoard->m_pMetrics, x, y );

         if ( piece == Empty )
         {
            if ( IsValidPiecePlacement( pBoard->m_Chess, x, y ) )
            {
               
               DrawText( pScreen, pBoard->m_pFont, pieceLeft + kludgeX, pieceTop + kludgeY, "X", 0, 255, 255);
            }
            continue;
         }

         char buffer[2];
         switch ( piece )
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

         DrawText( pScreen, pBoard->m_pFont, pieceLeft + kludgeX, pieceTop + kludgeY, buffer, 0, 0, 255 );
      }
   }
}

