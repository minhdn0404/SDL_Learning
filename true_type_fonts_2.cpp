
// True Font Type - Module Version

/*
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
SDL_Texture* loadTexture(string path, SDL_Renderer* renderer );
SDL_Texture* loadFromRenderedText( string textureText, SDL_Color textColor);

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font *gFont = nullptr;

int main (int argc, char* argv[])
{
    initSDL(window,renderer);

    gFont = TTF_OpenFont( "Font/lazy.ttf", 20 );
    SDL_Color textColor = {0,0,0};
    SDL_Texture* texture = loadFromRenderedText("Hello Peter", textColor);

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_Rect rect = {0,50,602,27};
    SDL_RenderCopyEx(renderer,texture,nullptr,&rect,0.0,nullptr,SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);

    waitUntilKeyPressed();
    SDL_DestroyTexture(texture);
    texture = nullptr;
    quitSDL(window, renderer);
    return 0;

}

SDL_Texture* loadFromRenderedText( string textureText, SDL_Color textColor)
{
    SDL_Texture* mTexture = nullptr;
    SDL_Surface* textSurface = TTF_RenderText_Solid (gFont, textureText.c_str(), textColor);
    if (textSurface == nullptr) cout << "Unable to create text surface! " << endl << TTF_GetError();
    else {
        // Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface(renderer,textSurface);
        if (mTexture == nullptr) cout << "Unable to create texture from rendered text!" << endl << SDL_GetError();
    }
    return mTexture;
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
                 const string &msg, bool fatal)
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

    else
    {
        //Initialize renderer color
        SDL_SetRenderDrawColor(renderer, 255,255,255,255 );

        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
            cout <<  "SDL_image could not initialize! SDL_image Error: " << endl << IMG_GetError();

        //Initialize SDL_ttf
        if( TTF_Init() == -1 )
            cout << "SDL_ttf could not initialize! SDL_ttf Error: \n" <<  TTF_GetError() ;
    }

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
