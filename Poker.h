#pragma once

#include <Card.h>
#include <Deck.h>

#include <Curie/RM.h>

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

static const std::vector<std::string> PokerWinStrings
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
        , m_Entry(m_RM.Add())
        {
        }

        VisibleCard(const VisibleCard& c)
        : m_RM(c.m_RM)
        , m_Card(c.m_Card)
        , m_Entry(m_RM.Add())
        {
        }

        VisibleCard(VisibleCard&& c)
        : m_RM(c.m_RM)
        , m_Card(c.m_Card)
        , m_Entry(c.m_Entry)
        {
            c.m_Entry = nullptr;
        }

        VisibleCard& operator=(const VisibleCard& c)
        {
            if (&c != this)
            {
                m_Card = c.m_Card;

                m_Entry = m_RM.Add();
            }

            return *this;
        }

        VisibleCard& operator=(VisibleCard&& c)
        {
            if (&c != this)
            {
                m_Card = c.m_Card;

                m_Entry = c.m_Entry;
                c.m_Entry.m_CiCa = nullptr;
            }

            return *this;
        }

        ~VisibleCard()
        {
            if (m_Entry.m_CiCa)
                m_RM.Remove(m_Entry);
        }

        RM& m_RM;
        Card m_Card;
        RM::Entry m_Entry;
    };

    static void Load(RM& a_RM)
    {
        s_Keys.resize(PokerWinStrings.size(), 0);

        for (uint32_t pw = Pair; pw <= RoyalFlush; ++pw)
        {
            std::string asset = "content/";
            asset += Poker::GetString((PokerWin)pw);
            asset += ".png";

            s_Keys[pw] = a_RM.AddImage(asset);
        }
    }

    static std::string GetString(PokerWin a_W) { return PokerWinStrings[a_W]; }

    static std::vector<uint32_t> s_Keys;

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
    RM::Entry m_Score;
    PokerWin m_Win;
};
