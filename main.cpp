#include <Game.h>

#include <Curie/Quartz.h>
#include <Curie/RM.h>
#include <Curie/SB.h>

#include <cstdio>

int32_t main(int32_t argc, char* args[])
{
    Curie::VL::System s;

    Curie::VL::Window w;

    {
        Curie::Quartz q(25);
        Curie::Vis::RM rm(q, w);
        Curie::Snd::SB sb(q, 1);

        {
            Game g(q, rm, sb);
            g.run();
        }
    }

    return 0;
}
