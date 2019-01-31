#pragma once

#include <Spice.h>

#include <Curie/RM.h>

#include <better_enums/enum.h>

#include <string>

BETTER_ENUM(Value, uint8_t,
    Two,
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
    Ace
);

BETTER_ENUM(Suit, uint8_t,
    Spades,
    Hearts,
    Clubs,
    Diamonds
);

struct Card
{
    Card(Value a_Value, Suit a_Suit)
    : m_Value(a_Value)
    , m_Suit(a_Suit)
    {
    }

    std::string GetString()
    {
        std::string ret = m_Value._to_string();
        ret += " of ";
        ret += m_Suit._to_string();

        return ret;
    }

    uint32_t GetKey()
    {
        return RM::MakeKey<Spice, uint8_t>(Spice::CardSpice, { m_Value, m_Suit });
    }

    uint32_t GetSmallKey()
    {
        return RM::MakeKey<Spice, uint8_t>(Spice::SmallCardSpice, { m_Value, m_Suit });
    }

    Value m_Value;
    Suit m_Suit;
};
