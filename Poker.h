#pragma once

#include <Card.h>
#include <Deck.h>

#include <algorithm>
#include <memory>
#include <vector>

enum PokerFlags
{
    PF_None = 0x0,
    PF_Small = 0x1,
};

enum PokerWin
{
    None = 0,
    Pair,
    TwoPair,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
    RoyalFlush,
};

static const char* PokerWins[]
{
    "None",
    "Pair",
    "TwoPair",
    "ThreeOfAKind",
    "Straight",
    "Flush",
    "FullHouse",
    "FourOfAKind",
    "StraightFlush",
    "RoyalFlush",
};

struct Poker
{
    struct VisibleCard
    {
        VisibleCard(RM& a_RM, Card a_Card)
        : m_RM(a_RM)
        , m_Card(a_Card)
        , m_End(m_RM.Add())
        {
        }

        VisibleCard(const VisibleCard& c)
        : m_RM(c.m_RM)
        , m_Card(c.m_Card)
        , m_End(m_RM.Add())
        {
        }

        VisibleCard(VisibleCard&& c)
        : m_RM(c.m_RM)
        , m_Card(c.m_Card)
        , m_End(c.m_End)
        {
            c.m_End = nullptr;
        }

        VisibleCard& operator=(const VisibleCard& c)
        {
            if (&c != this)
            {
                m_Card = c.m_Card;

                m_End = m_RM.Add();
            }

            return *this;
        }

        VisibleCard& operator=(VisibleCard&& c)
        {
            if (&c != this)
            {
                m_Card = c.m_Card;

                m_End = c.m_End;
                c.m_End = nullptr;
            }

            return *this;
        }

        ~VisibleCard()
        {
            if (m_End)
                m_RM.Remove(m_End);
        }

        RM& m_RM;
        Card m_Card;
        CiCa::End** m_End;
    };

    static const char* GetString(PokerWin a_W) { return PokerWins[a_W]; }

    Poker(RM& a_RM, int32_t a_X, int32_t a_Y, PokerFlags a_Flags = PF_None);

    ~Poker();

    Poker(const Poker&) = delete;

    void Write();

    void Draw();

    void Hold(Card a_Card);

    void Score();

    RM& m_RM;
    int32_t m_X;
    int32_t m_Y;

    PokerFlags m_Flags;

    bool m_ShowScore;

    Deck m_Deck;
    std::vector<std::unique_ptr<VisibleCard>> m_Hand;
    PokerWin m_Win;
};
