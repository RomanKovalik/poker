#include <Game.h>

#include <Curie/IL.h>
#include <Curie/Quartz.h>
#include <Curie/RM.h>
#include <Curie/SB.h>
#include <Curie/VL.h>

#include <cstdio>

int32_t main(int32_t argc, char* args[])
{
    Curie::IL::System input_sys;

    Curie::VL::System video_sys;
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
