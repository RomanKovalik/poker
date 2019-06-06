#include <Play.h>

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

Play::Play(Quartz& a_Q, RM& a_RM, SB& a_SB)
: m_Q(a_Q)
, m_RM(a_RM)
, m_SB(a_SB)
{
    Card::Load(a_RM);

    for (uint32_t pw = Pair; pw <= RoyalFlush; ++pw)
    {
        std::string asset = "content/";
        asset += Poker::GetString((PokerWin)pw);
        asset += ".png";

        // m_RM.AddImage(RM::MakeKey<Spice, uint32_t>(Spice::WinSpice, {pw}), asset);
    }

    m_SB.AddSound(Sounds::BigDeal, m_SB.SForF(4.0), [&](uint32_t t, uint32_t l, SB::working_t& out)
    {
        out = SH(t, l)
            .Sin(7.0)
            .Scale(0.5)
            .Done();
    });

    m_SB.AddSound(Sounds::SmallDeal, m_SB.SForF(0.75), [&](uint32_t t, uint32_t l, SB::working_t& out)
    {
        out = SH(t, l)
            .Sin(8.0)
            .Scale(0.5)
            .Done();
    });
}

void Play::Run()
{
    bool exit = false;
    while ( ! exit)
    {
        Poker p(m_RM, 5, 385);

        // p.Hold(p.m_Deck.Take(Value::Ten, Suit::Diamonds));
        // p.Hold(p.m_Deck.Take(Value::Jack, Suit::Diamonds));
        // p.Hold(p.m_Deck.Take(Value::Queen, Suit::Diamonds));
        // p.Hold(p.m_Deck.Take(Value::King, Suit::Diamonds));
        // p.Hold(p.m_Deck.Take(Value::Seven, Suit::Hearts));

        while (p.m_Hand.size() < 5)
        {
            m_SB.PlaySound(Sounds::BigDeal);
            m_Q.Teeth(5);
            p.Draw();
            p.Write();
            m_Q.Teeth(10);
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
        Input in(m_Q);
        in.m_KeyDownResponses[{SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5}] = [&](SDL_Keycode a_Key)
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
        in.m_KeyDownResponses[{SDLK_RETURN}] = [](SDL_Keycode a_Key)
        {
            return true;
        };
        in.m_KeyDownResponses[{SDLK_ESCAPE}] = [&](SDL_Keycode a_Key)
        {
            exit = true;
            return exit;
        };

        in.Enter([&]()
        {
        });

        if (exit)
        {
            continue;
        }

        for (auto& o : others)
        {
            m_SB.PlaySound(Sounds::SmallDeal);

            uint32_t waited = 0;
            while (o->m_Hand.size() < 5)
            {
                o->Draw();
                o->Write();
                m_Q.Tooth();

                waited++;
            }

            m_Q.Teeth(1);

            o->Score();
            o->m_ShowScore = true;

            if (o->m_Win == (uint32_t)PokerWin::None)
            {
                m_SB.PlaySound(Sounds::Nup);
            }
            else
            {
                m_SB.PlaySound(Sounds::Win);
            }
        }

        Input in2(m_Q);
        in2.m_KeyDownResponses[{SDLK_RETURN}] = [](SDL_Keycode a_Key)
        {
            return true;
        };
        in2.m_KeyDownResponses[{SDLK_ESCAPE}] = [&](SDL_Keycode a_Key)
        {
            exit = true;
            return exit;
        };

        in2.Enter([&]()
        {
        });
    }

    m_Q.Tooth();
}
