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
    static void Load(RM& a_RM)
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

    Card(RM& a_RM, Value a_Value, Suit a_Suit)
    : m_RM(a_RM)
    , m_Value(a_Value)
    , m_Suit(a_Suit)
    , m_End(m_RM.Add())
    {
    }

    Card(const Card& c)
    : m_RM(c.m_RM)
    , m_Value(c.m_Value)
    , m_Suit(c.m_Suit)
    , m_End(m_RM.Add())
    {
    }

    Card(Card&& c)
    : m_RM(c.m_RM)
    , m_Value(c.m_Value)
    , m_Suit(c.m_Suit)
    , m_End(c.m_End)
    {
        c.m_End = nullptr;
    }

    Card& operator=(const Card& c)
    {
        if (&c != this)
        {
            m_Value = c.m_Value;
            m_Suit = c.m_Suit;

            m_End = m_RM.Add();
        }

        return *this;
    }

    Card& operator=(Card&& c)
    {
        if (&c != this)
        {
            m_Value = c.m_Value;
            m_Suit = c.m_Suit;

            m_End = c.m_End;
            c.m_End = nullptr;
        }

        return *this;
    }

    ~Card()
    {
        if (m_End)
            m_RM.Remove(m_End);
    }

    RM& m_RM;

    Value m_Value;
    Suit m_Suit;

    CiCa::End** m_End;
};
