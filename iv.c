#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

static SDL_HitTestResult SDLCALL drag_window(SDL_Window *win, const SDL_Point *area, void *data)
{
    (void)win; (void)area; (void)data;
    return SDL_HITTEST_DRAGGABLE;
}

int main(int argc, char *argv[])
{
#ifdef _WIN32
    _setmode(_fileno(stdin), _O_BINARY);
#endif

    FILE *in = stdin;

    char *pthrowaway = calloc(1000, sizeof(char));
    fgets(pthrowaway, 1000, in);

    char *pdimensions = calloc(1000, sizeof(char));
    fgets(pdimensions, 1000, in);

    int width = -1;
    int height = -1;
    sscanf(pdimensions, "%d %d", &width, &height);
    free(pdimensions);

    fgets(pthrowaway, 1000, in);
    free(pthrowaway);

    SDL_Window *pwindow = SDL_CreateWindow(
        "Visor",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        0
    );

    SDL_SetWindowHitTest(pwindow, drag_window, NULL);

    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

    SDL_Rect pixel = (SDL_Rect) {0, 0, 1, 1};
    Uint32 color = 0;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int r = getchar();
            int g = getchar();
            int b = getchar();

            color = SDL_MapRGB(psurface->format, (Uint8)r, (Uint8)g, (Uint8)b);
            pixel.x = x;
            pixel.y = y;
            SDL_FillRect(psurface, &pixel, color);
        }
    }

    SDL_UpdateWindowSurface(pwindow);

    int app_running = 1;
    while (app_running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                app_running = 0;
            }
        }
        SDL_Delay(100);
    }

    SDL_DestroyWindow(pwindow);
    SDL_Quit();
}