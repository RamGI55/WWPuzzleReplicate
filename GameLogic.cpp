//

//  WW Card Game Logic
//  1. change the colour of the tile when the tile has been clicked.
//  2. End the game if the player change the all of the tile in the given attempts.
//  3. otherwise player can reset or redo the process.
//  4. Score system.
//

#include "GameLogic.h"

#include <queue>
#include <string>
#include <vector>
#include <random>
#include <stack>

namespace Puzzle
{
    void GameLogic::Init(HWND hwnd)
    {
        CreateCard();
        _mClickCount = 10;
    }

    void GameLogic::Release()
    {
        mDeck.clear();

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
        graphics.DrawString(std::to_wstring(_mClickCount).c_str(), -1, &font, mCountRect, &format, &brush); // change to the attempts

    }

    void GameLogic::OnClick(int x, int y)
    {
       int ClickedRow = -1, ClickedCol = -1;
        for (int row =0 ; row <BOARD_ROWS ; row++   )
        {
            for (int col = 0 ; col < BOARD_COLS ; col++)
            {
                if (mDeck[row][col].isClicked(x, y))
                {
                    ClickedRow = row;
                    ClickedCol = col;
                    break;
                }
            }
            if (ClickedRow =! -1)
                break;
        }
       if (ClickedRow == -1 || _mClickCount < = 0 || mDeck[ClickedRow][ClickedCol].IsEmpty())
       {
           return;
       }
        Colour OriginalColour = mDeck[ClickedRow][ClickedCol].GetColour();

        Colour NewColour;
        switch (OriginalColour)
        {
            case Colour::Yellow: NewColour = Colour::Yellow; break;
            case Colour::Green: NewColour = Colour::Green; break;
            case Colour::Red: NewColour = Colour::Red; break;
            case Colour::Blue: NewColour = Colour::Blue; break;
        }
        auto ConnectedTiles = FindconnectedTiles(ClickedRow, ClickedCol, OriginalColour);

        for (auto [ row, col ] : ConnectedTiles)
        {
            mDeck[row][col].SetColour(NewColour);
            mDeck[row][col].Invalidate();
        }
        _mClickCount--;

        if (CheckVictory())
        {
            MessageBox(mHwnd, reinterpret_cast<LPCSTR>(L"You've won!"), reinterpret_cast<LPCSTR>(L"Win!"), MB_OK);
            Reset();
        }
        else if (_mClickCount <= 0)
        {
            MessageBox (mHwnd, reinterpret_cast<LPCSTR>(L"Out of moves! Try Again."), reinterpret_cast<LPCSTR>(L"Game Over"), MB_OK);
            Reset();
        }

        RECT CountRect = {
        static_cast<LONG>(mCountRect.X), static_cast<LONG>(mCountRect.Y),
        static_cast<LONG>(mCountRect.X+mCountRect.Width), static_cast<LONG>(mCountRect.Y+mCountRect.Height)}
        InvalidateRect(mHwnd, &CountRect, FALSE);
    }

    bool GameLogic::CheckVictory()
    {
        Colour FirstColour = Colour::Yellow;
        bool FoundFirst = false;

        for (int row = 0; row < BOARD_ROWS && !FoundFirst; row++)
        {
            for (int col = 0; col < BOARD_COLS && !FoundFirst; col++)
            {
                if (!mDeck[row][col].IsEmpty())
                {
                    FirstColour = mDeck[row][col].GetColour();
                    FoundFirst = true;
                }
            }
        }

        if (!FoundFirst)
        {
            return true;
        }

        for (int row = 0; row < BOARD_ROWS ; row++)
        {
            for (int col = 0; col < BOARD_COLS ; col++)
            {
                if (!mDeck[row][col].IsEmpty()&& mDeck[row][col].GetColour() != FirstColour)
                {
                    return false;
                }
            }
        }
    }

    void GameLogic::Reset()
    {
        _mClickCount = 10;
        CreateCard();
        InvalidateRect(mHwnd, nullptr, false);
    }

    std::vector<std::pair<int, int>> GameLogic::FindconnectedTiles(int row, int col, Colour TargetColour)
    {
        std::vector<std::pair<int, int>> ConnectedTiles;
        std::vector<std::vector<bool>> visited (BOARD_ROWS, std::vector<bool>(BOARD_COLS, false));

        // bfs mechanism for stacking pathfinding
        std::queue<std::pair<int, int>> queue;
        queue.push(std::make_pair(row, col));
        visited[row][col] = true;

        while (!queue.empty())
        {
            auto[r,c] = queue.front();
            queue.pop();

            if (!mDeck[r][c].IsEmpty() && mDeck[r][c].GetColour() == TargetColour)
            {
                ConnectedTiles.push_back(std::make_pair(r, c));

                std::pair<int, int> Directions[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
                for (auto [dr, dc] : Directions)
                {
                    int NewRow = r + dr;
                    int NewCol = c + dc;

                    if (NewRow >= 0 && NewRow <BOARD_ROWS && NewCol >= 0 && NewCol < BOARD_COLS &&
                        !visited[NewRow][NewCol] && !mDeck[NewRow][NewCol].IsEmpty()&& mDeck[NewRow][NewCol].GetColour() == TargetColour)
                    {
                        visited [NewRow][NewCol] = true;
                        queue.push(std::make_pair(NewRow, NewCol));
                    }
                }
            }
        }
        return ConnectedTiles;
    }



    void GameLogic::CreateCard()
    {
        for (int row = 0; row < BOARD_ROWS; row++)
        {
            for (int col = 0; col < BOARD_COLS; col++)
            {
                int index = row * BOARD_COLS +col;
                int posX = 15 + col *152;
                int posY = 10 + row *152;

                mDeck[row][col] = Cards(mHwnd, index,Colour::Yellow, posX, posY,true);
            }
        }

        std::mt19937 rng (std::random_device{}());

       // define the tetris like shapes and randomly distribute
        std::vector<std::vector<std::pair<int,int>>> tetrisShapes= {

            // I shape (horizontal)
            { {0, 0}, {0, 1}, {0,2}, {0,3}},
            // I shape (vertical)
            { {0,0}, {1,0}, {2,0}, {3,0}},
            // O Shape
            { { 0,0}, { 0,1}, {1,0}, {1,1}},
            // T shape
            {{0,0}, {0,1}, {0,2}, {1,1}},
            // L shape
            {{0,0}, {1,0}, {2,0}, {2,1}},
            // J shape
            {{0,1}, {1,1}, {2,0}, {2,1}},
            // S shape
            {{0,1}, {0,2}, {1,0}, {1,1}},
            // Z shape
            {{0,0}, {0,1}, {1,1}, {1,2}}
        };

        int numShapesToPlace = 10; // how much of the block you'd like to place in the map?
        for (int i = 0 ; i < numShapesToPlace; i ++ )
        {
            int ShapeIndex = rng()% tetrisShapes.size();
            auto& shape = tetrisShapes[ShapeIndex];

            int ColourIndex = rng()%4;
            Colour blockColour;
            switch (ColourIndex)
            {
                case 0: blockColour = Colour::Yellow; break;
                case 1: blockColour = Colour::Green; break;
                case 2: blockColour = Colour::Red; break;
                case 3: blockColour = Colour::Blue; break;
            }
            int StartRow = rng() % (BOARD_ROWS - 3);
            int StartCol = rng() % (BOARD_COLS - 3);

            bool CanPlace = true;
            for (auto& [RowOffset, ColOffset] : shape)
            {
                int row = StartRow + RowOffset;
                int col = StartCol + ColOffset;

                if (row >= BOARD_ROWS || col >= BOARD_COLS || !mDeck[row][col].IsEmpty())
                {
                    CanPlace = false;
                    break;
                }
            }
            if (CanPlace)
            {
                for (auto& [RowOffset, ColOffset] : shape)
                {
                    int row = StartRow + RowOffset;
                    int col = StartCol + ColOffset;

                    int index = row * BOARD_COLS + col;
                    int posX = 15 + col *152;
                    int posY = 10 + row *152;
                    mDeck[row][col] = Cards(mHwnd, index,blockColour, posX, posY,false);
                }
            }
            else
            {
                i--;
            }
        }

    }
}
