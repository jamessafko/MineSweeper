/*A game of MineSweeper by James Safko
 
 This minesweeper.cpp holds the main menus and calls minesweeperGame.h when the game begins.
 
 When the game is called, it operates just by using that game's class methods. Once the game ends,
 the stack returns to the main menu with an integer score.
 
 SCORING
 We utilize a file i/o system that automatically saves user's scores to text files,
 which are automatically recalled when they play the game at a later time.
 
 We have a hash map of Score objects. Each Score object holds a player's score data.
 
 When the player enters their names...
 if (they don't have a score object in the score map){
    if(they don't have a name.txt file with a score){
        it will create a .txt file for them and add them to the score map
    }
    if(they do have a name.txt file with a score){
    it will add a score object to the score map
    }
 }
 */

#include <iostream>
#include <fstream>
#include <map>
#include "score.h"
#include "minesweeperGame.h"

void askOnePlayerName(string &currP1, map<string, Score> &scoreMap){
    cout << "Who is playing this game? "<<endl;
    cin>>currP1;
    if(scoreMap.count(currP1)==0)//Equal to zero if there is no mathcing name
        scoreMap.emplace(currP1, Score(currP1));//Makes a new name
    else
        cout<<"Welcome back, "<<currP1<<"!"<<endl;
}

void printScore(map <string, Score> scoreMap){
    string name = "";
    string readIn = "";
    
    //update overall scores
    map <string, Score>::iterator iter;
    for(iter = scoreMap.begin(); iter != scoreMap.end(); iter++){//iterates through score map
        iter->second.updateFile();
    }
    
    cout<<"Who's overal score would you like to view?"<<endl;
    cin>>name;
    
    //All time cumulative score
    ifstream in(name + ".txt");
    if(in.fail()){//NOT EXIST
        cout<<"No profile with this name exists. Please play some games under this name first!"<<endl;
        in.close();//closes in stream
    }
    else{//DOES EXIST
        while(!in.eof())//writes the score
            in >> readIn;
        in.close();
        cout<<name<<"'s all time cumulative score is "<<stoi(readIn)<<endl;//returns the int version of score
        
        //Score from this current gaming session
        if(scoreMap.count(name)==0)//Equal to zero if there is no mathcing name
            cout<<name<<" has no current score from this gaming session."<<endl;
        else
            cout<<name<<" has a score of "<<scoreMap.at(name).currentScore<<" for this current gaming session."<<endl;
    }
}

int main(int argc, const char * argv[]) {
    //initialize objects
    map <string, Score> scoreMap;
    Minesweeper minesweeper;
    int choice;
    string currP1 = "";
    string currP2 = "";
    
    while(choice != 3){
        currP1 = "";
        cout<<  "|--------------------------------------| \n" <<
        "|                                      |\n" <<
        "|                                      |\n" <<
        "|            W e l c o m e             |\n" <<
        "|                  to                  |\n" <<
        "|              MineSweeper             |\n" <<
        "|--------------------------------------|\n" <<
        
        "\n \t 1. Play MineSweeper "<<
        "\n \t 2. Check your score "<<
        "\n \t 3. Quit  " <<endl<<
        "Enter your choice and press enter: ";
        cin >> choice;
        cout<<endl;
        switch (choice) {
            case 1:
                askOnePlayerName(currP1, scoreMap);
                scoreMap.at(currP1).currentScore += minesweeper.startMenu();
                break;
            case 2:
                printScore(scoreMap);
                break;
            case 3:
                //back
                break;
            default:
                cout << "Enter choice 1-3"<<endl;
                break;
        }
    }
    
    return 0;
}
