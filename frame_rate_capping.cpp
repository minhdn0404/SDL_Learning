// Capping Frame Rate
// Another thing we can do with SDL timers is manually cap the frame rate.
// Here we'll disable vsync and maintain a maximum frame rate.
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <sstream>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";

//For this demo, we're going render our frame normally, but at the end of the frame we're going to wait until the frame time is completed.
//For example here, when you want to render at 60 fps you have to spend 16 and 2/3rd milliseconds per frame ( 1000ms / 60 frames ).
//This is why here we calculate the number of ticks per frame in milliseconds.


void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);
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

class LTimer
{
    public:
		//Initializes variables
		LTimer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		Uint32 getTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

    private:
		//The clock time when the timer started
		Uint32 mStartTicks;

		//The ticks stored when the timer was paused
		Uint32 mPausedTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
};


SDL_Window* window;
SDL_Renderer* renderer;
// Globally used font
TTF_Font *gFont;
//Scene textures
LTexture gFPSTextTexture;

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

LTimer::LTimer()
{
    //Initialize the variables
    mStartTicks = 0;
    mPausedTicks = 0;

    mPaused = false;
    mStarted = false;
}

void LTimer::start()
{
    //Start the timer
    mStarted = true;

    //Unpause the timer
    mPaused = false;

    //Get the current clock time
    mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void LTimer::stop()
{
    //Stop the timer
    mStarted = false;

    //Unpause the timer
    mPaused = false;

	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}

void LTimer::pause()
{
    //If the timer is running and isn't already paused
    if( mStarted && !mPaused )
    {
        //Pause the timer
        mPaused = true;

        //Calculate the paused ticks
        mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
    }
}

void LTimer::unpause()
{
    //If the timer is running and paused
    if( mStarted && mPaused )
    {
        //Unpause the timer
        mPaused = false;

        //Reset the starting ticks
        mStartTicks = SDL_GetTicks() - mPausedTicks;

        //Reset the paused ticks
        mPausedTicks = 0;
    }
}

Uint32 LTimer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

    //If the timer is running
    if( mStarted )
    {
        //If the timer is paused
        if( mPaused )
        {
            //Return the number of ticks when the timer was paused
            time = mPausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - mStartTicks;
        }
    }

    return time;
}

bool LTimer::isStarted()
{
	//Timer is running and paused or unpaused
    return mStarted;
}

bool LTimer::isPaused()
{
	//Timer is running and paused
    return mPaused && mStarted;
}

int main (int argc, char* argv[])
{
    initSDL(window, renderer);

    gFont = TTF_OpenFont("Font/lazy.ttf",28);

    bool quit = false;
    SDL_Event e;
    SDL_Color textColor = {0,0,0,255};

    // The frame per second timer
    LTimer fpsTimer;

    //The frames per second cap timer
    LTimer capTimer;

    // in memory text stream
    stringstream timeText;

    // Start counting frames per second
    int countedFrames = 0;
    fpsTimer.start();
//For this program we'll not only need a timer to calculate the frame rate, but also a timer to cap the frames per second.
//Here before we enter the main loop we declare some variables and start the fps calculator timer.


    while (!quit)
    {
        //  Start cap timer
        capTimer.start();
// To cap the FPS we need to know how long the frame has taken to render which is why we start a timer at the beginning of each frame.


        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT) quit = true;
        }

        // Calculate and correct fps
        float avgFPS = countedFrames / (fpsTimer.getTicks()/1000.f);
        if (avgFPS > 2000000) avgFPS = 0;
//To calculate frames per second, you just take the number of rendered frames and divide it by the seconds passed.
//Now it is possible for there to be a very small amount of time passed for the first frame and have it give us a really high fps.
//This is why we correct the value if it is really high.

        //Set text to be rendered
        timeText.str( "" );
        timeText << "Average Frames Per Second (With Cap) " << avgFPS;

        gFPSTextTexture.setTextureFont(timeText.str().c_str(), textColor );
        //Clear screen
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( renderer );

        // Render texture
        gFPSTextTexture.render( ( SCREEN_WIDTH - gFPSTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gFPSTextTexture.getHeight() ) / 2);

        // Update screen
        SDL_RenderPresent(renderer);
        ++countedFrames;

        // If frame finished early
        int frameTicks = capTimer.getTicks();
        if (frameTicks < SCREEN_TICK_PER_FRAME)
        {
            // wait remaining time
            SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
        }
//Finally here we have the code to cap the frame rate. First we get how many ticks the frame took to complete.
//If the number of ticks the frame took to execute is less than the ticks needed per frame,
//we then delay for the remaining time to prevent the application from running too fast.

    }

//There's a reason we'll be using VSync for these tutorials as opposed to manually capping the frame rate.
//When running this application, you'll notice that it runs slightly fast.
//Since we're using integers (because floating point numbers are not precise), the ticks per frame will be 16ms as opposed to the exact 16 2/3ms.
//This solution is more of a stop gap in case you have to deal with hardware that does not support VSync.


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
// As you can see, we're disabling VSync for this demo because we'll be manually capping the frame rate.
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );

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
    gFPSTextTexture.free();
    // Free global font
    TTF_CloseFont (gFont);
    gFont = nullptr;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = nullptr;
	window = nullptr;

	// Quit SDL Subsystem
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
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

