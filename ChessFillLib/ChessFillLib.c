#include "ChessFillLib/ChessFillLib.h"

#include <stdio.h>
#include <stdlib.h>

enum PieceType PickNewCurrentPiece( struct ChessFillLib* pChessFill, int* pIndex )
{
   enum PieceType ePieceType = Empty;
   while ( ePieceType == Empty )
   {
      int index = rand() % 16;

      if ( pChessFill->m_PieceStatus[index] == PieceNotPlayed )
      {
         ePieceType = pChessFill->m_Pieces[index];
         if ( pIndex ) *pIndex = index;
      }
   }

   return ePieceType;
}

int ChessFillLibCreate( struct ChessFillLib** api )
{
   int nSize = sizeof( struct ChessFillLib );
   struct ChessFillLib* pChessFill = malloc(sizeof(struct ChessFillLib));
   if( pChessFill == NULL ){//Out of memory
      return CHESSFILLLIB_OUTOFMEMORY;
   }

   Restart(pChessFill);

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

void Restart( struct ChessFillLib* pChessFill )
{
   pChessFill->m_nLastX = pChessFill->m_nLastY = -1;

   for ( int x = 0; x < 4; x++ )
   {
      for ( int y = 0; y < 4; y++ )
      {
         pChessFill->m_Board[x][y] = Empty;
      }
   }

   enum PieceType initialPieces[16] =
   {
      Pawn,Pawn,Pawn,Pawn,Pawn,Pawn,Pawn,Pawn,
      Rook,Knight,Bishop,Queen,King,Bishop,Knight,Rook
   };

   for ( int i = 0; i < 16; i++ )
   {
      pChessFill->m_Pieces[i] = initialPieces[i];
      pChessFill->m_PieceStatus[i] = PieceNotPlayed;
   }

   PlaceNextPieceAt( pChessFill, rand() % 4, 2 + ( rand() % 2 ) );
}

enum PieceType GetLastPiece( struct ChessFillLib* pChessFill )
{
   return pChessFill->m_LastPiece;
}

enum PieceType GetPieceAt( struct ChessFillLib* pChessFill, int x, int y )
{
   if ( x < 0 || x > 3 || y < 0 || y > 3 )
   {
      return Empty;//TODO: Fix this
   }
   return pChessFill->m_Board[x][y];
}

int AnyPieceBetweenTwoSpots( struct ChessFillLib* pChessFill, int x1, int y1, int x2, int y2 )
{
   while ( x1 != x2 || y1 != y2 )
   {
      int xDirection = x1 < x2 ? 1 : x1 == x2 ? 0 : -1;
      int yDirection = y1 < y2 ? 1 : y1 == y2 ? 0 : -1;

      x1 += xDirection;
      y1 += yDirection;

      if ( GetPieceAt( pChessFill, x1, y1 ) != Empty )
      {
         return 1;
      }
   }

   return 0;
}

int IsValidPiecePlacement( struct ChessFillLib* pChessFill, int x, int y )
{
   if ( GetPieceAt( pChessFill, x, y ) != Empty )
   {
      return 0;
   }

   if ( pChessFill->m_nLastX == -1 && pChessFill->m_nLastY == -1 )
   {
      return 1;
   }

   if ( pChessFill->m_LastPiece == Pawn )
   {
      if ( pChessFill->m_nLastX != x )
      {
         return 0;
      }

      if ( pChessFill->m_nLastY < y )
      {
         return 0;
      }

      if ( pChessFill->m_nLastY >= ( y + 2 ) && pChessFill->m_nLastY == 3 )
      {
         return 0;
      }
   }
   else if ( pChessFill->m_LastPiece == Rook )
   {
      if ( pChessFill->m_nLastX != x && pChessFill->m_nLastY != y )
      {
         return 0;
      }

      if ( AnyPieceBetweenTwoSpots( pChessFill, pChessFill->m_nLastX, pChessFill->m_nLastY, x, y ) == 1 )
      {
         return 0;
      }
   }
   else if ( pChessFill->m_LastPiece == Knight )
   {
      if ( !( ( pChessFill->m_nLastX == x+2 && pChessFill->m_nLastY == y+1 ) ||
              ( pChessFill->m_nLastX == x-2 && pChessFill->m_nLastY == y+1 ) ||
              ( pChessFill->m_nLastX == x+1 && pChessFill->m_nLastY == y+2 ) ||
              ( pChessFill->m_nLastX == x-1 && pChessFill->m_nLastY == y+2 ) ||
              ( pChessFill->m_nLastX == x+2 && pChessFill->m_nLastY == y-1 ) ||
              ( pChessFill->m_nLastX == x-2 && pChessFill->m_nLastY == y-1 ) ||
              ( pChessFill->m_nLastX == x+1 && pChessFill->m_nLastY == y-2 ) ||
              ( pChessFill->m_nLastX == x-1 && pChessFill->m_nLastY == y-2 ) ) )
      {
         return 0;
      }
   }
   else if ( pChessFill->m_LastPiece == Bishop )
   {
      int diffx = pChessFill->m_nLastX - x;
      int diffy = pChessFill->m_nLastY - y;

      if ( diffx != diffy && diffx != -1*diffy )
      {
         return 0;
      }

      if ( AnyPieceBetweenTwoSpots( pChessFill, pChessFill->m_nLastX, pChessFill->m_nLastY, x, y ) == 1 )
      {
         return 0;
      }
   }
   else if ( pChessFill->m_LastPiece == Queen )
   {
      int diffx = pChessFill->m_nLastX - x;
      int diffy = pChessFill->m_nLastY - y;

      if ( diffx != diffy && diffx != -1*diffy 
           && pChessFill->m_nLastX != x && pChessFill->m_nLastY != y)
      {
         return 0;
      }

      if ( AnyPieceBetweenTwoSpots( pChessFill, pChessFill->m_nLastX, pChessFill->m_nLastY, x, y ) == 1 )
      {
         return 0;
      }
   }
   else if ( pChessFill->m_LastPiece == King )
   {
      int diffx = pChessFill->m_nLastX - x;
      int diffy = pChessFill->m_nLastY - y;

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

   for ( int i = 0; i < 16; i++ )
   {
      if ( pChessFill->m_PieceStatus[i] == PieceCurrentlyPlaying )
         pChessFill->m_PieceStatus[i] = PieceWasPlayed;
   }

   int index = 0;
   enum PieceType placingPiece = PickNewCurrentPiece( pChessFill, &index );

   pChessFill->m_PieceStatus[index] = PieceCurrentlyPlaying;

   if ( placingPiece == Pawn && y == 0 )
   {
      placingPiece = Queen;
   }

   pChessFill->m_LastPiece = placingPiece;
   pChessFill->m_Board[x][y] = placingPiece;
   pChessFill->m_nLastX = x;
   pChessFill->m_nLastY = y;

   return 0;
}

int PlacesRemaining( struct ChessFillLib* pChessFill )
{
   int placesRemaining = 0;
   for ( int y=0; y<4; y++ )
   {
      for ( int x = 0; x < 4; x++ )
      {
         if ( GetPieceAt( pChessFill, x, y ) == Empty )
            placesRemaining++;
      }
   }
   return placesRemaining;
}

enum PiecePlayedStatus GetPiecePlayStatus( struct ChessFillLib* pChessFill, enum PieceType ePieceType, int index )
{
   int pieceIndex = 0;
   for ( int i = 0; i < 16; i++ )
   {
      if ( pChessFill->m_Pieces[i] == ePieceType )
      {
         if ( index == pieceIndex )
         {
            return pChessFill->m_PieceStatus[i];
         }

         pieceIndex++;
      }
   }

   return PieceNotPlayed;
}

enum GameStatus GetGameStatus( struct ChessFillLib* pChessFill )
{
   int allSpotsFilled = 1;
   for ( int x = 0; x < 4; x++ )
   {
      for ( int y = 0; y < 4; y++ )
      {
         if ( pChessFill->m_Board[x][y] == Empty )
            allSpotsFilled = 0;
      }
   }

   if ( allSpotsFilled )
      return GameWon;

   int validPiecePlacements = 0;
   for ( int x = 0; x < 4; x++ )
   {
      for ( int y = 0; y < 4; y++ )
      {
         if ( IsValidPiecePlacement( pChessFill, x, y ) == 1 )
         {
            validPiecePlacements = 1;
            break;
         }
      }
   }

   return validPiecePlacements ? GameInProgress : GameLost;
}
