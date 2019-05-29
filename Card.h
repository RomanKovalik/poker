#pragma once

#include <Spice.h>

#include <Curie/RM.h>

#include <iostream>
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
    static void Load(RM& a_RM)
    {
        s_Keys.resize(2, std::vector<std::vector<uint32_t>>(
            ValueStrings.size(), std::vector<uint32_t>(
            SuitStrings.size(), 0)));

        for (auto v = 0; v < ValueStrings.size(); ++v)
        {
            for (auto s = 0; s < SuitStrings.size(); ++s)
            {
                Card c((Value)v, (Suit)s);

                std::string name = "content/out/";
                name += c.GetString();

                std::string smallName = name;

                smallName += "_t.png";
                name += ".png";

                std::cout << name << std::endl;

                s_Keys[0][v][s] = a_RM.AddImage(name);
                s_Keys[1][v][s] = a_RM.AddImage(smallName);
            }
        }
    }

    static std::vector<std::vector<std::vector<uint32_t>>> s_Keys;

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

    Value m_Value;
    Suit m_Suit;
};
