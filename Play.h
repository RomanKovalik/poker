#pragma once

#include <Card.h>

#include <pcg/pcg_random.hpp>

#include <vector>

struct Deck;
struct Quartz;
struct RM;
struct SB;

struct Play
{
    Play(Quartz& a_Q, RM& a_RM, SB& a_SB);
    ~Play()
    {
    }

    void Run();

    Quartz& m_Q;

    RM& m_RM;

    SB& m_SB;

    uint32_t m_BigDeal;
    uint32_t m_SoftBup;
    uint32_t m_Win;
};
