//
// Created by user on 2025-04-21.
//

#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Cards.h"
#include <memory>
#include <vector>

namespace Puzzle
{
    class GameLogic
    {
    public:
        void Init(HWND hwnd);
        void Release();
        void Draw(Gdiplus::Graphics& graphics);
        void OnClick(int x, int y);
        bool CheckVictory();
        void Reset();

        std::vector<std::pair<int,int>> FindconnectedTiles(int row, int col, Colour TargetColour);
        // card area - 885.f x 60.f x 120.f x 30.f

        // 8 x 5 grid of cards
        static const int BOARD_ROWS = 8;
        static const int BOARD_COLS = 8;
        const Gdiplus::RectF mCountRect { 1250.f, 60.f, 120.f,122.f};

        static Colour mSavedColour;

    private:
        // std::unique_ptr<Gdiplus::Image> mBackground;
        // container of the cards.
        Cards mDeck[BOARD_ROWS][BOARD_COLS];

        HWND mHwnd = nullptr;
        Colour mType = Colour::Yellow;
        int _mClickCount = 0 ;
        Cards* mpSelectedCard = nullptr;


    private:
        void CreateCard();


    };
}

#endif //GAMELOGIC_H
