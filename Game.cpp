#include <Game.h>

#include <Deck.h>
#include <Poker.h>

#include <Curie/Input.h>
#include <Curie/Quartz.h>
#include <Curie/RM.h>
#include <Curie/SB.h>
#include <Curie/SH.h>

#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

Game::Game(Curie::Quartz& a_Q, Curie::Vis::RM& a_RM, Curie::Snd::SB& a_SB)
: m_Q(a_Q)
, m_RM(a_RM)
, m_SB(a_SB)
{
    Card::load(a_RM);

    Poker::load(a_RM);

    m_BigDeal = m_SB.CreateSound(m_SB.SForF(5.0),
    [&](uint32_t t, uint32_t l, Curie::Snd::working_t& mono)
    {
        static Curie::Snd::Wave w;
        w.tune(220.0);
        mono = Curie::Snd::SH(t, l)
            .wave(w)
            .scale(0.9)
            .envelope(m_SB.SForF(0.75), m_SB.SForF(0.6), 0.3, m_SB.SForF(0.75))
            ();
    });

    m_SoftBup = m_SB.CreateSound(m_SB.SForF(4.0),
    [&](uint32_t t, uint32_t l, Curie::Snd::working_t& mono)
    {
        static Curie::Snd::Wave w;
        w.tune(160.0);
        mono = Curie::Snd::SH(t, l)
            .wave(w)
            .scale(0.075)
            .envelope(m_SB.SForF(0.5), m_SB.SForF(6.0), 0.4, m_SB.SForF(1.0))
            ();
    });

    m_Win = m_SB.CreateSound(m_SB.SForF(2.0),
    [&](uint32_t t, uint32_t l, Curie::Snd::working_t& mono)
    {
        static Curie::Snd::Wave w;
        w.tune(660.0);
        mono = Curie::Snd::SH(t, l)
            .wave(w)
            .scale(0.8)
            .envelope(m_SB.SForF(0.75), m_SB.SForF(0.75), 0.6, m_SB.SForF(0.5))
            ();
    });
}

void Game::run()
{
    m_Q.teeth(10);

    bool exit = false;
    while ( ! exit)
    {
        Poker p(m_RM, 5, 385);
        p.Write();
        m_Q.teeth(15);

        // p.Hold(p.m_Deck.Take(Value::Ten, Suit::Diamonds));
        // p.Hold(p.m_Deck.Take(Value::Jack, Suit::Diamonds));
        // p.Hold(p.m_Deck.Take(Value::Queen, Suit::Diamonds));
        // p.Hold(p.m_Deck.Take(Value::Nine, Suit::Diamonds));
        // p.Hold(p.m_Deck.Take(Value::Nine, Suit::Hearts));

        while (p.m_Hand.size() < 5)
        {
            m_SB.PlaySound(m_BigDeal);
            p.Draw();
            p.Write();
            m_Q.teeth(7);
        }

        std::vector<std::unique_ptr<Poker>> others;
        for (uint32_t row = 0; row < 12; ++row)
        {
            for (uint32_t col = 0; col < 6; ++col)
            {
                Poker* s = new Poker(m_RM, 14 + (col * 105), 10 + (row * 32), PF_Small);
                s->m_Deck = p.m_Deck;
                others.emplace_back(s);
            }
        }

        std::set<uint32_t> held;
        Input in;
        in.m_KeyDownResponses[Catch({SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5})] = [&](SDL_Keycode a_Key)
        {
            uint32_t index = a_Key - SDLK_1;

            if (held.find(index) == held.end())
            {
                for (auto& o : others)
                {
                    o->Hold(p.m_Hand[index]->m_Card);
                    o->Write();
                }

                held.insert(index);
            }

            return false;
        };
        in.m_KeyDownResponses[Catch({SDLK_RETURN})] = [](SDL_Keycode a_Key)
        {
            return true;
        };
        in.m_KeyDownResponses[Catch({SDLK_ESCAPE})] = [&](SDL_Keycode a_Key)
        {
            exit = true;
            return exit;
        };

        in.open([&]()
        {
            m_Q.tooth();
        });

        if (exit)
        {
            continue;
        }

        for (auto& o : others)
        {
            m_SB.PlaySound(m_SoftBup);

            while (o->m_Hand.size() < 5)
            {
                o->Draw();
            }

            o->Score();

            if (o->m_Win != (uint32_t)PokerWin::None)
            {
                m_SB.PlaySound(m_Win);
            }

            o->Write();
            m_Q.tooth();

            o->m_ShowScore = true;

            o->Write();
            m_Q.tooth();
        }

        Input in2;
        in2.m_KeyDownResponses[Catch({SDLK_RETURN})] = [](SDL_Keycode a_Key)
        {
            return true;
        };
        in2.m_KeyDownResponses[Catch({SDLK_ESCAPE})] = [&](SDL_Keycode a_Key)
        {
            exit = true;
            return exit;
        };

        in2.open([&]()
        {
            m_Q.tooth();
        });
    }

    m_Q.tooth();
}
