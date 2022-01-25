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

enum GameStatus
{
   GameInProgress,
   GameLost,
   GameWon
};

enum PiecePlayedStatus
{
   PieceWasPlayed,
   PieceCurrentlyPlaying,
   PieceNotPlayed
};

struct ChessFillLib
{
   enum PieceType m_Board[4][4];
   enum PieceType m_Pieces[16];
   enum PiecePlayedStatus m_PieceStatus[16];

   enum PieceType m_LastPiece;
   int m_nLastX;
   int m_nLastY;
};

#define CHESSFILLLIB_OK             (0)
#define CHESSFILLLIB_OUTOFMEMORY    (-1)

int ChessFillLibCreate( struct ChessFillLib** api );
int ChessFillLibFree( struct ChessFillLib** api );

void Restart( struct ChessFillLib* pChessFill );
enum PieceType GetLastPiece( struct ChessFillLib* pChessFill );
enum PieceType GetPieceAt( struct ChessFillLib* pChessFill, int x, int y );
int IsValidPiecePlacement( struct ChessFillLib* pChessFill, int x, int y );
int PlaceNextPieceAt( struct ChessFillLib* pChessFill, int x, int y );
int PlacesRemaining( struct ChessFillLib* pChessFill );
enum PiecePlayedStatus GetPiecePlayStatus( struct ChessFillLib* pChessFill, enum PieceType  ePieceType, int index );
enum GameStatus GetGameStatus( struct ChessFillLib* pChessFill );

#endif
