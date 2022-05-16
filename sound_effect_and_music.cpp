
// Sound Effect and Music
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
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

    #if defined (SDL_TTF_MAJOR_VERSION)
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

SDL_Window* window;
SDL_Renderer* renderer;
//Scene texture
LTexture gPromptTexture;

// The SDL_mixer data type for music is Mix_Music and one for short sounds is Mix_Chunk.
// The Music that will be played
Mix_Music *gMusic = nullptr;

// The sound effects that will be used
Mix_Chunk *gScratch = nullptr;
Mix_Chunk *gHigh = nullptr;
Mix_Chunk *gMedium = nullptr;
Mix_Chunk *gLow = nullptr;

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

    // Load prompt texture
    gPromptTexture.setTextureImage("21_sound_effects_and_music/prompt.png");

    // Load music
    gMusic = Mix_LoadMUS ("21_sound_effects_and_music/beat.wav");
    gScratch = Mix_LoadWAV( "21_sound_effects_and_music/scratch.wav" );
    gHigh = Mix_LoadWAV( "21_sound_effects_and_music/high.wav" );
    gMedium = Mix_LoadWAV( "21_sound_effects_and_music/medium.wav" );
    gLow = Mix_LoadWAV( "21_sound_effects_and_music/low.wav" );

    bool quit = false;
    SDL_Event e;
    while (!quit)
    {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT) quit = true;
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym)
                {
                    // Play High sound effect
                    case SDLK_1:
                    Mix_PlayChannel (-1,gHigh,0);
                    break;
                    // Play medium sound effect
                    case SDLK_2:
                    Mix_PlayChannel (-1,gMedium,0);
                    break;
                    // Play low sound effect
                    case SDLK_3:
                    Mix_PlayChannel (-1,gLow,0);
                    //Play scratch sound effect
                    case SDLK_4:
                    Mix_PlayChannel( -1, gScratch, 0 );
                    break;

                    case SDLK_9:
                    // if there is no music playing
                    if (Mix_PlayingMusic() == 0) Mix_PlayMusic (gMusic, -1); // play the music
                    // if music is being played
                    else {
                        // if music is paused
                        if (Mix_PausedMusic()==1) Mix_ResumeMusic();   // Resume the music
                        // if the music is playing
                        else Mix_PauseMusic(); // Pause the music
                    }
                    break;

                    case SDLK_0:
                    Mix_HaltMusic();  // Stop the music
                    break;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer,0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // Render Prompt
        gPromptTexture.render(0,0);

        SDL_RenderPresent(renderer);

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
/*
 To initialize SDL_mixer we need to call Mix_OpenAudio.
 The first argument sets the sound frequency, and 44100 is a standard frequency that works on most systems.
 The second argument determines the sample format, which again here we're using the default.
 The third argument is the number of hardware channels, and here we're using 2 channels for stereo.
 The last argument is the sample size, which determines the size of the chunks we use when playing sound.
 2048 bytes (AKA 2 kilobyes) worked fine for me, but you may have to experiment with this value to minimize lag when playing sounds.
*/
        //Initialize SDL_mixer
        if (Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            cout << "SDL_Mixer could not initialize! SDL_Mixer Error: " << Mix_GetError();
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    // Free loaded image
    gPromptTexture.free();

    // Free the sound effects
    Mix_FreeChunk( gScratch );
	Mix_FreeChunk( gHigh );
	Mix_FreeChunk( gMedium );
	Mix_FreeChunk( gLow );
	gScratch = nullptr;
	gHigh = nullptr;
	gMedium = nullptr;
	gLow = nullptr;

    //Free the music
	Mix_FreeMusic( gMusic );
	gMusic = NULL;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = nullptr;
	window = nullptr;

	// Quit SDL Subsystem
	SDL_Quit();
	IMG_Quit();
	Mix_Quit();
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
