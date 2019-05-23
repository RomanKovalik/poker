#pragma once

#include <Card.h>
#include <Deck.h>

#include <algorithm>
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
    std::vector<Card> m_Hand;
    PokerWin m_Win;

    std::vector<Flick*> m_Cards;
    Flick* m_Score;
};
