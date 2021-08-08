#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int offsets[6][2] = {{-1, 0}, {-1, 1}, {0, 1}, {0, -1}, {1, 0}, {1, -1}};

namespace utils
{
    enum Player
    {
        empty,
        white,
        black
    };

    utils::Player invert_player(utils::Player player)
    {
        return player == utils::white ? utils::black : utils::white;
    }
}

struct Node
{
    Node *rep;
    unsigned int size;
    utils::Player player;
    Node() : rep(this), size(1), player(utils::empty) {}
};

Node *find_set(Node *node)
{
    if (node != node->rep)
    {
        node->rep = find_set(node->rep);
    }
    return node->rep;
}

bool union_sets(Node *node1, Node *node2)
{
    Node *smaller = find_set(node1);
    Node *larger = find_set(node2);
    if (smaller == larger)
    {
        return false;
    }
    if (smaller->size > larger->size)
    {
        Node *temp = smaller;
        smaller = larger;
        larger = temp;
    }
    smaller->rep = larger;
    larger->size += smaller->size;
    return true;
}

Node *determine_winner(vector<vector<Node *>> &board, unsigned int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (board[0][i]->player == utils::white)
        {
            for (int j = 0; j < size; ++j)
            {
                if (find_set(board[size - 1][j]) == find_set(board[0][i]))
                {
                    return find_set(board[0][i]);
                }
            }
        }
        if (board[i][0]->player == utils::black)
        {
            for (int j = 0; j < size; ++j)
            {
                if (find_set(board[j][size - 1]) == find_set(board[i][0]))
                {
                    return find_set(board[i][0]);
                }
            }
        }
    }
}

int main()
{
    int case_count = 0;
    string board_size_str;
    while (getline(cin, board_size_str) && !board_size_str.empty())
    {
        int board_size;
        board_size = stoi(board_size_str);

        string starting_player;
        utils::Player current_player;

        cin >> starting_player;
        if (starting_player == "W")
        {
            current_player = utils::white;
        }
        else
        {
            current_player = utils::black;
        }

        vector<vector<Node *>> board(board_size, vector<Node *>(board_size));

        for (int j = 0; j < board_size; j++)
        {
            for (int k = 0; k < board_size; k++)
            {
                board[j][k] = new Node();
            }
        }

        cin.ignore(10000, '\n');
        string input;
        while (getline(cin, input) && !input.empty())
        {
            int row, col;
            stringstream ss(input);
            ss >> row >> col;

            board[row][col]->player = current_player;

            for (int i = 0; i < 6; i++)
            {
                int current_row = row + offsets[i][0];
                int current_col = col + offsets[i][1];
                if (current_row < 0 || current_row >= board_size || current_col < 0 || current_col >= board_size)
                {
                    continue;
                }
                if (board[current_row][current_col]->player == current_player)
                {
                    union_sets(board[row][col], board[current_row][current_col]);
                }
            }

            current_player = utils::invert_player(current_player);
        }

        Node *winner = determine_winner(board, board_size);

        string winner_str = winner->player == utils::white ? "W" : "B";
        cout << "caso " << case_count << ": " << winner_str << " " << winner->size << endl << endl;
        case_count++;
    }
}