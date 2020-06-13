#include <Deck.h>

#include <random>

Deck::Deck(Curie::Vis::RM& a_RM, DeckFlags a_Flags)
: m_RM(a_RM)
, m_RNG(pcg_extras::seed_seq_from<std::random_device>{})
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

Deck::Deck(const Deck& d)
: m_RM(d.m_RM)
, m_RNG(pcg_extras::seed_seq_from<std::random_device>{})
, m_Flags(d.m_Flags)
, m_Cards(d.m_Cards)
{
}

Deck& Deck::operator=(const Deck& d)
{
    if (&d != this)
    {
        m_RNG = pcg64_unique(pcg_extras::seed_seq_from<std::random_device>{});
        m_Flags = d.m_Flags;
        m_Cards = d.m_Cards;
    }

    return *this;
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
