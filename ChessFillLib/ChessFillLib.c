#include "ChessFillLib/ChessFillLib.h"

#include <stdio.h>
#include <stdlib.h>

void PickNewCurrentPiece( struct ChessFillLib* pChessFill )
{
   while ( 1 )
   {
      int index = rand() % 16;

      enum PieceType ePieceType = Empty;
      if ( index >= 0 && index < 8 )
      {
         ePieceType = Pawn;
      }
      else if ( index >= 8 && index < 10 )
      {
         ePieceType = Rook;
      }
      else if ( index >= 10 && index < 12 )
      {
         ePieceType = Knight;
      }
      else if ( index >= 12 && index < 14 )
      {
         ePieceType = Bishop;
      }
      else if ( index >= 14 && index < 15 )
      {
         ePieceType = Queen;
      }
      else if ( index >= 15 )
      {
         ePieceType = King;
      }

      if ( pChessFill->m_PiecesRemaining[ePieceType] <= 0 )
         continue;

      pChessFill->m_CurrentPiece = ePieceType;
      pChessFill->m_PiecesRemaining[ePieceType]--;
      break;
   }
}

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

   PickNewCurrentPiece( pChessFill );

   PlaceNextPieceAt( pChessFill, rand() % 4, 2 + ( rand() % 2 ) );

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

enum PieceType GetCurrentPiece( struct ChessFillLib* pChessFill )
{
   return pChessFill->m_CurrentPiece;
}

enum PieceType GetPieceAt( struct ChessFillLib* pChessFill, int x, int y )
{
   return pChessFill->m_Board[x][y];
}

int IsValidPiecePlacement( struct ChessFillLib* pChessFill, int x, int y )
{
   if ( GetPieceAt( pChessFill, x, y ) != Empty )
   {
      return 0;
   }

   if ( pChessFill->m_CurrentPiece == Pawn )
   {
      if ( pChessFill->m_nCurrentX != x )
      {
         return 0;
      }

      if ( pChessFill->m_nCurrentY < y )
      {
         return 0;
      }

      if ( pChessFill->m_nCurrentY >= ( y + 2 ) )
      {
         return 0;
      }
   }
   else if ( pChessFill->m_CurrentPiece == Rook )
   {
      if ( pChessFill->m_nCurrentX != x && pChessFill->m_nCurrentY != y )
      {
         return 0;
      }
   }
   else if ( pChessFill->m_CurrentPiece == Knight )
   {
      if ( !( pChessFill->m_nCurrentX == x+2 && pChessFill->m_nCurrentY == y+1 ) ||
            ( pChessFill->m_nCurrentX == x-2 && pChessFill->m_nCurrentY == y+1 ) ||
            ( pChessFill->m_nCurrentX == x+1 && pChessFill->m_nCurrentY == y+2 ) ||
            ( pChessFill->m_nCurrentX == x-1 && pChessFill->m_nCurrentY == y+2 ) ||
            ( pChessFill->m_nCurrentX == x+2 && pChessFill->m_nCurrentY == y-1 ) ||
            ( pChessFill->m_nCurrentX == x-2 && pChessFill->m_nCurrentY == y-1 ) ||
            ( pChessFill->m_nCurrentX == x+1 && pChessFill->m_nCurrentY == y-2 ) ||
            ( pChessFill->m_nCurrentX == x-1 && pChessFill->m_nCurrentY == y-2 ) )
      {
         return 0;
      }
   }
   else if ( pChessFill->m_CurrentPiece == Bishop )
   {
      int diffx = pChessFill->m_nCurrentX - x;
      int diffy = pChessFill->m_nCurrentY - y;

      if ( diffx != diffy )//TODO: Fix
      {
         return 0;
      }
   }
   else if ( pChessFill->m_CurrentPiece == Queen )
   {
      
   }
   else if ( pChessFill->m_CurrentPiece == King )
   {
      int diffx = pChessFill->m_nCurrentX - x;
      int diffy = pChessFill->m_nCurrentY - y;

      if ( diffx > 1 || diffx < -1 || diffy > 1 || diffy < -1 )
      {
         return 0;
      }
   }

   return 1;
}

int PlaceNextPieceAt( struct ChessFillLib* pChessFill, int x, int y )
{
   if ( IsValidPiecePlacement( pChessFill, x, y ) == 0 )
   {
      return 0;
   }

   pChessFill->m_Board[x][y] = pChessFill->m_CurrentPiece;
   //Pick new current piece
   PickNewCurrentPiece( pChessFill );

   return 0;
}

int PlacesRemaining( struct ChessFillLib* pChessFill )
{
   return pChessFill->m_PiecesRemaining[Pawn] +
      pChessFill->m_PiecesRemaining[Rook] +
      pChessFill->m_PiecesRemaining[Knight] +
      pChessFill->m_PiecesRemaining[Bishop] +
      pChessFill->m_PiecesRemaining[Queen] +
      pChessFill->m_PiecesRemaining[King];
}
