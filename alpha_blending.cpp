
// Alpha Blending (giống kiểu filter)

// Thanks to new hardware accelerated rendering, transparency is much faster in SDL 2.0.
// Here we'll use alpha modulation (which works much like color modulation) to control the transparency of a texture.


/*
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
void apply_image(string path, int x,int y,double w, double h);
SDL_Texture* loadTexture(string path );

void setColor (SDL_Texture* mTexture, Uint8 red, Uint8 green, Uint8 blue );
void render (int x, int y, int w, int h, SDL_Rect* clip,SDL_Texture* mTexture);

void setAlpha (SDL_Texture* mTexture, Uint8 alpha);
void setBlendMode (SDL_Texture* mTexture, SDL_BlendMode blending);

//Here we're going to add two functions to support alpha transparency on a texture.
//First there's setAlpha which will function much like setColor did in the color modulation tutorial.
//There's also setBlendMode which will control how the texture is blended.
//In order to get blending to work properly, you must set the blend mode on the texture. We'll cover this in detail later.

SDL_Window* window;
SDL_Renderer* renderer;
// Lưu ý SDL_Texture ko được phép khai báo global

int main (int argc, char* argv[])
{
    initSDL(window, renderer);

    SDL_Texture* gModulatedTexture = loadTexture("background/fadeout.png");
    // Start standard alpha blending
    setBlendMode( gModulatedTexture, SDL_BLENDMODE_BLEND);
    SDL_Texture* gBackgroundTexture = loadTexture("background/fadein.png");
//    Here we're loading the front texture we're going to alpha blend and a background texture.
//    As the front texture gets more transparent, we'll be able to see more of the back texture.
//    As you can see in the code, after we load the front texture successfully we set the SDL BlendMode to blend so blending is enabled.
//    Since the background isn't going to be transparent, we don't have to set the blending on it.

    bool quit = false;
    SDL_Event e;

    // Modulation componets
    // we declare a variable to control how much alpha the texture has.
    // It is initialized to 255 so the front texture starts out completely opaque.
    Uint8 a =255;
//    Now how does alpha work? Alpha is opacity, and the lower the opacity the more we can see through it.
//    Like red, green, or blue color components it goes from 0 to 255 when modulating it.
//    the lower the alpha the more transparent it is.


    // while application is running
    while (!quit)
    {
      // Handle events on queue
      while (SDL_PollEvent(&e) != 0)
      {
        // user request quit
        if (e.type == SDL_QUIT) quit = true;
        else if (e.type == SDL_KEYDOWN) {
           //Increase alpha on w
            if( e.key.keysym.sym == SDLK_w )
            {
                //Cap if over 255
                if( a + 32 > 255 ) a = 255;
                //Increment otherwise
                else a += 32;
            }

            //Decrease alpha on s
            else if( e.key.keysym.sym == SDLK_s )
            {
                //Cap if below 0
                if( a - 32 < 0 ) a = 0;
                //Decrement otherwise
                else a -= 32;
            }
        }
      }

       // Clear screen
       SDL_SetRenderDrawColor(renderer,255,255,255,255);
       SDL_RenderClear(renderer);


       // Render Background
       render(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,nullptr,gBackgroundTexture);

       // Render front blended
       setAlpha(gModulatedTexture,a);
       render(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,nullptr,gModulatedTexture);

       // Update screen
       SDL_RenderPresent(renderer);

    }

   // waitUntilKeyPressed();
    SDL_DestroyTexture(gBackgroundTexture);
    gBackgroundTexture = nullptr;
    SDL_DestroyTexture(gModulatedTexture);
    gModulatedTexture = nullptr;
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


void setAlpha(SDL_Texture* mTexture, Uint8 alpha)
{
    // Modulate texture alpha
    SDL_SetTextureAlphaMod(mTexture,alpha);
    // allows us to set the amount of alpha for the whole texture.
}

// setBlendMode allows us to enable blending
void setBlendMode(SDL_Texture* mTexture, SDL_BlendMode blending)
{
    //Set blending function
    SDL_SetTextureBlendMode(mTexture, blending);
}

void setColor (SDL_Texture* mTexture, Uint8 red, Uint8 green, Uint8 blue)
{
    // Pass in the texture you want to modulate and the color you want to modulate with
    SDL_SetTextureColorMod(mTexture,red,green,blue);

}

void render (int x, int y, int w, int h, SDL_Rect* clip, SDL_Texture* mTexture)
{
    SDL_Rect renderQuad  = {x,y,w,h};
    SDL_RenderCopy(renderer,mTexture,clip,&renderQuad);
    // clip là ảnh cắt được từ ảnh gốc
    // renderQuad là khung để đặt clip trên màn hình
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


