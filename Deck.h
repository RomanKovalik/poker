#pragma once

#include <Card.h>

#include <pcg/pcg_random.hpp>

#include <vector>

enum DeckFlags
{
    DF_None     = 0x0,
};

struct Deck
{
    Deck(DeckFlags a_Flags = DF_None);

    Deck(const Deck& a_Deck);

    Card Draw();

    Card Take(Value a_Value, Suit a_Suit);

    pcg64_unique m_RNG;

    DeckFlags m_Flags;

    std::vector<Card> m_Cards;
};
