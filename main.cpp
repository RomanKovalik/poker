#include <Play.h>

#include <Curie/Quartz.h>
#include <Curie/RM.h>
#include <Curie/SB.h>

#include <SDL2/SDL.h>

#include <stdio.h>

int32_t main(int32_t argc, char* args[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    Quartz q;

    auto w = RM::Create();
    RM rm(q, *w);

    SB sb(q);

    Play p(q, rm, sb);
    p.Run();

    RM::Destroy(w);

    SDL_Quit();

    return 0;
}
