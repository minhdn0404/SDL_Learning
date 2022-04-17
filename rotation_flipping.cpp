
// Rotation and flipping

//SDL 2's hardware accelerated texture rendering also gives us the ability to to do fast image flipping and rotation.
//In this tutorial we'll be using this to make an arrow texture spin and flip.


/*
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
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
void apply_image(string path, int x,int y,double w, double h);
SDL_Texture* loadTexture(string path );

void setColor (SDL_Texture* mTexture, Uint8 red, Uint8 green, Uint8 blue );
void render (int x, int y, int w, int h, SDL_Rect* clip,double angle,
             SDL_Point* center, SDL_RendererFlip flip, SDL_Texture* mTexture);

void setAlpha (SDL_Texture* mTexture, Uint8 alpha);
void setBlendMode (SDL_Texture* mTexture, SDL_BlendMode blending);

SDL_Window* window;
SDL_Renderer* renderer;
// Lưu ý SDL_Texture ko được phép khai báo global

int main (int argc, char* argv[])
{
    initSDL(window, renderer);

    // Scene Texture
    SDL_Texture* mTexture = loadTexture("background/arrow.png");

    bool quit = false;
    SDL_Event e;

    // Angle of rotation
    double degrees = 0;
    // Flip type
    SDL_RendererFlip flipType = SDL_FLIP_NONE;

    while (!quit)
    {
        // Handle event on queue
        while (SDL_PollEvent(&e)!=0)
        {
            if (e.type == SDL_QUIT) quit = true;
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym)
                {
                    case SDLK_a:
                    degrees -= 60;
                    break;

                    case SDLK_d:
                    degrees += 60;
                    break;

                    case SDLK_q:
                    flipType = SDL_FLIP_HORIZONTAL;
                    break;

                    case SDLK_w:
                    flipType = SDL_FLIP_NONE;
                    break;

                    case SDLK_e:
                    flipType = SDL_FLIP_VERTICAL;
                    break;
                }
            }
        }
        // Clear screen
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderClear(renderer);

        // Render arrow
        render (50,50, 300, 300, nullptr, degrees, nullptr,flipType,mTexture);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
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

void render (int x, int y, int w, int h, SDL_Rect* clip,double angle, SDL_Point* center, SDL_RendererFlip flip, SDL_Texture* mTexture)
{
    // Set rendering space and render to screen
    SDL_Rect renderQuad  = {x,y,w,h};

    // Render to screen
    SDL_RenderCopyEx(renderer,mTexture,clip,&renderQuad,angle,center,flip);

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
