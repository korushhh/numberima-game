#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

char matris[9][9];

struct Player {
    char name[30];
    char password[20];
    int score;
};

bool save_to_file(Player &p, char *file_path) {
    ofstream file;
    file.open(file_path, ios::binary);
    if (!file.is_open()) {
        cout << "Error: Unable to open file." << endl;
        return false;
    }
    file.write((char *)&p, sizeof(Player));
    return true;
}

bool load_from_file(Player &p, char *file_path) {
    ifstream file;
    file.open(file_path, ios::binary);
    if (!file.is_open()) {
        cout << "Error: Unable to open file." << endl;
        return false;
    }
    file.read((char *)&p, sizeof(Player));
    return true;
}

void display() {
    srand(time(0));
    int z = (rand() % 9);
    int y = (rand() % 9);
    cout << "    ";
    for (int i = 0; i < 9; i++)
        cout << i << "   ";
    cout << endl;
    for (int i = 0; i < 9; i++) {
        cout << i << "   ";
        for (int j = 0; j < 9; j++) {
            if (((i == 5 && j == 6) || (i == 4 && j == 6) || (i == 6 && j == 6) || (i == 5 && j == 5) || (i == 5 && j == 7)) && (i != z || j != y))
            {
                matris[i][j] = '9';
            }
            else if (i != z || j != y)
            {
                char x = '0' + (rand() % 10);
                if (x != '0')
                {
                    matris[i][j] = x;
                }
                else
                    matris[i][j] = '1';
            }
            else
                matris[i][j] = '*';

            if (j != 8)
            {
                cout << matris[i][j] << " | ";
            }
            else
            {
                cout << matris[i][j];
            }
        }
        cout << endl;
    }
}

void sort(char matris[][9], int row)
{
    char temp;
    for (int i = 0; i < 8; i++)
    {
        for (int j = i + 1; j < 9; j++)
        {
            if (matris[row][i] > matris[row][j])
            {

                temp = matris[row][i];
                matris[row][i] = matris[row][j];
                matris[row][j] = temp;
            }
        }
    }
}

void sort1(char matris[][9], int col)
{

    char temp;
    for (int i = 0; i < 8; i++)
    {
        for (int j = i + 1; j < 9; j++)
        {
            if (matris[i][col] > matris[j][col])
            {

                temp = matris[i][col];
                matris[i][col] = matris[j][col];
                matris[j][col] = temp;
            }
        }
    }
}

bool game(char m[][9], int row, int col, int row1, int col1)
{
    if (m[row][col] >= '1' && m[row][col] <= '9')
    {
        if (m[row1][col1] >= '1' && m[row1][col1] <= '9')
        {
            if ((abs(row - row1) == 1 || abs(col - col1) == 1))
            {
                if ((m[row][col] - '0') + (m[row1][col1] - '0') == 10 || m[row][col] == m[row1][col1])
                {
                    return true;
                }
            }

            if (row == row1)
            {
                int min;
                int max;

                int p = (col1 - col);
                if (p > 0)
                {
                    min = col;
                    max = col1;
                }
                if (p < 0)
                {
                    min = col1;
                    max = col;
                }
                int counter{1};

                for (int i = min + 1; i < max; i++)
                {

                    if (m[row][i] == 'x')
                        counter++;
                }
                if (counter == abs(col1 - col))
                {

                    if ((m[row][col] - '0') + (m[row1][col1] - '0') == 10 || m[row][col] == m[row1][col1])
                    {
                        return true;
                    }
                }
            }

            if (col == col1)
            {
                int min;
                int max;

                int p = (row1 - row);
                if (p > 0)
                {
                    min = row;
                    max = row1;
                }
                if (p < 0)
                {
                    min = row1;
                    max = row;
                }
                int counter{1};

                for (int i = min + 1; i < max; i++)
                {

                    if (m[i][col] == 'x')
                        counter++;
                }
                if (counter == abs(row1 - row))
                {

                    if ((m[row][col] - '0') + (m[row1][col1] - '0') == 10 || m[row][col] == m[row1][col1])
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}
bool wincheck(char m[][9])
{
    for (int i = 1; i < 8; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (m[i][j] >= '1' && m[i][j] <= '9')
            {
                int counter{1};

                while (i + counter < 9 && m[i + counter][j] == 'x')
                {
                    counter++;
                }

                if (i + counter < 9 && ((m[i + counter][j] >= '1' && m[i + counter][j] <= '9') && (m[i + counter][j] == m[i][j] || m[i + counter][j] + m[i][j] == '0' + 10)))
                    return true;

                int counter1{1};

                while (i - counter1 >= 0 && m[i - counter1][j] == 'x')
                {
                    counter1++;
                }

                if (i - counter1 >= 0 && ((m[i - counter1][j] >= '1' && m[i - counter1][j] <= '9') && (m[i - counter1][j] == m[i][j] || m[i - counter1][j] + m[i][j] == '0' + 10)))
                    return true;

                int counter2{1};

                while (j + counter2 < 9 && m[i][j + counter2] == 'x')
                {
                    counter2++;
                }

                if (j + counter2 < 9 && ((m[i][j + counter2] >= '1' and m[i][j + counter2] <= '9') && (m[i][j + counter2] == m[i][j] || m[i][j + counter2] + m[i][j] == '0' + 10)))
                    return true;

                int counter3{1};

                while (j - counter3 >= 0 && m[i][j - counter3] == 'x')
                {
                    counter3++;
                }

                if (j - counter3 >= 0 && ((m[i][j - counter3] >= '1' and m[i][j - counter3] <= '9') && (m[i][j - counter3] == m[i][j] || m[i][j - counter3] + m[i][j] == '0' + 10)))
                    return true;
            }
        }
    }
    return false;
}


int main()
{
	
    display();
    Player ali;
    ali.score = 0;
    cout << "Enter your name: ";
    cin >> ali.name;
    cout << "Enter your password: ";
    cin >> ali.password;

    char temp_matris[9][9]; 

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            temp_matris[i][j] = matris[i][j];
        }
    }

    int row, col, row1, col1;
    char choose;
    while (wincheck(temp_matris))
    {
        cout << "Enter the row and then the column number for the first cell: ";
        cin >> row >> col;
        if (temp_matris[row][col] == '*')
        {
            temp_matris[row][col] = 'x';

            cout << "Choose R or C: ";
            cin >> choose;
            if (choose == 'R' || choose == 'r')
            {
                sort(temp_matris, row);
            }
            else if (choose == 'C' || choose == 'c')
            {
                sort1(temp_matris, col);
            }
            cout << " ";
            for (int i = 0; i < 9; i++)
                cout << "   " << i;
            cout << endl;
            for (int i = 0; i < 9; i++)
            {
                cout << i << "   ";
                for (int j = 0; j < 9; j++)
                {
                    if (j != 8)
                    {
                        cout << temp_matris[i][j] << " | ";
                    }
                    else
                    {
                        cout << temp_matris[i][j];
                    }
                }
                cout << endl;
            }
        }
        else
        {
            cout << "Enter the row and then the column number for the second cell: ";
            cin >> row1 >> col1;
            while (temp_matris[row1][col1] == '*')
            {
                cout << "ERROR";
                cout << "Enter the row and then the column number for the second cell: ";
                cin >> row1 >> col1;
            }

            if (game(temp_matris, row, col, row1, col1))
            {
                temp_matris[row][col] = 'x';
                temp_matris[row1][col1] = 'x';
                ali.score++;
            }
            else
                cout << "Wrong choice" << endl;

            cout << " ";
            for (int i = 0; i < 9; i++)
                cout << "   " << i;
            cout << endl;
            for (int i = 0; i < 9; i++)
            {
                cout << i << "   ";
                for (int j = 0; j < 9; j++)
                {
                    if (j != 8)
                    {
                        cout << temp_matris[i][j] << " | ";
                    }
                    else
                    {
                        cout << temp_matris[i][j];
                    }
                }
                cout << endl;
            }

            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    matris[i][j] = temp_matris[i][j];
                }
            }
			cout << endl << "Game Over Your Score :" << ali.score ;
			
            save_to_file(ali, "ali.txt");

            if (load_from_file(ali, "ali.txt"))
            {
                cout << "Player name: " << ali.name << ", Password: " << ali.password << ", Score: " << ali.score << endl;
            }
            else
            {
                cout << "Error: Couldn't load player data from file." << endl;
            }
        }
    }

    return 0;
}
