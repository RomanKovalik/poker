#include <Game.h>

#include <Curie/Quartz.h>
#include <Curie/RM.h>
#include <Curie/SB.h>

#include <cstdio>

int32_t main(int32_t argc, char* args[])
{
    VL::System s;

    VL::Window w;

    {
        Quartz q(25);
        RM rm(q, *w.window);
        SB sb(q, 1);

        {
            Game g(q, rm, sb);
            g.run();
        }
    }

    return 0;
}
