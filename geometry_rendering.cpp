
// Geometry Rendering (rendering API) (vẽ hình đơn giản)
/*
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <cmath>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();

SDL_Texture* loadTexture (string path, SDL_Renderer* renderer);

int main (int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    // clear screen
    SDL_SetRenderDrawColor(renderer,0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear(renderer);

    //Render red filled quad
    SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };  // x,y,w,h
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );    // R is red, G is green, B is blue, A is alpha. Alpha controls how opaque something is and we'll cover that in the transparency tutorial.
    SDL_RenderFillRect( renderer, &fillRect );  // a fill rectangle, which is a solid rectangle.

    //Render green outlined quad
    SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
    SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255);
    SDL_RenderDrawRect( renderer, &outlineRect );  // draw a rectangle outline with an empty center

    //Draw blue horizontal line
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
    SDL_RenderDrawLine( renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 ); // (renderer,x1,y1,x2,y2) (start point and end point axis)


    //Draw vertical line of yellow dots
    SDL_SetRenderDrawColor( renderer, 255, 255, 0, 255);
    // a sequence of dots
    for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
    {
        SDL_RenderDrawPoint( renderer, SCREEN_WIDTH / 2, i );
//        We're just taking a set of points and drawing them from top to bottom.
//        Again notice the y coordinate and the inverted y axis
    }

    //Update screen
    SDL_RenderPresent( renderer );

//    Notice the call to SDL_SetRenderDrawColor. We're using 255 red and 255 green which combine together to make yellow.
//    Remember that call to SDL_SetRenderDrawColor at the top of the loop? If that wasn't there, the screen would be cleared with
//    whatever color was last set with SDL_SetRenderDrawColor, resulting in a yellow background in this case.

    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}

SDL_Texture* loadTexture( string path, SDL_Renderer* renderer )
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == nullptr )
        cout << "Unable to load image " << path << " SDL_image Error: "
             << IMG_GetError() << endl;
    else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == nullptr )
            cout << "Unable to create texture from " << path << " SDL Error: "
                 << SDL_GetError() << endl;
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    // khi dùng máy ảo (thực hành ở trường)
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       //SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


    //Khi chạy trong môi trường bình thường (không chạy trong máy ảo)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy ảo (ví dụ tại máy tính trong phòng thực hành ở trường)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

*/
