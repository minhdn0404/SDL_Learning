
// vẽ ảnh
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
SDL_Texture* loadTexture(string path, SDL_Renderer* renderer );


int main (int argc, char* argv[])
{

    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

//    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // white
//    SDL_RenderDrawPoint(renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
//    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);   // red
//    SDL_RenderDrawLine(renderer, 100, 100, 200, 200);
//    SDL_Rect filled_rect;
//    filled_rect.x = SCREEN_WIDTH - 400;
//    filled_rect.y = SCREEN_HEIGHT - 150;
//    filled_rect.w = 320;
//    filled_rect.h = 100;
//    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
//    SDL_RenderFillRect(renderer, &filled_rect);

//
//    SDL_RenderPresent(renderer);
    // SDL_UpdateWindowSurface(SDL_Window *window)   (khi dùng máy ảo)


    SDL_Texture* background1 = loadTexture("background/Wallpaper_01.jpeg", renderer);

    // render testure to the screen
    SDL_RenderCopy (renderer, background1, nullptr, nullptr);  // toàn bộ ảnh

    SDL_Texture* background2 = loadTexture("background/kiwi_01.JPG", renderer);
    SDL_Rect kiwi;
    SDL_QueryTexture(background2,nullptr,nullptr, &kiwi.w, &kiwi.h);
    kiwi.x = 0;
    kiwi.y = 0;
    kiwi.h = SCREEN_HEIGHT;
    kiwi.w = SCREEN_WIDTH/2.0;

//    SDL_Rect kiwiRect;
//    kiwiRect.x = 100;
//    kiwiRect.y = 100;
//    kiwiRect.h = kiwi.h/2.0;
//    kiwiRect.w = kiwi.w/3.0;
    SDL_RenderCopy(renderer, background2, nullptr, &kiwi);   // render texture to the screen


    SDL_RenderPresent(renderer);

    waitUntilKeyPressed();

    SDL_DestroyTexture(background1); // hủy Texture
    background1 = nullptr;
    SDL_DestroyTexture(background2);
    background2 = nullptr;

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
