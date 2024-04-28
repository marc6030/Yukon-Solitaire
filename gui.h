// Data structure for shared data
typedef struct {
    char lastCommand[100];
    Card *list[11];
    Card *deck;
} SharedData;

void init() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
}

void cleanup() {
    TTF_Quit();
    SDL_Quit();
}

void drawCard(SDL_Renderer* renderer, int x, int y, int width, int height, int value, char suit) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect = { 100, 100, 200, 150 }; // x, y, bredde, høyde
    SDL_RenderDrawRect(renderer, &rect);

    char* str = "";
    renderText(str, 100, 100, renderer, font); 
  //  SDLTest_DrawCharacter(renderer,100,100,'C');
}

void renderText(const char *text, int x, int y, SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Color color = {0, 255, 255}; // White color
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

DWORD WINAPI createWindow(LPVOID lpParam) {
    SharedData* sharedData = (SharedData*)lpParam;

    init(); // Initialize SDL and TTF

    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    TTF_Font* font = TTF_OpenFont("font.ttf", 24); // Load your TrueType font here

    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Render text
      //  renderText("Hello, SDL!", 100, 100, renderer, font); // Example text rendering

        // Render cards
        if(sharedData->list[0] != NULL){
            drawCard(renderer, 100, 100, 200, 300, sharedData->list[0]->value, sharedData->list[0]->value);
        }

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font); // Close the font
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    cleanup(); // Cleanup SDL and TTF

    return 0;
}


/*

// Function to create a window
DWORD WINAPI createWindow(LPVOID lpParam) {

    SharedData* sharedData = (SharedData*)lpParam;


    // Create a window
    SDL_Window* window = SDL_CreateWindow(
        "SDL Window",              // Window title
        SDL_WINDOWPOS_UNDEFINED,   // Initial x position
        SDL_WINDOWPOS_UNDEFINED,   // Initial y position
        800,                       // Width
        600,                       // Height
        SDL_WINDOW_SHOWN           // Flags
    );
    if (window == NULL) {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main loop
    int running = 1;
    while (running) {
      int sizeX = 10;
    //  printf("%d\n", sizeX);
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        if(sharedData->list[0] != NULL){
          drawCard(renderer, sizeX, 100, 200, 300, sharedData->list[0]->value,sharedData->list[0]->value); // Draw a card at position (100, 100) with width 200 and height 300
        }
      //  drawCard(SDL_Renderer* renderer, int x, int y, int width, int height, int value, char suit)
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
*/
