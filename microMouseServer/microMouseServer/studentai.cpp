#include "string"
#include "micromouseserver.h"
#include <iostream>
using namespace std;

void printArray(int (&map)[20][20]){
    for(int i=19; i>0; i--){
        for(int j=0; j<20; j++){
            cout <<map[i][j]<<" ";
        }
        cout <<endl;
    }
}
//rohit has a cat

void directionLeft(int *direction){
    if(!(*direction-1<0)){
        *direction--;
    } else {
        *direction=4;
    }
}

void directionRight(int *direction){
    if(!(*direction+1>4)){
        *direction++;
    } else {
        *direction=1;
    }
}

void movement(int *x, int *y, int *direction){
    if(*direction==1){
        *y += 1;
    } else if(*direction==2){
        *x +=1;
    } else if(*direction==3){
        *y -=1;
    } else {
        *x -=1;
    }
}

void microMouseServer::studentAI()
{
    static int x = 0;
    static int y = 0;
    static int lefts = 0;
    static int rights = 0;
    static int forwards = 0;

    static int direction = 1;

    static int map[20][20];

    if(isWallLeft()){
        if(isWallForward()){
            if(isWallRight()){
                directionRight(&direction);
                turnRight();
                forwards=0;
            } else {
                turnRight();
                directionRight(&direction);
                rights++;
                lefts=0;
                forwards=0;
                moveForward();
                forwards++;
               movement(&x, &y, &direction);
            }
        } else {
            moveForward();
            forwards++;
            movement(&x, &y, &direction);
        }
    } else {
        turnLeft();
        directionLeft(&direction);
        lefts++;
        rights=0;
        forwards=0;
        moveForward();
        movement(&x, &y, &direction);
        forwards++;
    }

    map[x][y] += 1;

    if(forwards>2){
        lefts=0;
        rights=0;
    }

    if(lefts>=3){
        //printUI("You have found the end of the maze");
        printArray(map);
        foundFinish();
        lefts=0;
        rights=0;
    }
    else if(rights>=3){
        //printUI("You have found the end of the maze");
        printArray(map);
        foundFinish();
        lefts=0;
        rights=0;
    }

    //if(!isWallLeft() && ((timesLeft > timesForward) && (!isWallForward())));
    //if(!isWallLeft() && ((timesLeft > timesForward) && (!isWallForward())));

}
