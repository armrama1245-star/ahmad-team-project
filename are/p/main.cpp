#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <windows.h>
#include <conio.h>

using namespace std;

void menu(char map[13][50]);
void game_stages(char map[13][50]);
void Description();
void exit_game();
void loadmap(char map[13][50], const char filename[]);
void runmap(char map[13][50], int chances, int destroyed, int totalE);
void find_player(char map[13][50], int &px, int &py);
void launch(char map[13][50], int stage, int &destroyed, int chances, int px, int py);
bool collision(char map[13][50], int x, int y, int &destroyed);
int count_E(char map[13][50]);
void toggle_walls(char map[13][50], bool &state);
void show_win_screen();
void save_best_score(int stage, int destroyed);

int main()
{
    char map[13][50];
    menu(map);
    return 0;
}

// --------------------------------------------------

void menu(char map[13][50])
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    const int items = 3;
    int choice = 0;

    while (true)
    {
        system("cls");

        SetConsoleTextAttribute(hConsole, 7);
        cout<<"================================================"<<endl;
        cout<<"                   start menu                  "<<endl;
        cout<<"================================================\n"<<endl;

        // item 1
        if (choice == 0)
            SetConsoleTextAttribute(hConsole, 11);
        else
            SetConsoleTextAttribute(hConsole, 7);

        cout << (choice==0 ? "> " : "  ") << "1. Game stages" << endl;

        // item 2
        if (choice == 1)
            SetConsoleTextAttribute(hConsole, 11);
        else
            SetConsoleTextAttribute(hConsole, 7);

        cout << (choice==1 ? "> " : "  ") << "2. Description" << endl;

        // item 3
        if (choice == 2)
            SetConsoleTextAttribute(hConsole, 11);
        else
            SetConsoleTextAttribute(hConsole, 7);

        cout << (choice==2 ? "> " : "  ") << "3. exit" << endl;

        SetConsoleTextAttribute(hConsole, 7);
        cout<<"________________________________________________"<<endl;

        int key = _getch();

        // Arrow keys
        if (key == 224)
        {
            key = _getch();

            if (key == 72) // up
            {
                choice--;
                if (choice < 0) choice = items - 1;
            }
            else if (key == 80) // down
            {
                choice++;
                if (choice >= items) choice = 0;
            }
        }
        // Enter
        else if (key == 13)
        {
            if (choice == 0) { game_stages(map); return; }
            if (choice == 1) { Description(); return; }
            if (choice == 2) { exit_game(); return; }
        }
    }
}



// --------------------------------------------------

void game_stages(char map[13][50])
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    const int items = 3;
    int choice = 0;

    while (true)
    {
        system("cls");

        SetConsoleTextAttribute(hConsole, 7);
        cout<<"================================================"<<endl;
        cout<<"                   Game stages                 "<<endl;
        cout<<"================================================\n"<<endl;

        // stage 1
        if (choice == 0)
            SetConsoleTextAttribute(hConsole, 11);
        else
            SetConsoleTextAttribute(hConsole, 7);

        cout << (choice==0 ? "> " : "  ")
             << "1. The start of the adventure" << endl;

        // stage 2
        if (choice == 1)
            SetConsoleTextAttribute(hConsole, 11);
        else
            SetConsoleTextAttribute(hConsole, 7);

        cout << (choice==1 ? "> " : "  ")
             << "2. Walls of death" << endl;

        // stage 3
        if (choice == 2)
            SetConsoleTextAttribute(hConsole, 11);
        else
            SetConsoleTextAttribute(hConsole, 7);

        cout << (choice==2 ? "> " : "  ")
             << "3. Teleporting smart pigs" << endl;

        SetConsoleTextAttribute(hConsole, 7);
        cout<<"________________________________________________"<<endl;

        int key = _getch();

        if (key == 224)
        {
            key = _getch();

            if (key == 72) // up
            {
                choice--;
                if (choice < 0) choice = items - 1;
            }
            else if (key == 80) // down
            {
                choice++;
                if (choice >= items) choice = 0;
            }
        }
        else if (key == 13) // Enter
        {
            int stage = choice + 1;

            if(stage==1) loadmap(map,"abn.txt");
            if(stage==2) loadmap(map,"ab2.txt");
            if(stage==3) loadmap(map,"ab3.txt");

            int chances = (stage==3 ? 9 : 4);
            int destroyed = 0;
            int totalE = count_E(map);

            int px, py;
            find_player(map, px, py);

            while(chances > 0)
            {
                runmap(map, chances, destroyed, totalE);
                launch(map, stage, destroyed, chances, px, py);
                chances--;

                if(count_E(map) == 0)
                {
                    save_best_score(stage, destroyed);
                    show_win_screen();
                    return;
                }
            }

            save_best_score(stage, destroyed);
            runmap(map, 0, destroyed, totalE);
            return;
        }
    }
}


// --------------------------------------------------

void Description()
{
    system("cls");
    cout<<"================================================"<<endl;
    cout<<"                   Description                 "<<endl;
    cout<<"================================================"<<endl;
    cout<<"Simple Angry-Birds-like console game.\n";
    system("pause");
}

// --------------------------------------------------

void exit_game()
{
    system("cls");
    cout<<"End.\n";
}

// --------------------------------------------------

void loadmap(char map[13][50], const char filename[])
{
    ifstream file(filename);
    for (int i=0;i<13;i++)
        for (int j=0;j<50;j++)
            file >> map[i][j];
    file.close();
}

// --------------------------------------------------

int count_E(char map[13][50])
{
    int cnt = 0;
    for(int i=0;i<13;i++)
        for(int j=0;j<50;j++)
            if(map[i][j]=='E') cnt++;
    return cnt;
}

// --------------------------------------------------

void runmap(char map[13][50], int chances, int destroyed, int totalE)
{
    system("cls");

    cout << "Chances: ";
    for(int i=0;i<chances;i++) cout<<"*";

    cout << "                                ";
    cout << "(" << destroyed << "/" << totalE << ")\n\n";

    for (int i=0;i<13;i++)
    {
        for (int j=0;j<50;j++)
            cout << map[i][j];
        cout << endl;
    }

    this_thread::sleep_for(chrono::milliseconds(200));
}

// --------------------------------------------------

void find_player(char map[13][50], int &px, int &py)
{
    for (int i=0;i<13;i++)
        for (int j=0;j<50;j++)
            if (map[i][j] == 'P')
            {
                px = i;
                py = j;
                return;
            }
}

// --------------------------------------------------

void toggle_walls(char map[13][50], bool &state)
{
    state = !state;
    for(int i=0;i<13;i++)
        for(int j=0;j<50;j++)
            if(map[i][j] == '$')
                map[i][j] = (state ? '#' : '.');
}

// --------------------------------------------------

void launch(char map[13][50], int stage, int &destroyed, int chances, int px, int py)
{
    int i,j;
    cout<<"Enter i (up): ";
    cin>>i;
    cout<<"Enter j (right): ";
    cin>>j;

    int x = px;
    int y = py;

    bool wall_state = true;

    while (i >= 0)
    {
        int nx = x - i;
        int ny = y + j;

        if(stage == 2)
            toggle_walls(map, wall_state);

        if (collision(map,nx,ny,destroyed))
            break;

        map[nx][ny] = '*';
        runmap(map, chances, destroyed, count_E(map)+destroyed);
        map[nx][ny] = '.';

        x = nx;
        y = ny;
        i--;
    }
}

// --------------------------------------------------

bool collision(char map[13][50], int x, int y, int &destroyed)
{
    if (x<0 || y<0 || x>=13 || y>=50)
        return true;

    if (map[x][y] == '#')
        return true;

    if (map[x][y] == 'E')
    {
        destroyed++;
        map[x][y] = '.';
        return true;
    }

    return false;
}

// --------------------------------------------------

void save_best_score(int stage, int destroyed)
{
    int score[3] = {0,0,0};

    ifstream in("abm.txt");
    for(int i=0;i<3;i++)
        in >> score[i];
    in.close();

    if(destroyed > score[stage-1])
        score[stage-1] = destroyed;

    ofstream out("abm.txt");
    for(int i=0;i<3;i++)
        out << score[i] << endl;
    out.close();
}

// --------------------------------------------------

void show_win_screen()
{
    char win_map[13][50];
    ifstream file("win.txt");

    for(int i=0;i<13;i++)
        for(int j=0;j<50;j++)
            file >> win_map[i][j];

    file.close();

    system("cls");
    for(int i=0;i<13;i++)
    {
        for(int j=0;j<50;j++)
            cout << win_map[i][j];
        cout << endl;
    }

    this_thread::sleep_for(chrono::seconds(4));
}



