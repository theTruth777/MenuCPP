#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

class EngineMenu {
    public:

        EngineMenu(SDL_Renderer *windowsplashFontRenderer, SDL_Window *window){
            TTF_Init();
            splashFontRenderer = windowsplashFontRenderer;
            windowScreen = window;
            splashScreenTextBlink = 0;
            SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        }

        void initSplashScreen(const char *displayName, const char *fontFamily, const char *backgroundImg = NULL){
           prepareSplashScreen(displayName, fontFamily);

            if(backgroundImg != NULL){

                prepareSplashScreenBackgroundImage(backgroundImg);

            }
           
        }

        void displaySplashScreen(){
            renderSplashScreen();
        }

        void quitSplashScreen(){
            destroySplashScreen();
        }

    private:
        SDL_Window *windowScreen;
        SDL_Renderer *splashFontRenderer;
        SDL_Texture *splashFontTexture;
        SDL_Surface *splashFontSurface;

        TTF_Font *font;
        const char *splashText;

        int windowHeight;
        int windowWidth;

        int splashScreenTextBlink;


        void prepareSplashScreen(const char *displayName, const char *fontFamily){
            font = TTF_OpenFont(fontFamily, 25);
            splashText = displayName;
        }

        void renderSplashScreen(){
            int textWidth = 0;
            int textHeight = 0;

            SDL_Color color = {255, 255, 255};
            splashFontSurface = TTF_RenderText_Solid(font, splashText, color);
            splashFontTexture = SDL_CreateTextureFromSurface(splashFontRenderer, splashFontSurface);

            splashScreenTextBlink++;
            if(splashScreenTextBlink == 100){

                splashScreenTextBlink = 0;
                
            }

            //Handle splash screen text blinkg effect
            if(splashScreenTextBlink < 50){

                SDL_QueryTexture(splashFontTexture, NULL, NULL, &textWidth, &textHeight);

                const int devideScreenWidth = windowWidth / 2;
                const int deviceText = textWidth / 2;
                const int dediceScreenHeight = windowHeight / 2;

                SDL_Rect fontStruct = {devideScreenWidth - deviceText, dediceScreenHeight, textWidth, textHeight };                
                SDL_RenderCopy(splashFontRenderer, splashFontTexture, NULL, &fontStruct);

            }else{

                splashFontTexture = NULL;
                splashFontSurface = NULL;

            }

        }

        void destroySplashScreen(){

            SDL_DestroyTexture(splashFontTexture);
            SDL_FreeSurface(splashFontSurface);

        }

        void prepareSplashScreenBackgroundImage(const char *filename){
            return;
            SDL_Renderer *splashImageRenderer = SDL_CreateRenderer(windowScreen, -1, 0);
            SDL_Surface *image = SDL_LoadBMP("image.bmp");
            SDL_Texture *texture = SDL_CreateTextureFromSurface(splashFontRenderer, image);
        }
};

#endif