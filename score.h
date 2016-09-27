/*SCORE CLASS
 Created by James Safko.
 Each instance of this class represents a player and assists with file i/o,
 and score management on name.txt files.
 EXAMPLE:
 For me, James, I would enter my name "James." After playing, my score would be saved
 to a file named "James.txt".
 */

#ifndef Score_h
#define Score_h

#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;


class Score{
public:
    string name;//Player's name
    int currentScore;//The score from this current gaming session
    int fileScore;//The score from their cumulative previous sessions (sourced from their .txt file)
    
    Score(string nameIn);//Constructor
    int getFileScore();//Reads in score from name.txt file
    void updateFile();//Updates the player's name.txt file with their score
};

Score::Score(string nameIn){
    name = nameIn;
    fileScore = getFileScore();//Assigns name.txt score (if there is one) to fileScore
    currentScore = 0;
}

//Reads in score from name.txt file
int Score::getFileScore(){
    string readIn = "";
    ifstream in;
    
    in.open((name + ".txt").c_str());//Opens name.txt file
    if(in.fail()){//If the file does not exist
        in.close();//closes in stream
        ofstream out((name + ".txt").c_str());//creates out stream file with name
        out<<0;//writes a score of zero
        out.close();
        return 0;//Returns score of zerp
    }
    else{//If the file name does exist
        while(!in.eof())//Takes the score
            in >> readIn;
        in.close();
        return (atoi(readIn.c_str()) + 0);//Converts the string to an int and returns it
    }
    return 0;
}

//Updates the player's name.txt file with their score
void Score::updateFile(){
    fstream file;
    fileScore += currentScore;//Updates fileScore.
    file.open((name + ".txt").c_str());//Opens name.txt file
    file << fileScore;//Writes new score in
    file.close();
}

#endif /* Score_h */
