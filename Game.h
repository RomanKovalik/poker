#pragma once

#include <Curie/Quartz.h>
#include <Curie/RM.h>
#include <Curie/SB.h>

#include <cstdint>
#include <memory>

struct Game
{
    Game(Curie::Quartz& a_Q, Curie::Vis::RM& a_RM, Curie::Snd::SB& a_SB);
    ~Game()
    {
    }

    void run();

    Curie::Quartz& m_Q;

    Curie::Vis::RM& m_RM;

    Curie::Snd::SB& m_SB;

    std::shared_ptr<Curie::Snd::Sound> m_BigDeal;
    std::shared_ptr<Curie::Snd::Sound> m_SoftBup;
    std::shared_ptr<Curie::Snd::Sound> m_Win;
};
