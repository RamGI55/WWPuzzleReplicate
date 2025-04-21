//

//  WW Card Game Logic
//  1. change the colour of the tile when the tile has been clicked.
//  2. End the game if the player change the all of the tile in the given attempts.
//  3. otherwise player can reset or redo the process.
//  4. Score system.
//

#include "GameLogic.h"
#include <string>
#include <vector>
#include <random>

namespace Puzzle
{

    void GameLogic::Init(HWND hwnd)
    {
        mBackground = std::make_unique<Gdiplus::Image>(L"404Background.png");
        CreateCard();
    }

    void GameLogic::Release()
    {
        mDeck.clear();

        mBackground.reset();
    }

    void GameLogic::Draw(Gdiplus::Graphics& graphics)
    {
        // graphics.DrawImage(mBackground.get(), 0, 0, mBackground->GetWidth(), mBackground->GetHeight());

        for (auto& cards: mDeck)
        {
            cards.Draw(graphics);
        }

        Gdiplus::PointF pos(1300.f, 20.f);

        Gdiplus::SolidBrush brush(Gdiplus::Color (255,79, 64));
        Gdiplus::Font font (L"Microsoft Sans Serif", 20);

        graphics.DrawString(L"Attempts Left: ", -1, &font, pos, &brush);
        Gdiplus::StringFormat format;

        format.SetAlignment(Gdiplus::StringAlignmentCenter);
        format.SetAlignment(Gdiplus::StringAlignmentCenter);
        graphics.DrawString(std::to_wstring(_mClickCount).c_str(), -1, &font, mCountRect, &format, &brush);

    }

    void GameLogic::OnClick(int x, int y)
    {
        Cards *pCard {};
        for (auto& card: mDeck)
        {
            if (card.isClicked(x,y))
            {
                pCard = &card;
                break;
            }
        }

        if (pCard)
        {
        }
    }

    void GameLogic::CreateCard()
    {
        std::vector<Colour> types;
        while (types.size() < static_cast<size_t> (BOARD_COLS * BOARD_ROWS))
        {
            int modulator = types.size() % 8;

        }

        int posX { 15 }, posY { 10 };
        int index = 0;

        for (int x = 0 ; x <BOARD_ROWS; ++x)
        {
            posY = 10;
            for (int y = 0 ; y <BOARD_COLS; ++y)
            {
                mDeck [x][y] = (Cards(mHwnd, index, types[index++], posX , posY ));
                posY += 150 + 2;
            }
            posX += 150 + 2;
        }
    }
}
