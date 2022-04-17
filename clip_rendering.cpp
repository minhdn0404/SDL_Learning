
// Clip Rendering and Sprite Sheets
// (Có thể cắt 1 phần nào đó của bức ảnh và vẽ vào vị trí bất kỳ trên màn hình với kích thước tùy ý)

//Sometimes you only want to render part of a texture.
//A lot of times games like to keep multiple images on the same sprite sheet as opposed to having a bunch of textures.
//Using clip rendering, we can define a portion of the texture to render as opposed to rendering the whole thing.


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

void render (int x, int y, int w, int h, SDL_Rect* clip, SDL_Texture* dots );

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Rect gSpriteClips[ 4 ];

int main (int argc, char* argv[])
{
    initSDL(window, renderer);

    //Clear screen
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );   // màn hình trắng
    SDL_RenderClear( renderer );

    SDL_Texture* dots = loadTexture("background/dots.png");


    //Render top left sprite
    render(0,0,gSpriteClips[ 0 ].w,gSpriteClips[ 0 ].h, &gSpriteClips[ 0 ],dots);

    //Render top right sprite
    render(SCREEN_WIDTH - gSpriteClips[ 1 ].w, 0 , gSpriteClips[ 1 ].w, gSpriteClips[ 1 ].h, &gSpriteClips[ 1 ], dots );

    //Render bottom left sprite
    render(0, SCREEN_HEIGHT-gSpriteClips[2].h, gSpriteClips[ 2 ].w, gSpriteClips[ 2 ].h, &gSpriteClips[2], dots );

   //Render bottom right sprite
    render(SCREEN_WIDTH - gSpriteClips[ 3 ].w, SCREEN_HEIGHT - gSpriteClips[ 3 ].h, gSpriteClips[ 3 ].w, gSpriteClips[ 3 ].h, &gSpriteClips[ 3 ], dots );



    //Update screen
    SDL_RenderPresent( renderer );

    waitUntilKeyPressed();
    SDL_DestroyTexture(dots);
    dots = nullptr;
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

void render (int x, int y, int w, int h, SDL_Rect* clip, SDL_Texture* dots)
{
    SDL_Rect renderQuad  = {x,y,w,h};
    SDL_RenderCopy(renderer,dots,clip,&renderQuad);
    // clip là ảnh cắt được từ ảnh gốc
    // renderQuad là vị trí để đặt clip trên màn hình
}

SDL_Texture* loadTexture( string path)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == nullptr )
        cout << "Unable to load image " << path << " SDL_image Error: "
             << IMG_GetError() << endl;
    else {
        //Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 255, 255 ) );

        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == nullptr )
            cout << "Unable to create texture from " << path << " SDL Error: "
                 << SDL_GetError() << endl;
        else {

        // Tách ảnh vừa load được thành 4 tấm
            //Set top left sprite
        gSpriteClips[ 0 ].x =   0;
        gSpriteClips[ 0 ].y =   0;
        gSpriteClips[ 0 ].w = 100;
        gSpriteClips[ 0 ].h = 100;

        //Set top right sprite
        gSpriteClips[ 1 ].x = 100;
        gSpriteClips[ 1 ].y =   0;
        gSpriteClips[ 1 ].w = 100;
        gSpriteClips[ 1 ].h = 100;

        //Set bottom left sprite
        gSpriteClips[ 2 ].x =   0;
        gSpriteClips[ 2 ].y = 100;
        gSpriteClips[ 2 ].w = 100;
        gSpriteClips[ 2 ].h = 100;

        //Set bottom right sprite
        gSpriteClips[ 3 ].x = 100;
        gSpriteClips[ 3 ].y = 100;
        gSpriteClips[ 3 ].w = 100;
        gSpriteClips[ 3 ].h = 100;
        }
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
