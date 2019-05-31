#include <Poker.h>

#include <functional>
#include <map>

Poker::Poker(RM& a_RM, int32_t a_X, int32_t a_Y, PokerFlags a_Flags)
: m_RM(a_RM)
, m_X(a_X)
, m_Y(a_Y)
, m_Flags(a_Flags)
, m_ShowScore(false)
, m_Win(PokerWin::None)
, m_Score(nullptr)
{
    m_Cards.push_back(m_RM.AddFlick());
    m_Cards.push_back(m_RM.AddFlick());
    m_Cards.push_back(m_RM.AddFlick());
    m_Cards.push_back(m_RM.AddFlick());
    m_Cards.push_back(m_RM.AddFlick());

    m_Score = m_RM.AddFlick();
}

Poker::~Poker()
{
    for (auto c : m_Cards)
        m_RM.RemoveFlick(c);

    m_Cards.clear();

    m_RM.RemoveFlick(m_Score);
}

void Poker::Write()
{
    uint32_t i = 0;
    for (auto& c : m_Hand)
    {
        uint32_t key;
        uint32_t spacing = 0;

        if (m_Flags & PF_Small)
        {
            key = Card::s_Keys[1][c.m_Value][c.m_Suit];
            spacing = 1;
        }
        else
        {
            key = Card::s_Keys[0][c.m_Value][c.m_Suit];
        }

        SDL_Rect r;
        r.x = m_X + ((m_RM.GetImage(key)->W + spacing) * i);
        r.y = m_Y;
        r.w = 1;
        r.h = 1;

        m_Cards[i]->write(key, r);

        i++;
    }

    if (m_ShowScore)
    {
        SDL_Rect r;
        r.x = m_X + 2;
        r.y = m_Y - 8;
        r.w = 1;
        r.h = 1;

        m_Score->write(m_Win, r);
    }
}

void Poker::Draw()
{
    m_Hand.push_back(m_Deck.Draw());
}

void Poker::Hold(Card a_Card)
{
    m_Hand.push_back(a_Card);
}

void Poker::Score()
{
    auto hand = m_Hand;
    std::sort(hand.begin(), hand.end(), [](const Card &a, const Card &b)->bool {
        if (a.m_Value != b.m_Value)
        {
            return a.m_Value < b.m_Value;
        }
        else
        {
            return a.m_Suit < b.m_Suit;
        }
    });

    std::map<Value, uint32_t> totals;
    bool flush = true;
    Suit prevSuit = Suit::Spades;
    bool straight = true;
    Value prevValue = Value::Two;
    for (auto it = hand.begin(); it != hand.end(); ++it)
    {
        if (it != hand.begin())
        {
            if (it->m_Suit != prevSuit)
            {
                flush = false;
            }

            if (it->m_Value != (prevValue + 1))
            {
                straight = false;
            }
        }

        totals[it->m_Value]++;

        prevSuit = it->m_Suit;
        prevValue = it->m_Value;
    }

    bool ace = totals[Value::Ace] >= 1;
    uint32_t pairs = 0;
    uint32_t trips = 0;
    uint32_t quads = 0;
    for (auto& vt : totals)
    {
        if (vt.second == 4)
        {
            quads++;
        }
        else if (vt.second == 3)
        {
            trips++;
        }
        else if (vt.second == 2)
        {
            pairs++;
        }
    }

    m_Win = [&](){
        if (straight && flush)
        {
            if (ace)
            {
                return PokerWin::RoyalFlush;
            }
            else
            {
                return PokerWin::StraightFlush;
            }
        }
        else if (quads == 1)
        {
            return PokerWin::FourOfAKind;
        }
        else if (trips == 1 && pairs == 1)
        {
            return PokerWin::FullHouse;
        }
        else if (flush)
        {
            return PokerWin::Flush;
        }
        else if (straight)
        {
            return PokerWin::Straight;
        }
        else if (trips == 1)
        {
            return PokerWin::ThreeOfAKind;
        }
        else if (pairs == 2)
        {
            return PokerWin::TwoPair;
        }
        else if (pairs == 1)
        {
            return PokerWin::Pair;
        }
        else
        {
            return PokerWin::None;
        }
    }();
}
