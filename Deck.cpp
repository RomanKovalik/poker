#include <Deck.h>

#include <random>

Deck::Deck(DeckFlags a_Flags)
: m_RNG(pcg_extras::seed_seq_from<std::random_device>{})
, m_Flags(a_Flags)
{
    for (auto v = 0; v <= Ace; ++v)
    {
        for (auto s = 0; s <= Diamonds; ++s)
        {
            m_Cards.push_back(Card((Value)v, (Suit)s));
        }
    }
}

Deck::Deck(const Deck& a_Deck)
: m_RNG(pcg_extras::seed_seq_from<std::random_device>{})
, m_Flags(a_Deck.m_Flags)
, m_Cards(a_Deck.m_Cards)
{
}

Card Deck::Draw()
{
    auto i = m_RNG(m_Cards.size());

    auto ret = m_Cards[i];

    m_Cards[i] = m_Cards.back();
    m_Cards.pop_back();

    return ret;
}

Card Deck::Take(Value a_Value, Suit a_Suit)
{
    for (auto& c : m_Cards)
    {
        if (c.m_Value == a_Value && c.m_Suit == a_Suit)
        {
            Card ret = c;
            c = m_Cards.back();
            m_Cards.pop_back();
            return ret;
        }
    }

    assert(false);
    return Card(Value::Ace, Suit::Spades);
}
