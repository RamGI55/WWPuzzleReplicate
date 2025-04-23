//
// Created by user on 2025-04-21.
//

#ifndef CARDS_H
#define CARDS_H

#pragma once

#include <Windows.h>
#include <gdiplus.h>
#include <memory>

namespace Puzzle
{
    enum class Colour
    {
       Yellow,
        Red,
        Green,
        Blue
    };
    // Types of the colours

    class Cards
    {
    private:
        // back and front image
        std::unique_ptr<Gdiplus::Image> mBoxes;
        // using smarter pointer to avoid memory leak.
        HWND mHwnd;
        int mIndex;
        // size of the card - x y
        int mX;
        int mY;
        // check if it is front.
        bool isFront; // ?
        Colour mColour; // Colours
        bool mIsEmpty {false};
        int mWidth {150};
        int mHeight {150};
        std::unique_ptr<Gdiplus::SolidBrush> mBrush;

    public:
        // Constructor of the card - Type, x, y
        Cards(HWND hwnd, int index, Colour type, int x, int y, bool isEmpty = false);
        Cards()
            : mHwnd(nullptr), mIndex(0), mX(0), mY(0), isFront(false), mIsEmpty(true),
              mBrush(nullptr) {}
        bool isClicked(int x, int y);
        // drawing the card
        void Draw(Gdiplus::Graphics& graphics);
        // invalidate the card for drawing the front.
        void Invalidate();

        Colour GetColour() {return mColour;}
        void SetColour(Colour newColour);
        int GetIndex() {return mIndex;}
        bool IsEmpty() const {return mIsEmpty;}
        void SetEmpty(bool isEmpty) {mIsEmpty = isEmpty;}
        bool isSaved;
    };
}



#endif //CARDS_H
