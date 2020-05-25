#pragma once

#include <cstdint>

struct Quartz;
struct RM;
struct SB;

struct Game
{
    Game(Quartz& a_Q, RM& a_RM, SB& a_SB);
    ~Game()
    {
    }

    void run();

    Quartz& m_Q;

    RM& m_RM;

    SB& m_SB;

    uint32_t m_BigDeal;
    uint32_t m_SoftBup;
    uint32_t m_Win;
};
