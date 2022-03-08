#ifdef _TINSPIRE
#include <os.h>
#include <libndls.h>
#endif
#include "Board.h"
#include "Replacements.h"

void CreateBoard(struct Board** ppBoard, struct ChessFillLib* chess )
{
   *ppBoard = malloc(sizeof(struct Board));
   struct Board* pBoard = *ppBoard;
   pBoard->m_Chess = chess;
   pBoard->m_pFont = LoadFont("ARIAL.TTF", NSDL_FONT_THIN, 255/*R*/, 0/*G*/, 0/*B*/, 12);
}

void FreeBoard(struct Board** ppBoard)
{
   struct Board* pBoard = *ppBoard;

   pBoard->m_Chess = NULL;

   FreeFont(pBoard->m_pFont);

   free(pBoard);
   *ppBoard = NULL;
}

void DrawBoard( struct Board* pBoard, struct SDL_Surface* pScreen )
{
   for ( int x = 0; x < 4; x++ )
   {
      for ( int y = 0; y < 4; y++ )
      {
         enum PieceType piece = GetPieceAt( pBoard->m_Chess, x, y );
         if ( piece == Empty )
         {
            if ( IsValidPiecePlacement( pBoard->m_Chess, x, y ) )
            {
               DrawText( pScreen, pBoard->m_pFont, x * 20, y * 20 + 25, "X", 0, 255, 255);
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


         DrawText( pScreen, pBoard->m_pFont, x * 20, y * 20 + 25, buffer, 0, 0, 255 );
      }
   }
}

