
// bắt sự kiện bàn phím in ra ảnh (kết hợp bắt sự kiện bàn phím và vẽ ảnh )
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
                 const string &msg, bool fatal = false);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();

SDL_Texture* loadTexture(string path, SDL_Renderer* renderer );

enum KeyPress
{
    key_press_up,
    key_press_down,
    key_press_left,
    key_press_right
};

draw_picture (int i,SDL_Renderer* renderer)
{
    switch (i)
    {
      case key_press_up:
        {
          SDL_Texture* background0 = loadTexture("04_key_presses/up.bmp", renderer);
          SDL_RenderCopy (renderer, background0, nullptr, nullptr);  // toàn bộ ảnh
          SDL_RenderPresent(renderer);
          SDL_DestroyTexture(background0); // hủy Texture
          background0 = nullptr;
          break;
        }
      case key_press_down:
        {
          SDL_Texture* background1 = loadTexture("04_key_presses/down.bmp", renderer);
          SDL_RenderCopy (renderer, background1, nullptr, nullptr);  // toàn bộ ảnh
          SDL_RenderPresent(renderer);
          SDL_DestroyTexture(background1); // hủy Texture
          background1 = nullptr;
          break;
        }
      case key_press_left:
        {
          SDL_Texture* background2 = loadTexture("04_key_presses/left.bmp", renderer);
          SDL_RenderCopy (renderer, background2, nullptr, nullptr);  // toàn bộ ảnh
          SDL_RenderPresent(renderer);
          SDL_DestroyTexture(background2); // hủy Texture
          background2 = nullptr;
          break;
        }
      case key_press_right:
        {
          SDL_Texture* background3 = loadTexture("04_key_presses/right.bmp", renderer);
          SDL_RenderCopy (renderer, background3, nullptr, nullptr);  // toàn bộ ảnh
          SDL_RenderPresent(renderer);
          SDL_DestroyTexture(background3); // hủy Texture
          background3 = nullptr;
          break;
        }
    }
}

int main (int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    SDL_Event e;

    while (true) {
        if ( SDL_WaitEvent(&e) == 0) SDL_Delay(100);   // nếu không có phím gì để bấm thì đợi 1 lúc rồi xử lí
        else if ( e.type == SDL_QUIT ) break;      // nếu đóng cửa số màn hình
        else if (e.type == SDL_KEYDOWN) {         // nếu user gõ phím
            cout << "_" << SDL_GetKeyName(e.key.keysym.sym) << "_" << endl;     // in ra phím được gõ
            // SDL_GetKeyName in ra tên phím
            switch (e.key.keysym.sym)
            {
            // SDLK là mã phím
              case SDLK_w:
              case SDLK_UP: draw_picture(0,renderer); break;
              case SDLK_s:
              case SDLK_DOWN: draw_picture(1,renderer);break;
              case SDLK_a:
              case SDLK_LEFT: draw_picture(2,renderer);break;
              case SDLK_d:
              case SDLK_RIGHT: draw_picture(3,renderer);break;
            }
        }
    }

    // waitUntilKeyPressed();
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

