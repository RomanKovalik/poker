#pragma once

#include <Card.h>
#include <Deck.h>

#include <better_enums/enum.h>

#include <algorithm>
#include <vector>

BETTER_ENUM(PokerFlags, uint32_t,
    None = 0x0,
    Small = 0x1
);


BETTER_ENUM(PokerWin, uint32_t,
    None,
    Pair,
    TwoPair,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
    RoyalFlush
);

struct Poker
{
    Poker(RM& a_RM, int32_t a_X, int32_t a_Y, PokerFlags a_Flags = PokerFlags::None);

    ~Poker();

    Poker(const Poker&) = delete;

    void See(SDL_Rect& a_Rect);

    void Draw();

    void Hold(Card a_Card);

    void Score();

    RM& m_RM;
    End* m_End;
    int32_t m_X;
    int32_t m_Y;

    PokerFlags m_Flags;

    bool m_ShowScore;

    Deck m_Deck;
    std::vector<Card> m_Hand;
    PokerWin m_Win;
};
