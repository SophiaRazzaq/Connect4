#include <iostream>
#include <fstream>
#include<string>
#include <vector>

using namespace std;


const int MaxRows = 14;
const int MaxCols = 14;
const int MaxGray = -1;
vector<vector<int>> Board;

struct Player {
    string Name;
    char Mark;

    Player(char mark = 'o', string PlayerName = "Player Name") {
        Mark = mark;
        Name = PlayerName;
    }

    void setPlayerName(string PlayerName) {
        Name = PlayerName;
        return;
    }

    void setPlayerMark(char PlayerMark) {
        Mark = PlayerMark;
        return;
    }
};

struct GameBoard {
  
    char Board[MaxRows][MaxCols];
    
    GameBoard(char FillChar = '.') {
        for (int r = 0; r < MaxRows; r++)
            for (int c = 0; c < MaxCols; c++)
                Board[r][c] = FillChar;
        return;
    }
};

struct Connect_N {

    GameBoard Board; // Game board to hold move data
    int Rows, Columns; // Game board size
    int ConnectLimit;// How many Marks to connect to win

    Player Players[2];// list of players
    int TurningPlayer; // index of turning player

    int GameEndState;
    // GameEndState 0 means game is not over
    // GameEndState 1 means first player has won it
    // GameEndState 2 means second player has won it

    int Moves_Made[MaxCols];
    // An array to hold the count of moves made in each
    // column. It will help us determine the row for
    // each move in an efficient way.

    Connect_N(int R = 6, int C = 7, int Limit = 4) {
        if (R < 0 || R > MaxRows)
            R = 6;

        if (C < 0 || C > MaxCols)
            C = 7;

        if (Limit < 0)
            Limit = 4;

        Rows = R;
        Columns = C;
        ConnectLimit = Limit;
        TurningPlayer = 0;
        GameEndState = 0;

        for (int i = 0; i < MaxCols; i++)
            Moves_Made[i] = 0;
    }

    bool MakeMove(int Col) {
        /**
            This function must validate the move and if
            possible make that move and update the entire
            state like board, turning player, GameEndState
            etc.

            It will return false if the move is not
            possible for some reason and true if
            move is valid and done successfully.

            An incomplete definition of this function is given
            below. You must update and complete it in all
            respects.
            /*
            

        // horizontalCheck
        for (int j = 0; j < Rows -  ; j++) {
            for (int i = 0; i < Columns ; i++) {
                if (Board.Board[i][j] == ConnectLimit && Board.Board[i][j + 1] == ConnectLimit && Board.Board[i][j + 2] == ConnectLimit && Board.Board[i][j + 3] == ConnectLimit ) {
                    return true;
                }
            }
        }
        // verticalCheck
        for (int i = 0; i < Columns - 3; i++) {
            for (int j = 0; j < Rows; j++) {
                if (Board.Board[i][j] == ConnectLimit && Board.Board[i + 1][j] == ConnectLimit && Board.Board[i + 2][j] == ConnectLimit && Board.Board[i + 3][j] == ConnectLimit) {
                    return true;
                }
            }
        }
        // ascendingDiagonalCheck
        for (int i = 3; i < Columns; i++) {
            for (int j = 0; j < Rows - 3; j++) {
                if (Board.Board[i][j] == Col && Board.Board[i - 1][j + 1] == Col && Board.Board[i - 2][j + 2] == Col && Board.Board[i - 3][j + 3] == Col)
                    return true;
            }
        }
        // descendingDiagonalCheck
        for (int i = 3; i < Columns; i++) {
            for (int j = 3; j < Rows; j++) {
                if (Board.Board[i][j] == Col  && Board.Board[i - 1][j - 1] == Col && Board.Board[i - 2][j - 2] == Col && Board.Board[i - 3][j - 3] == Col)
                    return true;
            }
        }
        return false;
    }
    */

    // Your updated code goes here

    int R = Moves_Made[Col];
    Board.Board[Rows - 1 - R][Col] = Players[TurningPlayer].Mark;
    TurningPlayer = (TurningPlayer + 1) % 2;
    Moves_Made[Col]++;
    return true;
    }

    bool GameisOn() {
        return GameEndState == 0;
    }

    bool SaveGame(string FileName) {
        
        if (Rows < 0)
            return false;

        ofstream FOUT(FileName);

        FOUT << "Saved game" << endl
            << Rows << " " << Columns << endl
            << MaxGray << endl;

        for (int r = 0; r < Rows ; r++) {
            for (int c = 0; c < Columns; c++) {
                FOUT << Board.Board[r][c] << " ";
            }
            FOUT << endl;
        }
        FOUT.close();
        return true;
        
    }

    bool ReserveMemory() {

        cout << MaxCols << " " << MaxRows << endl;
        if (MaxRows < 0 || MaxCols < 0)
            return false;
       // Create(Board.Board, MaxRows, MaxCols);

       
        return true;
    }

    void Create(vector<vector<int>>& Img, int H, int W) {
        Img = vector<vector<int>>(H);
        for (int i = 0; i < H; i++)
            Img[i] = vector<int>(W);
        return;
    }
   

    bool LoadSavedGame(string FileName) {
        ifstream FIN(FileName);
        if (!FIN.is_open())
            return false;
        

        FIN >> Columns >> Rows;
        if (!ReserveMemory()) {
            FIN.close();
            return false;
        }

        for (int r = 0; r < Rows; r++) {
            for (int c = 0; c < Columns; c++) {
                FIN >> Board.Board[r][c];
            }
        }

        FIN.close();
        return true;
    }
    

    void ShowGame() {
        /**
         This function must show the game on screen and
         if the game is not over take the next move from
         the next player and return that move.

         A very simple implementation is already provided
         to get you started but you better replace it with
         your code to produce a pleasing output
         */

        for (int r = 0; r < Rows; r++) {
            for (int c = 0; c < Columns; c++)
                cout << Board.Board[r][c] << "\t";
            cout << endl << endl;
        }
        if (GameisOn())
            cout << endl << Players[TurningPlayer].Name
            << "("
            << Players[TurningPlayer].Mark << ")"
            << "Moving " << endl;
    }

    void Play() {
        int Move;
        do {
            ShowGame();
            cout << "ENTER NEGATIVE NUMBER FOR THE MAIN MENU" << endl;
            cout << "Please Enter Your Move ? (0 - " << Columns << ") ";
            cin >> Move;
            if (Move < 0)
                break;
            MakeMove(Move);
        } while (GameisOn());
    }
};

int Menu() {
    int Choice;
    do {
        cout << "1. Play" << endl
            << "2. Save Game" << endl
            << "3. Load Game" << endl
            << "4. Exit" << endl
            << "Enter You Choice (1 - 4)";
        cin >> Choice;
    } while (Choice < 1 || Choice > 4);
    return Choice;
}

void initNewGame(Connect_N& C) {
    int Rows, Cols, Limit;
    cout << "How Many Rows : ";
    cin >> Rows;
    cout << "How Many Cols : ";
    cin >> Cols;
    cout << "Connectivity Limit : ";
    cin >> Limit;
    C.Rows = Rows;
    C.Columns = Cols;
    C.ConnectLimit = Limit;
    cout << "First Player Name : ";
    string N;
    cin >> N;
    C.Players[0].setPlayerName(N);
    cout << "Second Player Name : ";
    cin >> N;
    C.Players[1].setPlayerMark('x');
    C.Players[1].setPlayerName(N);
}

int main()
{
    int Choice;
    char FileName[100];
   

    bool GameNotLoaded = true;
    Connect_N Connect_Game(MaxRows, MaxCols, MaxRows);
    do {
        Choice = Menu();
        switch (Choice)
        {
        case 1:
            if (GameNotLoaded) {
                initNewGame(Connect_Game);
                GameNotLoaded = false;
            }
            Connect_Game.Play();
            break;
        case 2:
            cout << "Enter File Name ";
            cin >> FileName;
            if (Connect_N().SaveGame(FileName))
                cout << "Game Saved Successfully " << endl;
            else
                cout << "Game Not Saved Successfully " << endl;
            break;

        case 3:
            if (Choice == 1) {
                cout << "Enter File Name ";
                cin >> FileName;
                if (Connect_N().LoadSavedGame(FileName))
                    cout << "Game Loaded Successfully " << endl;
                else
                    cout << "Game Not Loaded Successfully " << endl;
            }
            break;
        }

    } while (Choice != 4);
    return 0;
}
