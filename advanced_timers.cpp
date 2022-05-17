
// Advanced timers
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <sstream>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void logSDLError(std::ostream& os,const std::string &msg, bool fatal = false);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();

class LTexture
{
public:
    // Innitialize variables
    LTexture ();
    // Deallocates memory
    ~LTexture();

    // load image
    void setTextureImage (string path);

    // Create image from font string
    void setTextureFont ( string textureText, SDL_Color textColor);

    // Get image dimension
    int getWidth();
    int getHeight();

    // Deallowcates texture
    void free();

    // Set Color modulation
    void setColor (Uint8 red, Uint8 green, Uint8 blue );

    // Set blending
    void setBlendMode (SDL_BlendMode blending);

    // Set alpha modulation
    void setAlpha (Uint8 alpha);

    // render texture at given point
    void render (int x, int y, SDL_Rect* clip = NULL, double angle = 0.0,
                 SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );


private:
    // The actual hardware texture
    SDL_Texture* mTexture;

    // Image dimension
    int mWidth;    // chiều rộng bức ảnh bị load
    int mHeight;   // chiều dài bức ảnh bị load

};

// we're going to make a timer class. It has all the basic function to start/stop/pause/unpause the timer and check its status.
// In terms of data members, we have the start time like before, a variable to store the time when paused,
// and status flags to keep track of whether the timer is running or paused.
class LTimer
{
public:
    // Initialize variables
    LTimer ();

    // various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    // Get the timer's time
    Uint32 getTicks();

    // Check the status of the timer
    bool isStarted ();
    bool isPaused ();
private:
    // The clock time when timer started
    Uint32 mStartTicks; // thời điểm timer bắt đầu chạy

    // The ticks stored when the timer wax paused
    Uint32 mPausedTicks; // thời điểm khi timer pause

    // The timer status
    bool mPaused;
    bool mStarted;

};

SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font *gFont;

// Scene texture
LTexture gTimeTextTexture;
LTexture gPausePromptTexture;
LTexture gStartPromptTexture;

LTexture::LTexture()
{
    // initialize
    mTexture = nullptr;
    mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
    // Deallocate
    free();
}

// This function takes in the string of text we want to render and the color we want to use to render it.
void LTexture::setTextureFont( string textureText, SDL_Color textColor)
{
    // Get rid of preexisting texture
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid (gFont, textureText.c_str(), textColor);
    if (textSurface == nullptr) cout << "Unable to create text surface! " << endl << TTF_GetError();
    else {
        // Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface(renderer,textSurface);
        if (mTexture == nullptr) cout << "Unable to create texture from rendered text!" << endl << SDL_GetError();
        else {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        //Get rid of old surface
		SDL_FreeSurface( textSurface );
    }
}

void LTexture::setTextureImage(string path)
{
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == nullptr )
        cout << "Unable to load image " << path << " SDL_image Error: "
             << IMG_GetError() << endl;
    else {

        // Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface -> format,0,255,255));

        mTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( mTexture == nullptr )
            cout << "Unable to create texture from " << path << " SDL Error: "
                 << SDL_GetError() << endl;
        else {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

void LTexture::free()
{
    // Free texture if it exist
    if (mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = 0;
		mHeight = 0;
    }
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    // Modulate testure rgb
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render (int x,int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    // Set Redering space and render to screen
    SDL_Rect renderQuad = {x,y,mWidth,mHeight};

    // Set clip rendering dimensions;
    if (clip!=nullptr)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    // Render to screen
    SDL_RenderCopyEx (renderer,mTexture,clip,&renderQuad,angle,center,flip);
}

LTimer::LTimer ()
{
    // Initialize the variables
    mStartTicks = 0;
    mPausedTicks = 0;

    mPaused = false;
    mStarted = false;
}

//The start function sets the started and paused flags, gets the timer's start time and initializes the pause time to 0.
//For this timer, if we want to restart it we just call start again.
//Since we can start the timer if it is paused and/or running, we should make sure to clear out the paused data.
void LTimer::start()
{
    // Start the timer
    mStarted = true;

    // UnPause the timer
    mPaused = false;

    // Get the current clock time
    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

// The stop function basically reinitializes all the variables.
void LTimer::stop()
{
    // Stop the timer
    mStarted = false;

    //Unpause the timer
    mPaused = false;

    // Clear tick variables
    mStartTicks = 0;
    mPausedTicks = 0;
}

// When pausing, we want to check if the timer is running because it doesn't make sense to pause a timer that hasn't started.
// If the timer is running, we set the pause flag, store the time when the timer was paused in mPausedTicks, and reset the start time.
void LTimer::pause()
{
    // If the timer is running and isn't already paused
    if (mStarted && !mPaused)
    {
        // Pause the timer
        mPaused = true;

        // Calculate the paused ticks
        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}

// So when we unpause the timer, we want to make sure the timer is running and paused
// because we can't unpause a timer that's stopped or running.
// We set the paused flag to false and set the new start time.
void LTimer::unpause()
{
    // If the timer is running and paused
    if (mStarted && mPaused)
    {
        // Unpause the timer
        mPaused = false;

        // Reset the starting ticks
        mStartTicks = SDL_GetTicks() - mPausedTicks;

        // Reset the paused ticks
        mPausedTicks = 0;
    }
}
//Say if you start the timer when SDL_GetTicks() reports 5000 ms and then you pause it at 10000ms.
//This means the relative time at the time of pausing is 5000ms.
//If we were to unpause it when SDL_GetTicks was at 20000, the new start time would be 20000 - 5000ms or 15000ms.
//This way the relative time will still be 5000ms away from the current SDL_GetTicks time.

//Getting the time is a little bit tricky since our timer can be running, paused, or stopped.
//If the timer is stopped, we just return the initial 0 value.
//If the timer is paused, we return the time stored when paused.
//If the timer is running and not paused, we return the time relative to when it started.
Uint32 LTimer::getTicks()
{
    // The actual timer time
    Uint32 time = 0;

    // If the timer is running
    if (mStarted)
    {
        // If the timer is paused
        if (mPaused)
        {
            // Return the number of ticks when the timer was paused
            time = mPausedTicks;
        }
        else {
            // Return the current time minus the start time
            time = SDL_GetTicks() - mStartTicks;
        }
    }
    return time;
}

bool LTimer::isStarted()
{
    // Timer is running and paused or unpaused
    return mStarted;
}

bool LTimer::isPaused()
{
    // Timer is running and paused
    return mPaused && mStarted;
}

int main (int argc, char* argv[])
{
    initSDL(window, renderer);

    gFont = TTF_OpenFont( "Font/lazy.ttf", 28 );
    SDL_Color textColor = {0,0,0,255}; // black

    // Load stop prompt texture
    gStartPromptTexture.setTextureFont("Press S to Start or Stop the Timer", textColor);
    // Load pause prompt texture
    gPausePromptTexture.setTextureFont("Press P to Pause or Unpause the Timer", textColor);

    bool quit = false;
    SDL_Event e;
    textColor = {0,0,0,255}; // black

// we declare a timer object and a string stream to turn the time value into text.
    // The application timer
    LTimer timer;
    // In memory text stream
    stringstream timeText;

    while (!quit)
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT ) quit = true;
            else if( e.type == SDL_KEYDOWN ) {
                // Start/stop
                if( e.key.keysym.sym == SDLK_s )
                {
                    if (timer.isStarted()) timer.stop();
                    else timer.start();
                }
                // Pause/unpause
                else if( e.key.keysym.sym == SDLK_p )
                {
                    if (timer.isPaused()) timer.unpause();
                    else timer.pause();
                }
            }
        }

        // Set text to be rendered
        timeText.str( "" );
        timeText << "Seconds since start time " << (timer.getTicks()/1000.f);
        // Render Text
        gTimeTextTexture.setTextureFont(timeText.str().c_str(),textColor);
        //Clear screen
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( renderer );

        //Render textures
        gStartPromptTexture.render( ( SCREEN_WIDTH - gStartPromptTexture.getWidth() ) / 2, 0 );
        gPausePromptTexture.render( ( SCREEN_WIDTH - gPausePromptTexture.getWidth() ) / 2, gStartPromptTexture.getHeight() );
        gTimeTextTexture.render( ( SCREEN_WIDTH - gTimeTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gTimeTextTexture.getHeight() ) / 2 );

        //Update screen
        SDL_RenderPresent( renderer );
    }

    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}

void logSDLError(std::ostream& os, const std::string &msg, bool fatal)
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
    else
    {
        //Initialize renderer color
        SDL_SetRenderDrawColor(renderer, 255,255,255,255 );

        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
            cout <<  "SDL_image could not initialize! SDL_image Error: " << endl << IMG_GetError();

        //Initialize SDL_ttf
        if( TTF_Init() == -1 )
            cout << "SDL_ttf could not initialize! SDL_ttf Error: \n" <<  TTF_GetError() ;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    //Free loaded images
	gTimeTextTexture.free();
	gStartPromptTexture.free();
	gPausePromptTexture.free();

	//Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

	//Destroy window
	SDL_DestroyRenderer(renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
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

