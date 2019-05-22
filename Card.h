#pragma once

#include <Spice.h>

#include <Curie/RM.h>

#include <string>

enum Value
{
    Two = 0,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
};

static const char* ValueStrings[]
{
    "Two",
    "Three",
    "Four",
    "Five",
    "Six",
    "Seven",
    "Eight",
    "Nine",
    "Ten",
    "Jack",
    "Queen",
    "King",
    "Ace",
};

enum Suit
{
    Spades = 0,
    Hearts,
    Clubs,
    Diamonds,
};

static const char* SuitStrings[]
{
    "Spades",
    "Hearts",
    "Clubs",
    "Diamonds",
};

struct Card
{
    Card(Value a_Value, Suit a_Suit)
    : m_Value(a_Value)
    , m_Suit(a_Suit)
    {
    }

    std::string GetString()
    {
        std::string ret = ValueStrings[m_Value];
        ret += "_";
        ret += SuitStrings[m_Suit];

        return ret;
    }

    uint32_t GetKey()
    {
        return 0; // RM::MakeKey<Spice, uint8_t>(Spice::CardSpice, { m_Value, m_Suit });
    }

    uint32_t GetSmallKey()
    {
        return 0; // RM::MakeKey<Spice, uint8_t>(Spice::SmallCardSpice, { m_Value, m_Suit });
    }

    Value m_Value;
    Suit m_Suit;
};
