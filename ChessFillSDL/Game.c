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
   CreateMetrics( &( pGame->m_pMetrics ) );
   CreateUsedPieceIndicator( &( pGame->m_pUsedPieceIndicator ), pGame->m_Chess, pGame->m_pMetrics );
   CreateBoard( &( pGame->m_pBoard ), pGame->m_Chess, pGame->m_pMetrics );
   //pGame->m_pConfig = pConfig;

#ifdef _TINSPIRE
   pGame->m_pYouWinGraphic = nSDL_LoadImage(image_YouWin);
   SDL_SetColorKey(pGame->m_pYouWinGraphic, SDL_SRCCOLORKEY, SDL_MapRGB(pGame->m_pYouWinGraphic->format, 255, 255, 255));
#endif

   pGame->m_pScreen = pScreen;
   //CreateBackground(&(pGame->m_pBackground), pGame->m_pScreen, pGame->m_pConfig, 1);

   CreateSelector(&pGame->m_pSelector, pGame->m_pScreen,/* pGame->m_pConfig,*/ pGame->m_pMetrics, pGame->m_Chess);

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

   //FreeBackground(&pGame->m_pBackground);
   FreeUsedPieceIndicator( &pGame->m_pUsedPieceIndicator );
   FreeSelector(&pGame->m_pSelector);
   FreeBoard( &pGame->m_pBoard );
   FreeMetrics(&pGame->m_pMetrics);

   //pGame->m_pConfig = NULL;//Does not own
   pGame->m_pScreen = NULL;//Does not own

   FreeFont(pGame->m_pFont);

   free(pGame);
   *ppGame = NULL;
}

void DrawGameBoard(struct Game* pGame)
{
   SDL_Rect rectDst;
   rectDst.w = SCREEN_WIDTH;
   rectDst.h = SCREEN_HEIGHT;
   rectDst.x = 0;
   rectDst.y = 0;

   SDL_FillRect(pGame->m_pScreen, &rectDst, SDL_MapRGB(pGame->m_pScreen->format, 255, 255, 255));
   //DrawBackground(pGame->m_pBackground);

   char buffer[25];
   int piecesRemain = PlacesRemaining( pGame->m_Chess );
   IntToA( buffer, 25, piecesRemain );
   int numCharacters = piecesRemain >= 10 ? 2 : 1;
   StringCopy( buffer + numCharacters, 23, " pieces remain" );

   DrawText( pGame->m_pScreen, pGame->m_pFont, GetRemainLabelX( pGame->m_pMetrics ), 10, buffer, 0, 0, 255);

   DrawUsedPieceIndicator( pGame->m_pUsedPieceIndicator, pGame->m_pScreen );
   DrawBoard( pGame->m_pBoard, pGame->m_pScreen );

   //Draw selector
   DrawSelector(pGame->m_pSelector);
   
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
           Move(pGame->m_pSelector, Up);
		  }
                  break;

	       case SDLK_DOWN:
               case SDLK_2:
		  if( pGame->m_eGameStatus == GameInProgress ) {
           Move(pGame->m_pSelector, Down);
		  }
                  break;

               case SDLK_LEFT:
               case SDLK_4:
		  if( pGame->m_eGameStatus == GameInProgress ) {
           Move(pGame->m_pSelector, Left);
		  }
                  break;

               case SDLK_RIGHT:
               case SDLK_6:
		  if( pGame->m_eGameStatus == GameInProgress ) {
           Move(pGame->m_pSelector, Right);
		  }
                  break;

               case SDLK_RETURN:
               case SDLK_LCTRL:
               case SDLK_RCTRL:
		  if( pGame->m_eGameStatus == GameInProgress ) {
           PlaceNextPieceAt( pGame->m_Chess, GetCurrentX( pGame->m_pSelector ), GetCurrentY( pGame->m_pSelector ) );

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

   DrawGameBoard(pGame);

   SDL_Delay(30);

   return 1;
}

void RestartGame( struct Game* pGame )
{
   Restart( pGame->m_Chess );
   pGame->m_eGameStatus = GetGameStatus( pGame->m_Chess );
   ResetSelectorPosition( pGame->m_pSelector );
}

int GameShouldQuit(struct Game* pGame)
{
   return pGame->m_bShouldQuit;
}

