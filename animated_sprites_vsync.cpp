
// Animated Sprites and VSync

//Animation in a nutshell is just showing one image after another to create the illusion of motion.
//Here we'll be showing different sprites to animate a stick figure.

//Say that we have frames of animation
//And showed one right after the other every 10th second


/*
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Animation Walking Man";
const int WALKING_ANIMATION_FRAMES = 4;
const int DELAY_TIME = 100;

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
void apply_image(string path, int x,int y,double w, double h);
SDL_Texture* loadTexture(string path );

void render (int x, int y, int w, int h, SDL_Rect* clip,SDL_Texture* mTexture);


SDL_Window* window;
SDL_Renderer* renderer;
// Lưu ý SDL_Texture ko được phép khai báo global

//Walking animation
SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ]; // mảng lưu 4 hình

int main (int argc, char* argv[])
{
    initSDL(window, renderer);

    // Clear screen
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);

    SDL_Texture* gSpriteSheetTexture = loadTexture("background/man_animation.png");

    bool quit = false;
    SDL_Event e;
    int frame = 0;

    while (!quit)
    {
        while (SDL_PollEvent(&e)!=0)
        {
            if (e.type == SDL_QUIT) quit = true;
        }
        // Clear screen
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderClear(renderer);

        // Render Current frame
        SDL_Rect* currentClip = &gSpriteClips[frame%4];   // số dư luôn là 0,1,2,3
        render( ( SCREEN_WIDTH - currentClip->w ) / 2,( SCREEN_HEIGHT - currentClip->h ) / 2,SCREEN_WIDTH/3,SCREEN_HEIGHT/3,currentClip,gSpriteSheetTexture );

        SDL_RenderPresent(renderer);

        SDL_Delay(DELAY_TIME);
        // Go to the next frame
        ++frame;
    }


   // waitUntilKeyPressed();
    SDL_DestroyTexture(gSpriteSheetTexture);
    gSpriteSheetTexture = nullptr;
    quitSDL(window, renderer);
    return 0;

}

void apply_image (string path, int x, int y, double w, double h)
{
    SDL_Texture* background = loadTexture(path);
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderCopy(renderer,background,nullptr,&rect);

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(background);
    background = nullptr;
}


void render (int x, int y, int w, int h, SDL_Rect* clip, SDL_Texture* mTexture)
{
    SDL_Rect renderQuad  = {x,y,w,h};
    SDL_RenderCopy(renderer,mTexture,clip,&renderQuad);
}

SDL_Texture* loadTexture( string path)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == nullptr )
        cout << "Unable to load image " << path << " SDL_image Error: "
             << IMG_GetError() << endl;
    else {
        //
        //Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 255, 255 ) );

        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == nullptr )
            cout << "Unable to create texture from " << path << " SDL Error: "
                 << SDL_GetError() << endl;
        else {
         //Set sprite clips
         gSpriteClips[ 0 ] = {0,0,64,205};
         gSpriteClips[ 1 ] = {64,0,64,205};
         gSpriteClips[ 2 ] = {128,0,64,205};
         gSpriteClips[ 3 ] = {192,0,64,205};
        }
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
