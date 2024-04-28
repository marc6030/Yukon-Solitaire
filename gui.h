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


void renderText(const char *text, int x, int y, SDL_Renderer* renderer, TTF_Font* font, int r, int g, int b) {
    SDL_Color color = {r, g, b}; // White color
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void drawCard(SDL_Renderer* renderer, int x, int y, int width, int height, int value, char suit, bool faceDown, TTF_Font* font) {
    if(faceDown){
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
      SDL_Rect rect = { x, y, width, height }; // x, y, bredde, høyde
      SDL_RenderFillRect(renderer, &rect);
    } else {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

      char buffer[50];
      sprintf(buffer, "%d%c", value, suit);

      SDL_Rect rect = { x, y, width, height }; // x, y, bredde, høyde
      SDL_RenderDrawRect(renderer, &rect);
      if(suit == 'D' || suit == 'H'){
        renderText(buffer, x, y, renderer, font , 255, 0, 0);
      } else {
        renderText(buffer, x, y, renderer, font , 0, 0, 0);
      }
    }
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

      int cardSize = 50;
      // draw Cards
      for(int i = 0;i<7;i++){
        if(sharedData->list[i] != NULL){
              Card* current = sharedData->list[i];
              int j = 0;
              while(current->next != NULL){
                int value = current->value;
                char suit = current->suit;
                bool faceDown = current->faceDown;

                drawCard(renderer, i*cardSize, j*cardSize, cardSize, cardSize, value, suit,faceDown , font);
                j++;
                current = current->next;
              }

              int value = current->value;
              char suit = current->suit;
              bool faceDown = current->faceDown;

              drawCard(renderer, i*cardSize, j*cardSize, cardSize, cardSize, value, suit,faceDown , font);
          }

          for(int i = 0;i<4;i++){
            if(sharedData->list[i+7] != NULL){
              Card* current = sharedData->list[i+7];
              while(current->next != NULL){
                current = current->next;
              }
              int value = current->value;
              char suit = current->suit;
              bool faceDown = current->faceDown;

              drawCard(renderer, i*cardSize, 600-cardSize, cardSize, cardSize, value, suit, faceDown, font);
            }
          }

      }

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font); // Close the font
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    cleanup(); // Cleanup SDL and TTF

    return 0;
}
