//
// Created by user on 2025-04-21.
//


//  Cards = must be consisted of 3 to 4 colours.
//  must be clustered, at least 2 boxes, up to 5 boxes.
//  can pre-made the block layout. (have to make shape class or dedicated shape logic if you want to)


#include "Cards.h"
#include <string>

namespace Puzzle
{
    Puzzle::Cards::Cards(HWND hwnd, int index, Colour type, int x, int y):
    mHwnd(hwnd), mIndex(index), mColour(type), mX (x), mY (y), isFront (false)
    {
        // initialise the status of the card. type, x, y and front status.
        std::wstring filename;
            // Switch the boxes based on the box colour
        switch (mColour)
        {
        case Colour::Yellow:
            filename = L"404Andoris.png";
            break;

        case Colour::Red:
            filename = L"404Belka.png";
            break;

        case Colour::Blue:
            filename = L"404Klukai.png";
            break;

        case Colour::Green:
            filename = L"404Mechty.png";
            break;
        default:
            filename = L"404Andoris.png"; // blank, cannot travel either.
            break;

        }
        mBoxes = std::make_unique<Gdiplus::Image>(filename.c_str());
        // initialise the back and front image of the card as dynamic memory. (we used the smarter pointer)
    }

    bool Puzzle::Cards::isClicked(int x, int y)
    {
        /*if (x >= mX && y >= mY && static_cast <UINT>(x) <=mX + mFront ->GetWidth() &&
            static_cast<UINT>(y) <=mY + mFront ->GetHeight())*/ // this if sentence is no longer needed if you use Rect.

        Gdiplus::Rect rct (mX, mY, mBoxes->GetWidth(), mBoxes->GetHeight()); // Rect function can verify the area of the windows.
        if (rct.Contains(x, y))
        {
            // TODO::change the card colour
            return true;
        }

        // Always false unless the card has been clicked.
        return false;
    }

    // must required for redrawing the boxes.
    void Puzzle::Cards::Draw(Gdiplus::Graphics& graphics)
    {
        if (isFront)
        {
            graphics.DrawImage(
                mBoxes.get(), mX, mY, mBoxes->GetWidth(), mBoxes->GetHeight());
        }
        else
        {
            graphics.DrawImage(
                mBack.get(), mX, mY, mBack->GetWidth(), mBack->GetHeight());
        }
        // if it is front, draw the front image of the card.

        // otherwise, draw the back image of the card.
    }

    void Cards::Invalidate()
    {
        RECT rect{mX, mY,
        static_cast<LONG> (mX+ mBack->GetWidth()),
        static_cast<LONG> (mY+ mBack->GetHeight())};

        InvalidateRect(mHwnd, &rect, false);
    }

}


