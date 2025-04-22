//
// Created by user on 2025-04-21.
//


//  Cards = must be consisted of 3 to 4 colours.
//  must be clustered, at least 2 boxes, up to 5 boxes.
//  can pre-made the block layout. (have to make shape class or dedicated shape logic if you want to)


#include "Cards.h"
#include <string>

#include "GameLogic.h"

namespace Puzzle
{
    Puzzle::Cards::Cards(HWND hwnd, int index, Colour type, int x, int y, bool isEmpty):
        mHwnd(hwnd), mIndex(index), mColour(type), mX(x), mY(y), isFront(false), mIsEmpty(isEmpty)
    {

        // initialise the status of the card. type, x, y and front status.
        if (mIsEmpty)
        {
            mBrush = std::make_unique<Gdiplus::SolidBrush>(Gdiplus::Color(255, 128, 128, 128));
        }
        // Switch the boxes based on the box colour
        switch (mColour)
        {
        case Colour::Yellow:
            mBrush = std::make_unique<Gdiplus::SolidBrush>(Gdiplus::Color(255, 255, 255, 0)); // should be the file?
            break;

        case Colour::Red:
            mBrush = std::make_unique<Gdiplus::SolidBrush>(Gdiplus::Color(255, 255, 0, 0));
            break;

        case Colour::Blue:
            mBrush = std::make_unique<Gdiplus::SolidBrush>(Gdiplus::Color(255, 0, 0,255));
            break;

        case Colour::Green:
            mBrush = std::make_unique<Gdiplus::SolidBrush>(Gdiplus::Color(255, 0, 255, 0));
            break;
        }
    }

    bool Puzzle::Cards::isClicked(int x, int y)
    {
        /*if (x >= mX && y >= mY && static_cast <UINT>(x) <=mX + mFront ->GetWidth() &&
            static_cast<UINT>(y) <=mY + mFront ->GetHeight())*/ // this if sentence is no longer needed if you use Rect.

        Gdiplus::Rect rct (mX, mY, mBoxes->GetWidth(), mBoxes->GetHeight()); // Rect function can verify the area of the windows.
        if (rct.Contains(x, y))
        {
            if (mIsEmpty)
            {
                return false;
            }
            return true;
        }

        // Always false unless the card has been clicked.
        return false;
    }

    // must required for redrawing the boxes.
    void Puzzle::Cards::Draw(Gdiplus::Graphics& graphics)
    {
        Gdiplus::Rect rect (mX, mY, mWidth, mHeight);
        graphics.FillRectangle(mBrush.get(), rect);
    }

    void Cards::Invalidate()
    {
        RECT rect{mX, mY,
        static_cast<LONG> (mX+mWidth),
        static_cast<LONG> (mY+mHeight)};

        InvalidateRect(mHwnd, &rect, false);
    }

    void Cards::SetColour(Colour newColour)
    {
        if (!mIsEmpty)
        {
            mColour = newColour;
            switch (mColour)
            {
            case Colour::Yellow:
                mBrush->SetColor(Gdiplus::Color(255, 255, 255, 0));
                break;

            case Colour::Red:
                mBrush->SetColor(Gdiplus::Color(255, 255, 0, 0));
                  break;

            case Colour::Blue:
                mBrush->SetColor(Gdiplus::Color(255, 0, 0, 255));
                break;

            case Colour::Green:
                mBrush->SetColor(Gdiplus::Color(255, 0, 255, 0));\
                break;
            }
        }

    }
}


