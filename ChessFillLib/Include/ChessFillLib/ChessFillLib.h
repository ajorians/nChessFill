#ifndef CHESSFILLLIB
#define CHESSFILLLIB

enum PieceType
{
   Empty = 0,
   Pawn,
   Rook,
   Knight,
   Bishop,
   Queen,
   King
};

struct ChessFillLib
{
   enum PieceType m_Board[4][4];
   int m_PiecesRemaining[7];

   enum PieceType m_CurrentPiece;
   int m_nCurrentX;
   int m_nCurrentY;
};

#define CHESSFILLLIB_OK             (0)
#define CHESSFILLLIB_OUTOFMEMORY    (-1)

int ChessFillLibCreate( struct ChessFillLib** api );
int ChessFillLibFree( struct ChessFillLib** api );

enum PieceType GetCurrentPiece( struct ChessFillLib* pChessFill );
enum PieceType GetPieceAt( struct ChessFillLib* pChessFill, int x, int y );
int IsValidPiecePlacement( struct ChessFillLib* pChessFill, int x, int y );
int PlaceNextPieceAt( struct ChessFillLib* pChessFill, int x, int y );
int PlacesRemaining( struct ChessFillLib* pChessFill );

#endif
