#include <Poker.h>

#include <functional>
#include <map>

Poker::Poker(RM& a_RM, int32_t a_X, int32_t a_Y, PokerFlags a_Flags)
: m_RM(a_RM)
, m_End(m_RM.AddEnd(std::bind(&Poker::See, this, std::placeholders::_1), this))
, m_X(a_X)
, m_Y(a_Y)
, m_Flags(a_Flags)
, m_ShowScore(false)
, m_Win(PokerWin::None)
{
}

Poker::~Poker()
{
    m_RM.RemoveEnd(m_End);
}

void Poker::See(SDL_Rect& a_Rect)
{
    uint32_t i = 0;
    for (auto& c : m_Hand)
    {
        uint32_t key;
        uint32_t spacing = 0;

        if (m_Flags & PF_Small)
        {
            key = c.GetSmallKey();
            spacing = 1;
        }
        else
        {
            key = c.GetKey();
        }

        a_Rect.x = m_X + ((m_RM.GetImage(key)->W + spacing) * i);
        a_Rect.y = m_Y;
        a_Rect.w = 1;
        a_Rect.h = 1;

        m_RM.Copy(key, a_Rect);

        i++;
    }

    if (m_ShowScore)
    {
        a_Rect.x = m_X + 2;
        a_Rect.y = m_Y - 8;
        a_Rect.w = 1;
        a_Rect.h = 1;
        // m_RM.Copy(RM::MakeKey<Spice, uint32_t>(Spice::WinSpice, {m_Win}), a_Rect);
    }
}

void Poker::Draw()
{
    std::unique_lock<std::mutex> lk(m_RM.m_Mutex);
    m_Hand.push_back(m_Deck.Draw());
}

void Poker::Hold(Card a_Card)
{
    std::unique_lock<std::mutex> lk(m_RM.m_Mutex);
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
