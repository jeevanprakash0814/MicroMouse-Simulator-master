#include "string"
#include "micromouseserver.h"
#include <iostream>
using namespace std;

/*
 * Name: Jeevan Prakash
 * Version: 20180805
 *
*/

void printArray(int (&map)[MAZE_HEIGHT][MAZE_WIDTH]){
    for(int i=0; i<MAZE_HEIGHT; i++){
        for(int j=0; j<MAZE_HEIGHT; j++){
            cout <<map[i][j]<<"  ";
        }
        cout <<endl;
    }
}

void directionLeft(int *direction){
    *direction=(*direction+3)%4;
}

void directionRight(int *direction){
    *direction=(*direction+1)%4;
}

void movement(int *x, int *y, int *direction){
    if(*direction==0){
        *y -= 1;
    } else if(*direction==1){
        *x +=1;
    } else if(*direction==2){
        *y +=1;
    } else {
        *x -=1;
    }
}

void microMouseServer::studentAI()
{
    static int x = 0;
    static int y = MAZE_HEIGHT-1;
    static int lefts = 0;
    static int rights = 0;

    static bool beginning = true;

    static int direction = 0;

    static int map[MAZE_HEIGHT][MAZE_WIDTH];

    if(beginning){
        map[MAZE_HEIGHT-1][0] = 1;
    }

    //y = same row;
    //x = same column;
    int timesLeft = 0;
    int timesForward = 0;
    int timesRight = 0;

    switch(direction){
        case 0:
        if(isWallLeft()){
            timesLeft = INT_MAX;
        } else {
            timesLeft = map[y][x - 1];
        }
        if(isWallForward()){
            timesForward = INT_MAX;
        } else {
            timesForward = map[y - 1][x];
        }
        if(isWallRight()){
            timesRight = INT_MAX;
        } else {
            timesRight = map[y][x + 1];
        }
        break;
        case 1:
        if(isWallLeft()){
            timesLeft = INT_MAX;
        } else {
            timesLeft = map[y - 1][x];
        }
        if(isWallForward()){
            timesForward = INT_MAX;
        } else {
            timesForward = map[y][x + 1];
        }
        if(isWallRight()){
            timesRight = INT_MAX;
        } else {
            timesRight = map[y + 1][x];
        }
        break;
        case 2:
        if(isWallLeft()){
            timesLeft = INT_MAX;
        } else {
            timesLeft = map[y][x + 1];
        }
        if(isWallForward()){
            timesForward = INT_MAX;
        } else {
            timesForward = map[y + 1][x];
        }
        if(isWallRight()){
            timesRight = INT_MAX;
        } else {
            timesRight = map[y][x - 1];
        }
        break;
        case 3:
        if(isWallLeft()){
            timesLeft = INT_MAX;
        } else {
            timesLeft = map[y + 1][x];
        }
        if(isWallForward()){
            timesForward = INT_MAX;
        } else {
            timesForward = map[y][x - 1];
        }
        if(isWallRight()){
            timesRight = INT_MAX;
        } else {
            timesRight = map[y - 1][x];
        }
        break;
    }

    if( !isWallLeft() && !( ((timesLeft >= timesForward) && !isWallForward()) || ((timesLeft >= timesRight) && !isWallRight()) ) ){
        turnLeft();
        directionLeft(&direction);
        lefts++;
        rights=0;
        moveForward();
        movement(&x, &y, &direction);
    }
    else if(!isWallForward() && !( (timesLeft >= timesRight) && !isWallRight() ) ){
        moveForward();
        lefts = 0;
        rights = 0;
        movement(&x, &y, &direction);
    }
    else if(!isWallRight()){
        turnRight();
        directionRight(&direction);
        rights++;
        lefts=0;
        moveForward();
        movement(&x, &y, &direction);
    }
    else {
        directionRight(&direction);
        directionRight(&direction);
        rights = 0;
        lefts = 0;
        turnRight();
        turnRight();
        moveForward();
        movement(&x, &y, &direction);
    }

    map[y][x] += 1;

    if(lefts>=3){
        printArray(map);
        foundFinish();
        lefts=0;
        rights=0;
    }
    else if(rights>=3){
        printArray(map);
        foundFinish();
        lefts=0;
        rights=0;
    }

}
