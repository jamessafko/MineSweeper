#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

#ifndef score_h
#define score_h

class Score{
public:
    string name;
    int ticTacToeScore, minesweeperScore, connectFourScore, goFishScore,
    sodukuScore, currentScore, fileScore;
public:
    Score(string nameIn);
    int getFileScore();//Gets the score from your old game
    void updateFile();
};

Score::Score(string nameIn){
    name = nameIn;
    
    fileScore = getFileScore();
    ticTacToeScore = 0;
    minesweeperScore = 0;
    connectFourScore= 0;
    goFishScore = 0;
    sodukuScore = 0;
    currentScore = 0;
}

int Score::getFileScore(){
    string readIn = "";
    
    ifstream in(name + ".txt");
    if(in.fail()){//NOT EXIST
        cout<<"DNE"<<endl;
        in.close();//closes in stream
        ofstream out(name + ".txt");//creates out stream file with name
        out<<0;//writes a score of zero
        out.close();
        return 0;
    }
    else{//DOES EXIST
        while(!in.eof())//writes the score
            in >> readIn;
        in.close();
        return stoi(readIn);//returns the int version of score
    }
}

void Score::updateFile(){
    fstream file;
    fileScore += currentScore;
    file.open(name + ".txt");
    file << fileScore;
    file.close();
}




#endif /* score_h */
