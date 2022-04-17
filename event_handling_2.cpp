
// bắt sự kiện bàn phím di chuyển con trỏ
/*
#include <iostream>
#include <SDL.h>

using namespace std;

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 360;
const int RECT_SIZE = 30;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();

void draw (SDL_Renderer* renderer, int x, int y)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = RECT_SIZE;
    rect.h = RECT_SIZE+3;


    SDL_SetRenderDrawColor(renderer,255,0,0,0);   // set màu vẽ
    SDL_RenderDrawRect(renderer, &rect);    // set hình chữ nhật
    SDL_RenderPresent(renderer);           // vẽ

}

int main (int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

   // tọa độ con trỏ
    int x = SCREEN_WIDTH/2;
    int y = SCREEN_HEIGHT/2;
    const int step = 50;


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
              case SDLK_UP: y-=step; break;
              case SDLK_s:
              case SDLK_DOWN: y+=step;break;
              case SDLK_a:
              case SDLK_LEFT: x-=step;break;
              case SDLK_d:
              case SDLK_RIGHT: x+=step;break;
            }

            draw(renderer,x,y);
        }
    }

    // waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
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
