#pragma once

#include <Card.h>

#include <Curie/RM.h>

#include <pcg/pcg_random.hpp>

#include <vector>

enum DeckFlags
{
    DF_None     = 0x0,
};

struct Deck
{
    Deck(RM& a_RM, DeckFlags a_Flags = DF_None);

    Deck(const Deck& d);

    Deck& operator=(const Deck& d);

    Card Draw();

    Card Take(Value a_Value, Suit a_Suit);

    RM& m_RM;

    pcg64_unique m_RNG;

    DeckFlags m_Flags;

    std::vector<Card> m_Cards;
};
