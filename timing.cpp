
// Timing
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

SDL_Window* window;
SDL_Renderer* renderer;
// Scene texture
// We'll have a texture to prompt input and a texture to display the current time in milliseconds.
LTexture gTimeTextTexture;
LTexture gPromptTextTexture;
// Font
TTF_Font *gFont = nullptr;

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

int main (int argc, char* argv[])
{
    initSDL(window, renderer);

    gFont = TTF_OpenFont( "Font/lazy.ttf", 28 );
    //Set text color as black
    SDL_Color textColor = { 0, 0, 0, 255 };
// The time texture changes every frame so we have to render that every frame,
// but the prompt texture doesn't change so we can render it once
    gPromptTextTexture.setTextureFont("Press Enter to Reset Start Time.", textColor);

    bool quit = false;
    SDL_Event e;
    //Set text color as black
    textColor = { 0, 0, 0, 255 };

    //Current time start time - startTime variable
    Uint32 startTime = 0;

    //In memory text stream
    stringstream timeText;
// For those of you who have never used string streams, just know that they function like iostreams
// only instead of reading or writing to the console, they allow you to read and write to a string in memory.
// It'll be easier to see when we see them used further on in the program.

    while ( !quit )
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT ) quit = true;
            //Reset start time on return keypress
            else if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN ) {
                startTime = SDL_GetTicks();
// SDL_GetTicks which returns the time since the program started in milliseconds.
// For this demo, we'll be having a timer that restarts every time we press the return key.

// the timer's time is just the current time since the program started returned by SDL_GetTicks.
// If we were to restart the timer when SDL_GetTicks was at 5000 milliseconds (5 seconds),
// then at 10,000 milliseconds the current time - the start time would be 10000 minus 5000 would be 5000 milliseconds.
// So even though the timer contained by SDL_GetTicks hasn't restarted, we can have a timer keep track of a relative start time and reset its start time
            }

        }

        //Set text to be rendered
        timeText.str( "" );
        timeText << "Milliseconds since start time " << SDL_GetTicks() - startTime;

        //Render text
        gTimeTextTexture.setTextureFont( timeText.str().c_str(), textColor );


        //Clear screen
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( renderer );

        //Render textures
        gPromptTextTexture.render( ( SCREEN_WIDTH - gPromptTextTexture.getWidth() ) / 2, 0 );
        gTimeTextTexture.render( ( SCREEN_WIDTH - gPromptTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gPromptTextTexture.getHeight() ) / 2 );

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
	gPromptTextTexture.free();

	//Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

	//Destroy window
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow(window);
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
