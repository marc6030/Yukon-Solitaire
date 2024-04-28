// Data structure for shared data
typedef struct {
    char lastCommand[100];
    Card *list[11];
    Card *deck;
} SharedData;


void drawCard(SDL_Renderer* renderer, int x, int y, int width, int height, int value, char suit) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect = { 100, 100, 200, 150 }; // x, y, bredde, høyde
    SDL_RenderDrawRect(renderer, &rect);
}


// Function to create a window
DWORD WINAPI createWindow(LPVOID lpParam) {

    SharedData* sharedData = (SharedData*)lpParam;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

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
