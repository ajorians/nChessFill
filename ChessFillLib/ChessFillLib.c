#include "ChessFillLib/ChessFillLib.h"

#include <stdio.h>
#include <stdlib.h>

int ChessFillLibCreate( struct ChessFillLib** api )
{
   int nSize = sizeof( struct ChessFillLib );
   struct ChessFillLib* pChessFill = malloc(sizeof(struct ChessFillLib));
   if( pChessFill == NULL ){//Out of memory
      return CHESSFILLLIB_OUTOFMEMORY;
   }

   for ( int x = 0; x < 4; x++ )
   {
      for ( int y = 0; y < 4; y++ )
      {
         pChessFill->m_Board[x][y] = Empty;
      }
   }

   pChessFill->m_PiecesRemaining[Pawn] = 8;
   pChessFill->m_PiecesRemaining[Rook] = 2;
   pChessFill->m_PiecesRemaining[Knight] = 2;
   pChessFill->m_PiecesRemaining[Bishop] = 2;
   pChessFill->m_PiecesRemaining[Queen] = 1;
   pChessFill->m_PiecesRemaining[King] = 1;

   *api = pChessFill;
   return CHESSFILLLIB_OK;
}

int ChessFillLibFree( struct ChessFillLib** api )
{
   struct ChessFillLib* pChessFill = *api;
   free( pChessFill );
   *api = NULL;

   return CHESSFILLLIB_OK;
}

enum PieceType GetCurrentPiece( struct ChessFillLib* api )
{
   return api->m_CurrentPiece;
}

enum PieceType GetPieceAt( struct ChessFillLib* api, int x, int y )
{
   return api->m_Board[x][y];
}

int IsValidPiecePlacement( struct ChessFillLib* api, int x, int y )
{
   return 0;
}

int PlaceNextPieceAt( struct ChessFillLib* api, int x, int y )
{
   if ( IsValidPiecePlacement( api, x, y ) == 0 )
   {
      return 0;
   }

   api->m_Board[x][y] = api->m_CurrentPiece;
   //Pick new current piece

   return 0;
}
