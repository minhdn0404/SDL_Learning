
// Animation2 : bắt sự kiện bàn phím di chuyển hinh vuông

/*
#include <iostream>
#include <SDL.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();

struct Box
{
   int x;
   int y;
   int size = 10;

   void render (SDL_Renderer* renderer)    // hàm vẽ hình vuông
   {
       SDL_Rect rect = {x,y,size,size};
       SDL_SetRenderDrawColor(renderer,0,255,0,255);
       SDL_RenderFillRect(renderer,&rect);
   }

   void move ()  // hàm di chuyển hình vuông
   {
       x+=5;
       y+=5;
   }

   int step = 5;
   void move_left () {
       x-=step;
   }
   void move_right () {
       x+=step;
   }
   void move_down () {
       y+=step;
   }
   void move_up () {
       y-=step;
   }

   // hàm kiểm tra xem hình vuông có nằm trong 1 phạm vi cho trước hay không
   bool inside (int minX, int minY, int maxX, int maxY)
   {
       return (minX<=x && minY<=y && x+size<=maxX && y+size<=maxY);
   }



};

int main (int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);

    Box box;
    box.x = 10;
    box.y = 10;
    // Vẽ hình vuông
    box.render(renderer);

    // chyển động đều trên màn hình
    while (box.inside(0,0,SCREEN_WIDTH,SCREEN_HEIGHT)==true)
    {
         SDL_SetRenderDrawColor(renderer,255,255,255,255);
         SDL_RenderClear(renderer);
         box.render(renderer);
         SDL_RenderPresent(renderer);
         SDL_Delay(10);

         SDL_Event e;
         if ( SDL_WaitEvent(&e) == 0) SDL_Delay(100);   // nếu không có phím gì để bấm thì đợi 1 lúc rồi xử lí
         else if ( e.type == SDL_QUIT ) break;      // nếu đóng cửa số màn hình
         else if (e.type == SDL_KEYDOWN) {         // nếu user gõ phím
            switch (e.key.keysym.sym)
            {
              case SDLK_UP:    box.move_up(); break;
              case SDLK_DOWN:  box.move_down(); break;
              case SDLK_LEFT:  box.move_left();  break;
              case SDLK_RIGHT: box.move_right(); break;
              default: break;
            }
         }

    }




    waitUntilKeyPressed();
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

