//check time
//scoring system

#include <vector>
#include <iostream>
#include <ctime>
#include <stdlib.h>

#ifndef minesweeperGame_h
#define minesweeperGame_h
using namespace std;

class Square {
    friend class Minesweeper;
    private:
        bool doPrint, isMine, isFlagged;
        int localMines;
        Square();
};

Square::Square(){
    doPrint = false;
    isMine = false;
    isFlagged = false;
    localMines = 0;
}


class Minesweeper{
    private:
        int numTiles, numMines, height, width, numActivated;
        time_t startTime;
        float score;
        vector<Square> mineField;
        bool firstSelect;
    public:
        Minesweeper();
        int startMenu();
        void startGame();
        
        void printMatrix();
        void game();
        
        void generateMines(int xNot, int yNot);
        void generateNonMines();
        void minesLeft(int &localMines, int r, int c);
        void minesRight(int &localMines, int r, int c);
        void minesUpLeft(int &localMines, int r, int c);
        void minesUpRight(int &localMines, int r, int c);
        void minesUp(int &localMines, int r, int c);
        void minesDownLeft(int &localMines, int r, int c);
        void minesDownRight(int &localMines, int r, int c);
        void minesDown(int &localMines, int r, int c);
        
        void endGame(string winlose);
    
        void printInfo();
    
        bool validation(int &userChoice, int start, int range);
};

Minesweeper::Minesweeper(){
    numActivated = 0;
    score = 0;
    numTiles = 0;
    startTime = 0;
    width = 0;
    height = 0;
}

/*INPUT VALIDATOR. Takes in the user's choice, start(lowest value allowed), range(number of choices possible)*/
bool Minesweeper::validation(int &userChoice, int start, int range){
    if(cin.fail()) {//If the data entered is a string, char, or non-int number
        cin.clear();//clear the instream
        cin.ignore(1000, '\n');//clear the buffer
        cout<<"Please enter an integer.\n"<<endl;
        return false;
    }
    else if(userChoice < start || userChoice > range){//out of range
        cout<<"Please enter a choice between " << start << " and "<< range <<".\n"<<endl;
        return false;
    }
    else
        return true;
}

int Minesweeper::startMenu(){
    bool done = false;
    bool done2 = false;
    bool done3 = false;
    int userChoice2 = 0;
    int userChoice = 0;
    
    while(!done){
        cout<<"\n\t\t Welcome to...\n\tM I N E S W E E P E R"<<endl<<endl;
        cout<<"1. Quit\n2. Rules\n3. Start game\n\nChoice: ";
        cin>>userChoice;
        cout<<endl;
        
        //Input validation
        if(!validation(userChoice, 1, 3))
            continue;

        //Processing choice
        switch (userChoice) {
            case 1://Quit
                done = true;
                break;
            case 2://Rules
                cout<<"\nR U L E S :\n"<<endl;
                cout<<"If you activate a square with a mine (square marked 'M'), the game ends."<<endl;
                cout<<"If you activate a square with a number, that number signifies how many mines"<<endl;
                cout<<"lie in the 8 surrounding squares.\n"<<endl;
                cout<<"Navigation: This game is represented by a grid with numbers representing each"<<endl;
                cout<<"row and column. When you are activating or flagging a square, you will be asked"<<endl;
                cout<<"To put in the appropriate row and column position of the desired square.\n"<<endl;
                cout<<"A tip: Flag the squares you believe to be mines. This will help you visualize"<<endl;
                cout<<"Where potential mines could be.\n"<<endl;
                cout<<"Scoring: If you win, your final score will be based upon the time you took"<<endl;
                cout<<"To uncover all non-mine spaces plus a bonus. If you lose, your score will be"<<endl;
                cout<<"based upon how many of your flagged squares were actually mines.\n\n"<<endl;
                break;
            case 3://Start Game

                done2 = false;
                while(!done2){
                    //Difficulty options
                    cout<<"\nD I F F I C U L T Y\n\n1. Easy\n2. Hard\n3. Custom\n4. Back\n\nChoice: ";

                    cin>>userChoice2;
                    
                    //Input validation
                    if(!validation(userChoice2, 1, 4))
                        continue;
                    
                    //Process difficulty choice
                    switch (userChoice2) {
                        case 1://Easy
                            width = 6;
                            height = 6;
                            numMines = 7;
                            numTiles = width * height;
                            startGame();
                            done2 = true;
                            done = true;
                            break;
                        case 2://Hard
                            width = 10;
                            height = 10;
                            numMines = 25;
                            numTiles = width * height;
                            startGame();
                            done2 = true;
                            done = true;
                            break;
                        case 3://Custom
                            done3 = false;
                            while(!done3){
                                cout<<"Please enter a width between 2 and 25: ";
                                cin>>width;
                                if(!validation(width, 2, 25))//Input Validation
                                    continue;
                                
                                cout<<"Please enter a height between 2 and 25: ";
                                cin>>height;
                                if(!validation(height, 2, 25))//Input Validation
                                    continue;
                                
                                numTiles = width * height;
                                cout<<"Please enter a number of mines between 0 and "<< numTiles-1<<": ";
                                cin>>numMines;
                                if(!validation(numMines, 0, (numTiles - 1)))//Input Validation
                                    continue;
                                done3 = true;
                            }
                            startGame();
                            done2 = true;
                            done = true;
                            break;
                        case 4:
                            cout<<endl;
                            done2 = true;
                            done = true;
                            break;
                        default:
                            break;
                    }
                }
                break;
        }
    }
    return score;
}

/*START GAME. Clears the mine field vector. Creates the start time. Remakes the square matrix*/
void Minesweeper::startGame(){
    firstSelect = true;
    mineField.clear();
    
    //initialize start time,
    startTime = time(0);
    
    //initializes the vector
    for(int i = 0; i < numTiles; i++)
        mineField.push_back(Square());
    
    //calls the game
    game();
}

/*Organizes how the player interacts with the game, taking in their input
 and calling the appropriate function.*/
void Minesweeper::game(){
    int userChoice = 0;
    bool done2 = false;
    bool done = false;
    
    //This loops facilitates the user's choices
    while(!done){
        //prints the matrix
        printMatrix();
        
        //User choice
        cout<<"\t\t\t\t\t\tO P T I O N S\n1. Flag/unflag a square\t\t2. Activate a square\t\t3. Quit"<<endl;
        cout<<"Choice: ";
        cin>>userChoice;//user validation
        if(!validation(userChoice, 1, 3))
            continue;
        cout<<endl;
        
        int x, y;
        switch (userChoice) {
            case 1://Flag a square
                done2 = false;
                while(!done2){
                    //chose square
                    cout<<"Flagging square...\nPress enter 0 to go back.\n\nInput row number: ";
                    cin>>x;
                    if(x == 0)//back
                        break;
                    if(!validation(x, 1, width))//Input validation
                        break;
                    
                    cout<<"Enter column number: ";
                    cin>>y;
                    if(y == 0)//back
                        break;
                    if(!validation(y, 1, height))//Input validation
                        break;
                    
                    //Make the square flagged/unflagged
                    mineField[x-1 + ((y-1) * width)].isFlagged = !mineField[x-1 + ((y-1) * width)].isFlagged;
                    
                    done2 = true;//exit this loop
                    break;
                }
                break;
            case 2://Activate a square
                done2 = false;
                while(!done2){
                    //choose square
                    cout<<"Activating square...\nPress enter 0 to go back.\n\nInput row number: ";
                    cin>>x;
                    if(x == 0)//back
                        break;
                    if(!validation(x, 1, width))//Input validation
                        break;
                    cout<<"Enter column number: ";
                    cin>>y;
                    if(y == 0)//back
                        break;
                    if(!validation(y, 1, height))//Input validation
                        break;
                    
                    /*If this is the first selection, the squares must be labelled after (to prevent the first square
                     selected from being a mine)*/
                    if(firstSelect){
                        generateMines(x, y);
                        generateNonMines();
                        firstSelect = false;
                    }
                    
                    //If you have already activated this square
                    else if(mineField[x-1 + ((y-1) * width)].doPrint == true){
                        cout<<"\nYou have already activated this square."<<endl;
                        break;
                    }

                    //Make the chose square printable
                    mineField[x-1 + ((y-1) * width)].doPrint = true;
                    
                    //If it was a successful activation
                    numActivated++;
                    
                    //Did I lose?
                    if(mineField[x-1 + ((y-1) * width)].isMine){//lose
                        done = true;//exit outer loop
                        endGame("lose");
                    }
                    //Did I win?
                    else if(numActivated == numTiles - numMines){
                        done = true;//exit outer loop
                        endGame("win");
                    }
                    
                    done2 = true;//exit this loop
                }
                
                break;
            
            case 3://Quit
                done = true;
                endGame("draw");
                break;
            default:
                break;
        }
    }
}

/*Prints out the matrix of the game*/
void Minesweeper::printMatrix(){
    int r = 0;
    int c = 0;
    
    //column index
    cout<<endl<<"   ";//initial indent
    for(c = 0; c < width; c++){
        if(c+1 >= 10)//smaller spaces to fit 2 digit numbers
            cout<<"  "<<c+1;
        else
            cout<<"  "<<c+1<<" ";
    }
    cout<<endl;
    
    for(r = 0; r < height; r++){
        //top bar above row r
        cout<<"   ";
        for(c = 0; c < height; c++)
            cout<<"+---";
        cout<<"+"<<endl;
        
        //row index
        if(r+1 >= 10)
            cout<< r+1 << " ";//row value
        else
            cout<< r+1 << "  ";//row value
        
        //Data for row r
        for(c = 0; c < width; c++){//prints
            cout<< "| ";//value

            if(mineField[r + (c * width)].isFlagged == true && !mineField[r + (c * width)].doPrint)//if it's flagged
                cout<<"F ";
            else if(mineField[r + (c * width)].doPrint){//If this square is to be printed
                if(mineField[r + (c * width)].isMine){//If it's a mine
                    cout<<"M ";
                    //end game
                }
                else
                    cout<<mineField[r + (c * width)].localMines<<" ";
            }
            else//no print
                cout<<"  ";
        }
        cout<<"|"<<endl;
    }
    
    //bottom row
    cout<<"   ";
    for(int c = 0; c < width; c++)
        cout<<"+---";
    cout<<"+"<<endl<<endl;
}


/*GENERATES MINES. Taking in the first selection location, this generates randomly the
 location of the mines (but not on the first selection location)*/
void Minesweeper::generateMines(int xNot, int yNot){
    int x, y, r, c;
    int i = 0;
    srand((int)time(NULL));//seed the random number
    while(i < numMines){
        //generate random values for the mines
        x = rand() % width + 1;//x position on the display (between 1 and width)
        y = rand() % height + 1;//y position on the screen (between 1 and height)
        c = x - 1;//actual column index (between 0 and width - 1)
        r = y - 1;//actual row index (between 0 and height - 1)
        
        //checks to see if this was the chosen block or already is a mine
        if((y == yNot && x == xNot) || mineField[r +(c * width)].isMine){
            continue;
        }
        mineField[r + (c * width)].isMine = true;
        i++;
    }
}

void Minesweeper::minesLeft(int &localMines, int r, int c){
    if(mineField[r + ((c-1) * width)].isMine)//left
        localMines++;
}
void Minesweeper::minesRight(int &localMines, int r, int c){
    if(mineField[r + ((c+1) * width)].isMine)//right
        localMines++;
}
void Minesweeper::minesUpLeft(int &localMines, int r, int c){
    if(mineField[r-1 + ((c-1) * width)].isMine)//up and left
        localMines++;
}
void Minesweeper::minesUpRight(int &localMines, int r, int c){
    if(mineField[r-1 + ((c+1) * width)].isMine)//up and right
        localMines++;
}
void Minesweeper::minesUp(int &localMines, int r, int c){
    if(mineField[r-1 + (c * width)].isMine)//up
        localMines++;
}
void Minesweeper::minesDownLeft(int &localMines, int r, int c){
    if(mineField[r+1 + ((c-1) * width)].isMine)//down and left
        localMines++;
}
void Minesweeper::minesDownRight(int &localMines, int r, int c){
    if(mineField[r+1 + ((c+1) * width)].isMine)//down and right
        localMines++;
}
void Minesweeper::minesDown(int &localMines, int r, int c){
    if(mineField[r+1 + (c * width)].isMine)//down
        localMines++;
}


/*GENERATES NON MINES SQUARES. Loops through each index in the array and calculates how many of the adjacent
 indexes are mines. */
void Minesweeper::generateNonMines(){
    int localMines = 0;
    for(int r = 0; r < height; r++){
        for(int c = 0; c < width; c++){
            localMines = 0;
            if(mineField[r + (c * width)].isMine){//if this space is a mine
                continue;
            }
            else{//calculate local mines
                if(c == width - 1 && r == 0){//top right corner
                    minesDown(localMines, r, c);
                    minesDownLeft(localMines, r, c);
                    minesLeft(localMines, r, c);
                }
                else if(c == width - 1 && r == height - 1){//bottom right corner
                    minesUp(localMines, r, c);
                    minesLeft(localMines, r, c);
                    minesUpLeft(localMines, r, c);
                }
                else if(c == 0 && r == height - 1){//bottom left corner
                    minesUp(localMines, r, c);
                    minesRight(localMines, r, c);
                    minesUpRight(localMines, r, c);
                }
                else if(c == 0 && r == 0){//top left corner
                    minesDown(localMines, r, c);
                    minesRight(localMines, r, c);
                    minesDownRight(localMines, r, c);
                }
                else if(c == width - 1){//right edge
                    minesUp(localMines, r, c);
                    minesLeft(localMines, r, c);
                    minesUpLeft(localMines, r, c);
                    minesDownLeft(localMines, r, c);
                    minesDown(localMines, r, c);
                }
                else if(c == 0){//left edge
                    minesUp(localMines, r, c);
                    minesRight(localMines, r, c);
                    minesUpRight(localMines, r, c);
                    minesDownRight(localMines, r, c);
                    minesDown(localMines, r, c);
                }
                else if(r == 0){//top edge
                    minesLeft(localMines, r, c);
                    minesRight(localMines, r, c);
                    minesDown(localMines, r, c);
                    minesDownLeft(localMines, r, c);
                    minesDownRight(localMines, r, c);
                }
                else if(r == height - 1){//bottom edge
                    minesLeft(localMines, r, c);
                    minesRight(localMines, r, c);
                    minesUp(localMines, r, c);
                    minesUpLeft(localMines, r, c);
                    minesUpRight(localMines, r, c);
                }
                else{//everything else
                    minesLeft(localMines, r, c);
                    minesRight(localMines, r, c);
                    minesUp(localMines, r, c);
                    minesUpLeft(localMines, r, c);
                    minesUpRight(localMines, r, c);
                    minesDown(localMines, r, c);
                    minesDownLeft(localMines, r, c);
                    minesDownRight(localMines, r, c);
                }
                mineField[r + (c * width)].localMines = localMines;//update local mines
            }
        }
    }
}

/*Called if you hit a mine or if you activate all squares not occupied by mines. Passes in string "lose", "win", or "draw."*/
void Minesweeper::endGame(string winlose){
    int flaggedRight = 0;
    int activatedSafely = 0;
    float timeTaken = 0;
    
    if(winlose == "lose"){//If you lost
        cout<<"\nYou hit a mine!"<<endl;
        for(int i = 0; i < numTiles; i++){
            if(mineField[i].isMine && mineField[i].isFlagged)//If you flagged a square that was a mine
                flaggedRight++;
            if(mineField[i].doPrint && !mineField[i].isMine)//If you activated the square without it being a mine
                activatedSafely++;
        }
        cout<<"\nYou flagged "<<flaggedRight<<" squares that were mines, and activated "<< activatedSafely <<" squares without activating a mine."<<endl;
        score += (100 * activatedSafely/(numTiles-numMines));
    }
    else if(winlose == "draw")//If you quit
        cout<<"\nYou quit."<<endl;
    else{//If you won
        cout<<"\nYou won!"<<endl;
        score = 100;
    }
    
    timeTaken = (float) difftime(time(0), startTime);//Find how long they spent
    /*The score scales with the number of tiles used.
     The longer you take, the less points you receive.
     If you lose, you receieve points for the amount of mines you flagged correctly and the number of
     tiles you activated without them being mines.*/
    if(score < 0)//If the score becomes negative, set it to zero
        score = 0;

    cout<<"It took you "<< timeTaken <<" seconds to play."<<endl;
    cout<<"Your final score is "<<score<<endl;
}

/*Prints all square's info (debugging tool)*/
void Minesweeper::printInfo(){
    int size = (int) mineField.size();
    for(int i = 0; i < size; i++){
        cout<<"space "<<i<<endl;
        cout<<"doPrint "<<mineField[i].doPrint<<endl;
        cout<<"isMine "<<mineField[i].isMine<<endl;
        cout<<"isFlagged "<<mineField[i].isFlagged<<endl;
        cout<<"localMines "<<mineField[i].localMines<<endl<<endl;
    }
}

#endif /* minesweeperGame_h */
