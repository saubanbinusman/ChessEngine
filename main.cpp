#include "include\\actionList.h"
#include <iostream>
#include<iomanip>
#include "include\\chess.h"
#include "include\\autoPlayer.h"
#include "include\\humanPlayer.h"
#include "include\\minimaxPlayer.h"
#include "include\\ENUM.h"

using namespace std;

int main(){
    chess Game;
    // srand(time(NULL));
    Game.Players[1] = new autoPlayer(Black);
    Game.Players[0] = new minimaxPlayer(White);
    Game.playGame();
    
    return 0;
}
