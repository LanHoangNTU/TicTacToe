// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <limits>
#include<algorithm>

int board[3][3] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
};


int human = -10;
int ai = 10;
int tie = 11;


bool equals(int a, int b, int c) {
    return a == b && b == c && a != 0;
}

int checkWinner() {
    int winner = 0;
    for (int i = 0; i < 3; i++)
    {
        if (equals(board[i][0], board[i][1], board[i][2]))
            winner = board[i][0];
        if (equals(board[0][i], board[1][i], board[2][i]))
            winner = board[0][i];
    }

    if (equals(board[0][0], board[1][1], board[2][2]))
        winner = board[0][0];
    if (equals(board[0][2], board[1][1], board[2][0]))
        winner = board[0][2];

    int emptyDots = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 0) emptyDots += 1;
        }
    }

    if (winner == 0 && emptyDots == 0)
        return tie;
    else
        return winner;
}

int minimax(int m_board[3][3], bool isAI) {
    int result = checkWinner();
    if (result != 0) {
        return result;
    }

    int best = 0;
    int turnScore = 0;
    if (isAI){
        turnScore = ai;
        best = std::numeric_limits<int>::min();
    }
    else {
        turnScore = human;
        best = std::numeric_limits<int>::max();
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (m_board[i][j] == 0)
            {
                m_board[i][j] = turnScore;
                int score = minimax(m_board, !isAI);
                m_board[i][j] = 0;
                if (isAI)
                    best = std::max(score, best);
                else
                    best = std::min(score, best);
                //std::cout << "\t" << result;
            }
        }
    }

    return best;
}

void AIMove() {
    int best = std::numeric_limits<int>::min();
    int x;
    int y;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 0)
            {
                board[i][j] = ai;
                int score = minimax(board, false);
                board[i][j] = 0;
                if (score > best) {
                    best = score;
                    x = i;
                    y = j;
                }
            }
        }
    }

    board[x][y] = ai;
}

void outBoard() {
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            switch (board[i][j])
            {
            case 10:
                std::cout << "\tX";
                break;
            case -10:
                std::cout << "\tO";
                break;
            default:
                std::cout << "\t_";
                break;
            }
        }
        std::cout << "\n";
    }
}

int main()
{
    int i = 0;
    bool turn = false;
    int x;
    int y;
    while (checkWinner() == 0) {
        system("cls");
        outBoard();
        if (turn) {
            bool flag = false;
            do{
                std::cout << "x: ";
                std::cin >> x;
                std::cout << "y: ";
                std::cin >> y;

                if (board[x][y] == 0) {
                    board[x][y] = human;
                    flag = true;
                }
                else
                    std::cout << "Try again\n";
            } while (!flag);
        }
        else {
            AIMove();
        }

        turn = !turn;
        i++;
    }

    system("cls");
    outBoard();
}
