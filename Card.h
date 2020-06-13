#pragma once

#include <Curie/RM.h>

#include <string>
#include <vector>

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

static const std::vector<std::string> ValueStrings
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

static const std::vector<std::string> SuitStrings
{
    "Spades",
    "Hearts",
    "Clubs",
    "Diamonds",
};

struct Card
{
    static void load(Curie::Vis::RM& a_RM)
    {
        s_Keys.resize(2, std::vector<std::vector<uint32_t>>(
            ValueStrings.size(), std::vector<uint32_t>(
            SuitStrings.size(), 0)));

        for (auto v = 0; v < ValueStrings.size(); ++v)
        {
            for (auto s = 0; s < SuitStrings.size(); ++s)
            {
                std::string name = "content/out/";
                name += GetString((Value)v, (Suit)s);

                std::string smallName = name;

                smallName += "_t.png";
                name += ".png";

                s_Keys[0][v][s] = a_RM.AddImage(name);
                s_Keys[1][v][s] = a_RM.AddImage(smallName);
            }
        }
    }

    static std::string GetString(Value a_Value, Suit a_Suit)
    {
        std::string ret = ValueStrings[a_Value];
        ret += "_";
        ret += SuitStrings[a_Suit];

        return ret;
    }

    static std::vector<std::vector<std::vector<uint32_t>>> s_Keys;

    Card(Value a_Value, Suit a_Suit)
    : m_Value(a_Value)
    , m_Suit(a_Suit)
    {
    }

    bool operator==(const Card& c)
    {
        return c.m_Value == m_Value && c.m_Suit == m_Suit;
    }

    Value m_Value;
    Suit m_Suit;
};
