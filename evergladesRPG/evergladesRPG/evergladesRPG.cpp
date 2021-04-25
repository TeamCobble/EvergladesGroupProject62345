/*
    Stanley Toussaint, Vladia Zouga, Anil Beesham

    evergladesRPG.cpp

    Lost in the everglades is a menu-driven RPG between a player and the computer by prompting the user inputs.
        1. See Rules
        2. Play Game
        3. Quit

    Input:

    Processing:

    Output:

*/


//Header files
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

//Function prototypes
void gameRules();
int returnToMain(int);


int movingChoice() {
    cout << "\n1 for up\n";
    cout << "2 for down\n";
    cout << "3 for left\n";
    cout << "4 for right\n";
    cout << "5 for up-right\n";
    cout << "6 for down-right\n";
    cout << "7 for up-left\n";
    cout << "8 for down-left\n";
    cout << "\nChoose: ";

    int choice;
    cin >> choice;

    return choice;
}

int* newXYInvalid(int choice, int x, int y) {
    int invalid = 0;
    switch (choice) {
    case 1: {
        if (x > 0) {
            x--;
        }
        else {
            cout << "invalid move.\n";
            invalid = 1;
        }
        break;
    }
    case 2: {
        if (x < 4) {
            x++;
        }
        else {
            cout << "invalid move.\n";
            invalid = 1;
        }
        break;
    }
    case 3: {
        if (y > 0) {
            y--;
        }
        else {
            cout << "invalid move.\n";
            invalid = 1;
        }
        break;
    }
    case 4: {
        if (y < 4) {
            y++;
        }
        else {
            cout << "invalid move.\n";
            invalid = 1;
        }
        break;
    }
    case 5: {

        if (x > 0 && y < 4) {
            x--;
            y++;
        }
        else {
            cout << "invalid move.\n";
            invalid = 1;
        }
        break;
    }
    case 6: {
        if (x < 4 && y < 4) {
            x++;
            y++;
        }
        else {
            cout << "invalid move.\n";
            invalid = 1;
        }
        break;
    }
    case 7: {
        if (x > 0 && y > 0) {
            x--;
            y--;
        }
        else {
            cout << "invalid move.\n";
            invalid = 1;
        }
        break;
    }
    case 8: {
        if (x < 4 && y>0) {
            x++;
            y--;
        }
        else {
            cout << "invalid move.\n";
            invalid = 1;
        }
        break;
    }
    default: {
        cout << "Please choose correct option.\n";
        break;
    }
    }


    int* ret = new int[3];
    ret[0] = x;
    ret[1] = y;
    ret[2] = invalid;
    return ret;
}
void init(char brd[][5], char dis[][5]) {
    // fill the board 
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
        {

            brd[i][j] = '*';
            dis[i][j] = '*';
        }
    }

}
void randomRanger(char brd[][5]) {
    int i = 0;
    // random 10 danger
    for (;;) {
        int a = rand() % 5;
        int b = rand() % 5;
        if (brd[a][b] == '*') {
            if (a != 0 || b != 0) {
                if (a != 4 || b != 4) {
                    brd[a][b] = 'd';
                    i++;
                }
            }
        }

        if (i == 10) {
            break;
        }
    }

}

int currentPoint(int p) {
    return(12 - p);
}

void play() {
    char brd[5][5];
    char dis[5][5];

    init(brd, dis);
    randomRanger(brd);


    // postion for ranger
    dis[0][0] = 'R';
    // postion for Tourist
    dis[4][4] = 'T';

    int point = 12;
    int p = 0;
    int x = 0, y = 0;
    while (p <= 12) {

        if (x == 4 && y == 4) {
            break;
        }

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                cout << dis[i][j] << " | ";
            }
            cout << endl;
        }
        cout << "Gongs Left: " << currentPoint(p) << endl;



        int choice = movingChoice();
        // previous postion
        int px = x;
        int py = y;

        int* values;
        values = newXYInvalid(choice, x, y);
        x = values[0];
        y = values[1];
        int invalid = values[2];



        if (invalid == 0) {
            // set '*' in previous postion
            dis[px][py] = ' ';



            if (brd[x][y] == 'd') {
                cout << "\n------ Danger ------\n";
                // random danger
                int r = rand() % 3;

                // random operation
                if (r == 0) {
                    cout << "\nHiding or wait.";
                    p += 5;
                }
                if (r == 1) {
                    cout << "\nRanger fights & wins.";
                    p += 2;
                }
                if (r == 2) {
                    cout << "\nRanger fights & loses.";
                    p += 3;
                    // reset position
                    x = 0;
                    y = 0;
                }
            }


            cout << endl;
            cout << endl;

            // new position for ranger
            dis[x][y] = 'R';
        }

    }


    // winn or loss
    if (p >= 12) {
        cout << "\n\nLoses the game.\n\n";
    }
    else {
        cout << "\n\nWon the game.\n\n";
    }

}


int main()
{ //Variables

    srand((unsigned int)time(NULL));
    int choice = -1;

    // for break the loop
    int brk = 1;
    // Rpg title page sections

    while (true) {
        brk = 1;
        cout << "[==========================================================]\n" << endl
            << "\tLost in the everglades RPG ..."
            << "\n" << endl;
        choice = returnToMain(choice);

        cout << "\n[========================|========|========================]" << endl << endl;
        // drive menu
        switch (choice)
        {
        case 1: // See rules
            gameRules();

            break;

        case 2: // play game
            play();
            break;
        case 3:
            cout << "\n   Thank you for playing Lost In The Everglades. Good bye! " << endl << endl;
            cout << "\n[==========================================================]" << endl;
            brk = 0;
            break;


        default: //Error for invalid entry
            cout << "\n\tError...Invalid option try again" << endl
                << "\n" << endl << endl;
        }
        if (brk != 1) {
            break;
        }

    }

    return 0;
}

void gameRules()
{// Shows the complete game rules
    cout << "\n"
        << "\tLost in the everglades RPG"
        << "\n\tGame Rules "
        << "\n" << endl;
    cout << "\n A group of tourists has been lost in the Everglades and a ranger must rescue them before time"
        << "\n runs out." << endl
        << "\n The Everglades are represented by a 5x5 matrix. The ranger(R) starts the rescue at the upper-left"
        << "\n corner of the park, the group of tourists(T) are lost at the lower-right corner. The ranger has"
        << "\n 12 gongs of time to find and rescue the tourists before they perish." << endl
        << "\n During the journey, the ranger might find dangers(hungry alligator, swarm of giant mosquitoes,"
        << "\n venomous spider or Python)." << endl
        << "\n\n When the ranger finds a danger, they can choose to fight them or hide and wait for them to"
        << "\n leave."
        << "\n\n\t• If the Ranger hides & waits"
        << "\n\t  o Moves to the desired cell"
        << "\n\t  o Loses 5 gongs of time"
        << "\n\n\t• If the Ranger fights & wins"
        << "\n\t  o Moves to the desired cell"
        << "\n\t  o Loses 2 gongs of time"
        << "\n\n\t• If the Ranger fights & loses"
        << "\n\t  o Goes back to the initial cell"
        << "\n\t  o Loses 3 gongs of time"
        << "\n\t  o The Danger remains in the cell" << endl << endl;

}

int returnToMain(int choice)
{

    cout << "\n"
        << "\n\t1. See game rules."
        << "\n\t2. Play Game."
        << "\n\t3. Quit "
        << "\n\n\tEnter your choice (1-3): ";
    cin >> choice;

    return choice;
}
