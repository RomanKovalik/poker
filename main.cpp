#include <Game.h>

#include <Curie/Quartz.h>
#include <Curie/RM.h>
#include <Curie/SB.h>

#include <SDL2/SDL.h>

#include <cstdio>

int32_t main(int32_t argc, char* args[])
{
    VL::system s;

    VL::window w;

    {
        Quartz q(25);

        {
            RM rm(q, *w.window_handle);
            SB sb(q, 1);

            {
                Game g(q, rm, sb);
                g.run();
            }
        }
    }

    return 0;
}
