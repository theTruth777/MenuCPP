#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

class EngineMenu {
    public:

        EngineMenu(SDL_Renderer *windowRenderer, SDL_Window *window){
            TTF_Init();
            renderer = windowRenderer;
            splashScreenTextBlink = 0;
            SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        }

        void initSplashScreen(const char *displayName, const char *fontFamily){
           prepareSplashScreen(displayName, fontFamily);
        }

        void displaySplashScreen(){
            renderSplashScreen();
        }

        void quitSplashScreen(){
            destroySplashScreen();
        }

    private:
        SDL_Renderer *renderer;
        SDL_Texture *fontTextureWhite;
        SDL_Surface *fontSurfaceWhite;

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
            fontSurfaceWhite = TTF_RenderText_Solid(font, splashText, color);
            fontTextureWhite = SDL_CreateTextureFromSurface(renderer, fontSurfaceWhite);

            splashScreenTextBlink++;
            if(splashScreenTextBlink == 100){

                splashScreenTextBlink = 0;
                
            }

            //Handle splash screen text blinkg effect
            if(splashScreenTextBlink < 50){

                SDL_QueryTexture(fontTextureWhite, NULL, NULL, &textWidth, &textHeight);

                const int devideScreenWidth = windowWidth / 2;
                const int deviceText = textWidth / 2;
                const int dediceScreenHeight = windowHeight / 2;

                SDL_Rect fontStruct = {devideScreenWidth - deviceText, dediceScreenHeight, textWidth, textHeight };                
                SDL_RenderCopy(renderer, fontTextureWhite, NULL, &fontStruct);

            }else{
                
                fontTextureWhite = NULL;
                fontSurfaceWhite = NULL;

            }

        }

        void destroySplashScreen(){

            SDL_DestroyTexture(fontTextureWhite);
            SDL_FreeSurface(fontSurfaceWhite);

        }
};

#endif