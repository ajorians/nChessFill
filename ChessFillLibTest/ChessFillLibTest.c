#include <ChessFillLib/ChessFillLib.h>
#include <stdio.h>

#define TEST_SUCCEEDED	(0)
#define TEST_FAILED	(1)

int TestConstruction()
{
   struct ChessFillLib* pChessFillLib = NULL;

   if ( CHESSFILLLIB_OK != ChessFillLibCreate( &pChessFillLib ) )
   {
      return TEST_FAILED;
   }

   ChessFillLibFree( &pChessFillLib );
   return TEST_SUCCEEDED;
}

int TestGetLastPiece()
{
   struct ChessFillLib* pChessFillLib = NULL;

   if ( CHESSFILLLIB_OK != ChessFillLibCreate( &pChessFillLib ) )
   {
      return TEST_FAILED;
   }

   enum PieceType ePiece = GetLastPiece( pChessFillLib );
   if( ePiece == Empty )
   {
      return TEST_FAILED;
   }

   ChessFillLibFree( &pChessFillLib );
   return TEST_SUCCEEDED;
}

typedef int (*testfunc)();
testfunc g_Tests[] =
{
   TestConstruction,
   TestGetLastPiece
};

void RunTests()
{
   unsigned i;
   for(i=0; i<sizeof(g_Tests)/sizeof(testfunc); i++) {

      int nRet = g_Tests[i]();
      if( nRet == TEST_SUCCEEDED ) {
         printf("........OK\n");
      } else {
         printf("........FAIL\n");
      }
   }
}

int main()
{
   RunTests();
   return 0;
}