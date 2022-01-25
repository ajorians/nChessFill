#ifdef _TINSPIRE
#include <os.h>
#include <libndls.h>
#endif
#include "Game.h"
#include "Replacements.h"
//#include "YouWinGraphic.h"

void CreateGame(struct Game** ppGame/*, struct Config* pConfig*/, struct SDL_Surface* pScreen)
{
   *ppGame = malloc(sizeof(struct Game));
   struct Game* pGame = *ppGame;
   ChessFillLibCreate(&(pGame->m_Chess));
   //pGame->m_pConfig = pConfig;

#ifdef _TINSPIRE
   pGame->m_pYouWinGraphic = nSDL_LoadImage(image_YouWin);
   SDL_SetColorKey(pGame->m_pYouWinGraphic, SDL_SRCCOLORKEY, SDL_MapRGB(pGame->m_pYouWinGraphic->format, 255, 255, 255));
#endif

   pGame->m_pScreen = pScreen;
   //CreateBackground(&(pGame->m_pBackground), pGame->m_pScreen, pGame->m_pConfig, 1);
   //pGame->m_pMetrics = NULL;
   //CreateMetrics(&pGame->m_pMetrics, pGame->m_Cross);

   //pGame->m_pSelector = NULL;
   //CreateSelector(&pGame->m_pSelector, pGame->m_pScreen, pGame->m_pConfig, pGame->m_pMetrics, pGame->m_Cross);

   pGame->m_bShouldQuit = 0;

   pGame->m_pFont = LoadFont("ARIAL.TTF", NSDL_FONT_THIN, 255/*R*/, 0/*G*/, 0/*B*/, 12);

   RestartGame( pGame );
}

void FreeGame(struct Game** ppGame)
{
   struct Game* pGame = *ppGame;

#ifdef _TINSPIRE
   SDL_FreeSurface(pGame->m_pYouWinGraphic);
#endif
   //FreeSelector(&pGame->m_pSelector);
   //FreeBackground(&pGame->m_pBackground);
   //FreeMetrics(&pGame->m_pMetrics);

   //pGame->m_pConfig = NULL;//Does not own
   pGame->m_pScreen = NULL;//Does not own

   FreeFont(pGame->m_pFont);

   free(pGame);
   *ppGame = NULL;
}

void DrawBoard(struct Game* pGame)
{
   SDL_Rect rectDst;
   rectDst.w = SCREEN_WIDTH;
   rectDst.h = SCREEN_HEIGHT;
   rectDst.x = 0;
   rectDst.y = 0;

   SDL_FillRect(pGame->m_pScreen, &rectDst, SDL_MapRGB(pGame->m_pScreen->format, 255, 255, 255));

   char buffer[25];
   int piecesRemain = PlacesRemaining( pGame->m_Chess );
   IntToA( buffer, 25, piecesRemain );
   int numCharacters = piecesRemain >= 10 ? 2 : 1;
   StringCopy( buffer + numCharacters, 23, " pieces remain" );

   DrawText( pGame->m_pScreen, pGame->m_pFont, 10, 10, buffer, 0, 0, 255);

   for ( int i = 0; i < 8; i++ )
   {
      DrawText( pGame->m_pScreen, pGame->m_pFont, i * 20, 120, "P", 0, 0, 255);
      enum PlayStatus playStatus = GetPiecePlayStatus( pGame->m_Chess, Pawn, i );
      if ( playStatus == PieceWasPlayed )
      {
         SDL_Rect r = { i * 20, 120, 10, 10 };
         SDL_FillRect( pGame->m_pScreen, &r, SDL_MapRGB( pGame->m_pScreen->format, 0, 0, 0 ) );
      }
   }

   DrawText( pGame->m_pScreen, pGame->m_pFont, 0 * 20, 140, "R", 0, 0, 255);
   DrawText( pGame->m_pScreen, pGame->m_pFont, 1 * 20, 140, "k", 0, 0, 255);
   DrawText( pGame->m_pScreen, pGame->m_pFont, 2 * 20, 140, "B", 0, 0, 255);
   DrawText( pGame->m_pScreen, pGame->m_pFont, 3 * 20, 140, "Q", 0, 0, 255);
   DrawText( pGame->m_pScreen, pGame->m_pFont, 4 * 20, 140, "K", 0, 0, 255);
   DrawText( pGame->m_pScreen, pGame->m_pFont, 5 * 20, 140, "B", 0, 0, 255);
   DrawText( pGame->m_pScreen, pGame->m_pFont, 6 * 20, 140, "k", 0, 0, 255);
   DrawText( pGame->m_pScreen, pGame->m_pFont, 7 * 20, 140, "R", 0, 0, 255);

   //DrawBackground(pGame->m_pBackground);
#if 1
   for ( int x = 0; x < 4; x++ )
   {
      for ( int y = 0; y < 4; y++ )
      {
         enum PieceType piece = GetPieceAt( pGame->m_Chess, x, y );
         if ( piece == Empty )
         {
            if ( IsValidPiecePlacement( pGame->m_Chess, x, y ) )
            {
               DrawText( pGame->m_pScreen, pGame->m_pFont, x * 20, y * 20 + 25, "X", 0, 255, 255);
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
         

         DrawText( pGame->m_pScreen, pGame->m_pFont, x * 20, y * 20 + 25, buffer, 0, 0, 255 );
      }
   }

   DrawText( pGame->m_pScreen, pGame->m_pFont, pGame->m_nX * 20, pGame->m_nY * 20 + 25, "Z", 255, 0, 255 );

   //Draw selector
   //DrawSelector(pGame->m_pSelector);
   
   if ( pGame->m_eGameStatus == GameLost )
   {
      DrawText( pGame->m_pScreen, pGame->m_pFont, 100, 100, "Game over.  Press key to try again", 255, 0, 255 );
   }
   else if( pGame->m_eGameStatus == GameWon )
   {
      DrawText( pGame->m_pScreen, pGame->m_pFont, 100, 100, "You Won!", 255, 0, 255 );
      /*SDL_Rect rectYouWin;
      rectYouWin.x = (SCREEN_WIDTH - pGame->m_pYouWinGraphic->w)/2;
      rectYouWin.y = (SCREEN_HEIGHT - pGame->m_pYouWinGraphic->h)/2;
      rectYouWin.w = pGame->m_pYouWinGraphic->w;
      rectYouWin.h = pGame->m_pYouWinGraphic->h;
      SDL_BlitSurface(pGame->m_pYouWinGraphic, NULL, pGame->m_pScreen, &rectYouWin);*/
   }
#endif
   
   SDL_UpdateRect(pGame->m_pScreen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

int GamePollEvents(struct Game* pGame)
{
   SDL_Event event;
   while( SDL_PollEvent( &event ) ) {
      switch( event.type ) {
         case SDL_KEYDOWN:
            switch( event.key.keysym.sym) {
              case SDLK_ESCAPE:
                  return 0;
                  break;

               case SDLK_UP:
               case SDLK_8:
		  if( pGame->m_eGameStatus == GameInProgress ) {
           if ( pGame->m_nY > 0 )
           {
              pGame->m_nY--;
           }
                     //Move(pGame->m_pSelector, Up);
		  }
                  break;

	       case SDLK_DOWN:
               case SDLK_2:
		  if( pGame->m_eGameStatus == GameInProgress ) {
           if ( pGame->m_nY < 3 )
           {
              pGame->m_nY++;
           }
                     //Move(pGame->m_pSelector, Down);
		  }
                  break;

               case SDLK_LEFT:
               case SDLK_4:
		  if( pGame->m_eGameStatus == GameInProgress ) {
           if ( pGame->m_nX > 0 )
           {
              pGame->m_nX--;
           }
                     //Move(pGame->m_pSelector, Left);
		  }
                  break;

               case SDLK_RIGHT:
               case SDLK_6:
		  if( pGame->m_eGameStatus == GameInProgress ) {
           if ( pGame->m_nX < 3 )
           {
              pGame->m_nX++;
           }
                     //Move(pGame->m_pSelector, Right);
		  }
                  break;

               case SDLK_RETURN:
               case SDLK_LCTRL:
               case SDLK_RCTRL:
		  if( pGame->m_eGameStatus == GameInProgress ) {
           PlaceNextPieceAt( pGame->m_Chess, pGame->m_nX, pGame->m_nY );

		     pGame->m_eGameStatus = GetGameStatus(pGame->m_Chess);
		  }
        else
        {
           RestartGame( pGame );
        }
                  break;

               default:
                  break;
            }
          default:
             break;
      }
   }
   return 1;
}

int GameLoop(struct Game* pGame)
{
   if( GamePollEvents(pGame) == 0 )
      return 0;

   DrawBoard(pGame);

   SDL_Delay(30);

   return 1;
}

void RestartGame( struct Game* pGame )
{
   Restart( pGame->m_Chess );
   pGame->m_eGameStatus = GetGameStatus( pGame->m_Chess );
   pGame->m_nX = 0;
   pGame->m_nY = 0;
}

int GameShouldQuit(struct Game* pGame)
{
   return pGame->m_bShouldQuit;
}

