#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#include "include/window.h"

#include "include/menu.h"

using namespace std;


int main(int argc, char *argv[]){

    bool quit = false;

    SDL_Event event;

    EngineWindow appWindow;
    appWindow.createWindow("Menu Demonstration", 800, 600);

    EngineMenu engineMenu(appWindow.renderer, appWindow.mainWindow);

    //init the splash screen
    engineMenu.initSplashScreen("Press Enter to start", "liberation.ttf");

    while (!quit){

        SDL_PollEvent(&event);
        if(event.type==SDL_WINDOWEVENT && event.window.event==SDL_WINDOWEVENT_CLOSE){
            quit = true;
        }

        //clear the render
        SDL_RenderClear(appWindow.renderer);

        //render the splash screen
        engineMenu.displaySplashScreen();

        //render the new texture
        SDL_RenderPresent(appWindow.renderer);
        SDL_Delay(20);
    }

    
    engineMenu.quitSplashScreen();

    appWindow.destroyWindow();

    return 0;

}