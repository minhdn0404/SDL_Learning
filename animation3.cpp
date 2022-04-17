

// Animation 3: Chuyển hướng chuyển động

/*
#include <iostream>
#include <SDL.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";
const int STEP_DELAY = 10; // tốc độ chuyển động

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
   int step = 5;
   int stepX = 0;
   int stepY = 0;
   // vector chuyển động

   Box (int _x, int _y)
   {
       x = _x;
       y = _y;
   }

   void render (SDL_Renderer* renderer)    // hàm vẽ hình vuông
   {
       SDL_Rect rect = {x,y,size,size};
       SDL_SetRenderDrawColor(renderer,0,255,0,255);
       SDL_RenderFillRect(renderer,&rect);
   }

   void move ()  // hàm di chuyển hình vuông
   {
       x+=stepX;
       y+=stepY;
   }

   void turn_left () {
       stepX = -step;
       stepY = 0;
   }
   void turn_right () {
       stepX = step;
       stepY = 0;
   }
   void turn_down () {
       stepY = step;
       stepX = 0;
   }
   void turn_up () {
       stepY = -step;
       stepX = 0;
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

    Box box (10,10);

    // Vẽ hình vuông
    box.render(renderer);

    // chyển động đều trên màn hình
    while (box.inside(0,0,SCREEN_WIDTH,SCREEN_HEIGHT)==true)
    {
         box.move();

         SDL_SetRenderDrawColor(renderer,255,255,255,255);
         SDL_RenderClear(renderer);
         box.render(renderer);
         SDL_RenderPresent(renderer);
         SDL_Delay(STEP_DELAY);


         SDL_Event e;
         if ( SDL_PollEvent(&e) == 0) continue;
         else if ( e.type == SDL_QUIT ) break;
         else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym)
            {
              case SDLK_UP:    box.turn_up(); break;
              case SDLK_DOWN:  box.turn_down(); break;
              case SDLK_LEFT:  box.turn_left();  break;
              case SDLK_RIGHT: box.turn_right(); break;
              default: break;
            }
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
