

// Color Modulation (thay đổi màu sắc của ảnh)

// Color modulation allows you to alter the color of your rendered textures.
// Here we're going to modulate a texture using various colors.

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

void setColor (SDL_Texture* mTexture,Uint8 red, Uint8 green, Uint8 blue );
void render (int x, int y, int w, int h, SDL_Rect* clip,SDL_Texture* mTexture);

SDL_Window* window;
SDL_Renderer* renderer;
// Lưu ý SDL_Texture ko được phép khai báo global

int main (int argc, char* argv[])
{
    initSDL(window, renderer);

    SDL_Texture* mTexture = loadTexture("background/colors.png");

    bool quit = false;
    SDL_Event e;

    // Modulation componets
    Uint8 r = 255;
    Uint8 g = 255;
    Uint8 b = 255;

    // while application is running
    while (!quit)
    {
      // Handle events on queue
      while (SDL_PollEvent(&e) != 0)
      {
        // user request quit
        if (e.type == SDL_QUIT) quit = true;
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym)
            {
                // increase red
                case SDLK_q:
                r+=32;
                break;

                // increase green
                case SDLK_w:
                g+=32;
                break;

                // increase blue
                case SDLK_e:
                b+=32;
                break;

                //Decrease red
                case SDLK_a:
                r -= 32;
                break;

                //Decrease green
                case SDLK_s:
                g -= 32;
                break;

                //Decrease blue
                case SDLK_d:
                b -= 32;
                break;
            }
        }
      }
//    They increase/decrease the components by 32 so it's noticable with every key press.


    // Clear screen
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);

    // Modulate and render texture
    setColor(mTexture,r,g,b);
    render(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,nullptr,mTexture);

    SDL_RenderPresent(renderer);

    }

   // waitUntilKeyPressed();
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

// The function that will allow the texture modulation to be set.
// All it does is take in a red, green, and blue color components
void setColor (SDL_Texture* mTexture, Uint8 red, Uint8 green, Uint8 blue)
{
    // Pass in the texture you want to modulate and the color you want to modulate with
    SDL_SetTextureColorMod(mTexture,red,green,blue);

//    You may have noticed that SDL_SetTextureColorMod accepts Uint8 as arguments for the color components.
//    An Uint8 is just an integer that is Unsigned and 8bit. This means it goes from 0 to 255. 128 is about halfway between 0 and 255,
//    so when you modulate green to 128 it halves the green component for any pixel on the texture.
//    The red and blue squares don't get affected because they have no green in them, but the green becomes half as bright
//    and the white turns a light magenta (magenta is red 255, green 0, blue 255).
//    Color modulation is just a way to multiply a color throughout the whole texture.
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
