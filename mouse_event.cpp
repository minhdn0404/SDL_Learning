
// 17. Mouse Event

//Like with key presses, SDL has event structures to handle mouse events such as mouse motion, mouse button presses, and mouse button releasing.
//In this tutorial we'll make a bunch of buttons we can interact with.


/*
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <cmath>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";

//Button constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

// we'll have 4 buttons on the screen. Depending on whether the mouse moved over, clicked on, released on, or moved out of the button
// we'll display a different sprite. These constants are here to define all this.
enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);
void quitSDL();
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


    // We won't be using SDL_ttf to render text. This means we don't need the loadFromRenderedText function.
    // Rather than deleting code we may need in the future, we're going to wrap it in if defined statements so the compiler will ignore it
    // if we do not include SDL_ttf. It checks if the SDL_TTF_MAJOR_VERSION macro is defined.
    // Like #include, #if is a macro which is used to talk to the compiler. In this case it says if SDL_ttf is not defined, ignore this piece of code.
    #if defined(SDL_TTF_MAJOR_VERSION)
    // Create image from font string
    void setTextureFont ( string textureText, SDL_Color textColor);
    #endif // defined


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


// Here is the class to represent a button. It has a constructor to initialize, a position setter, an event handler for the event loop,
// and a rendering function. It also has a position and a sprite enumeration so we know which sprite to render for the button.
// Mouse button
class LButton
{
public:
    // Initialize internal variables
    LButton();

    // Set top left position
    void setPosition (int x, int y);

    // Handles mouse event
    void handleEvent (SDL_Event* e);

    // Shows button sprite
    void render();
private:
    // Top left position
    SDL_Point mPosition;

    // Curently used global sprite
    LButtonSprite mCurrentSprite;
};

SDL_Window* window;
SDL_Renderer* renderer;

// Mouse button sprites
SDL_Rect gSpriteClips [BUTTON_SPRITE_TOTAL];
LTexture gButtonSpriteSheetTexture;

// Button objects
LButton gButtons [TOTAL_BUTTONS];

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


// To make sure our source compiles without SDL_ttf, here again we sandwich the loading from font function in another if defined condition.
#if defined (SDL_TTF_MAJOR_VERSION)
void LTexture::setTextureFont( string textureText, SDL_Color textColor)
{
    // Get rid of preexisting texture
    free();

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
#endif // defined


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

LButton::LButton()
{
    mPosition.x = 0;
    mPosition.y = 0;

    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPosition(int x,int y)
{
    mPosition.x = x;
    mPosition.y = y;
}

// This function will be called in the event loop and will handle an event taken from the event queue for an individual button.
void LButton::handleEvent(SDL_Event* e)
{
    // First we check if the event coming in is a mouse event specifically
    // a mouse motion event (when the mouse moves), a mouse button down event (when you click a mouse button), or a mouse button up event (when you release a mouse click).
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
        // If one of these mouse events do occur, we check the mouse position using SDL_GetMouseState.
        // Depending on whether the mouse is over the button or not, we'll want to display different sprites.
        int x,y;
        SDL_GetMouseState(&x, &y);

        // Check if mouse is in button
        bool inside = true;

        // Mouse is left of the button
        if ( x < mPosition.x) inside = false;
        // Mouse is right of the button
        else if ( x > mPosition.x + BUTTON_WIDTH) inside = false;
        // Mouse above the button
        else if ( y < mPosition.y) inside = false;
        // Mouse below the button
        else if ( y > mPosition.y + BUTTON_HEIGHT) inside = false;

        // Mouse is outside button
        if (!inside) mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        // Mouse is inside button
        else {
            // Set mouse over sprite
            switch (e->type)
            {
                case SDL_MOUSEMOTION:
                   mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                   break;
                case SDL_MOUSEBUTTONDOWN:
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                    break;
                case SDL_MOUSEBUTTONUP:
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                    break;
            }
        }
    }
}

// In the rendering function, we just render the current button sprite at the button position.
void LButton::render()
{
    // Show current button sprite
    gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, &gSpriteClips[mCurrentSprite] );
}

int main (int argc, char* argv[])
{
    initSDL(window, renderer);

    gButtonSpriteSheetTexture.setTextureImage("button.png");
    // Set sprites
    for (int i=0; i<BUTTON_SPRITE_TOTAL; ++i)
    {
        gSpriteClips[i].x = 0;
        gSpriteClips[i].y = i*200;
        gSpriteClips[i].w = BUTTON_WIDTH;
        gSpriteClips[i].h = BUTTON_HEIGHT;
    }

    // Set button in corners
    gButtons[0].setPosition(0,0);
    gButtons[1].setPosition(SCREEN_WIDTH-BUTTON_WIDTH,0);
    gButtons[2].setPosition(0,SCREEN_HEIGHT-BUTTON_HEIGHT);
    gButtons[3].setPosition(SCREEN_WIDTH-BUTTON_WIDTH, SCREEN_HEIGHT-BUTTON_HEIGHT);


    bool quit = false;
    SDL_Event e;


    while (!quit)
    {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT) quit = true;

            // Handle button events
            for (int i = 0; i<TOTAL_BUTTONS; ++i)
            {
                gButtons[i].handleEvent(&e);
            }
        }
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        SDL_RenderClear(renderer);

        // Render Buttons
        for (int i=0; i<TOTAL_BUTTONS; ++i)
        {
            gButtons[i].render();
        }

        // Update screen
        SDL_RenderPresent(renderer);
    }


    waitUntilKeyPressed();
    quitSDL();
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

    // Just like SDL_image, we have to initialize it or the font loading and rendering functions won't work properly.
    // We start up SDL_ttf using TTF_init. We can check for errors using TTF_GetError().
    else
    {
        //Initialize renderer color
        SDL_SetRenderDrawColor(renderer, 255,255,255,255 );

        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
            cout <<  "SDL_image could not initialize! SDL_image Error: " << endl << IMG_GetError();

    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

}

void quitSDL()
{
    // Free loaded images
    gButtonSpriteSheetTexture.free();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = nullptr;
	window = nullptr;

	// Quit SDL Subsystem
	SDL_Quit();
	IMG_Quit();
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
