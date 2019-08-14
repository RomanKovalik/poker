#include <Play.h>

#include <Curie/Quartz.h>
#include <Curie/RM.h>
#include <Curie/SB.h>

#include <SDL2/SDL.h>

#include <cstdio>

#include <pcg/pcg_random.hpp>

template <pcg_detail::bitcount_t table_pow2, pcg_detail::bitcount_t advance_pow2, bool kdd = true>
using specialk = pcg_engines::ext_std8<table_pow2, advance_pow2, pcg_engines::oneseq_rxs_m_xs_8_8, kdd>;

int32_t main(int32_t argc, char* args[])
{
    static const uint32_t parts = 4;

    specialk<1, 4> rng(std::atoi(args[1]));
    uint64_t first = 0;
    uint8_t* p = reinterpret_cast<uint8_t*>(&first);
    for (uint32_t i = 0; i < parts; ++i)
    {
        p[i] = rng();
    }

    uint64_t next = 0;
    p = reinterpret_cast<uint8_t*>(&next);

    uint32_t i = 0;

    while (true)
    {
        for (uint32_t i = 0; i < parts; ++i)
        {
            p[i] = rng();
        }

        if (next == first)
            break;

        ++i;
    }

    std::cout << std::endl;

    std::cout << first << std::endl;
    std::cout << next << std::endl;
    std::cout << i << std::endl;

    return 0;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    auto w = RM::CreateWindow();

    {
        Quartz q(25);

        {
            RM rm(q, *w);
            SB sb(q, 1);

            {
                Play p(q, rm, sb);
                p.Run();
            }
        }
    }

    RM::Destroy(w);

    SDL_Quit();

    return 0;
}
