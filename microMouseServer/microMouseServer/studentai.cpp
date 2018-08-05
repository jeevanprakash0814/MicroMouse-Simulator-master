#include "string"
#include "micromouseserver.h"
#include <iostream>
using namespace std;

void startMenu(int (&map)[20][20]){
    map[19][0] = 1;
}
void printArray(int (&map)[20][20]){
    for(int i=19; i>=0; i--){
        for(int j=0; j<20; j++){
            cout <<map[i][j]<<" ";
        }
        cout <<endl;
    }

    cout <<" "<<endl;//This is how you do System.out.println in C++

    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            cout <<map[i][j]<<" ";
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
    static int y = 19;
    static int lefts = 0;
    static int rights = 0;
    static int forwards = 0;
    static int randomCount = 0;
    static int direction = 0;

    static int map[20][20];

    if(randomCount<1){
        startMenu(map);
    }
    randomCount++;

    //y = same row;
    //x = same column;
    int timesLeft = 0;
    int timesForward = 0;
    int timesRight = 0;

    switch(direction){
        case 0:
        if(isWallLeft()){
            timesLeft = 99;
        } else {
            timesLeft = map[y][x - 1];
        }
        if(isWallForward()){
            timesForward = 99;
        } else {
            timesForward = map[y - 1][x];
        }
        if(isWallRight()){
            timesRight = 99;
        } else {
            timesRight = map[y][x + 1];
        }
        if( !isWallLeft() && !( ((timesLeft > timesForward) && !isWallForward()) || ((timesLeft > timesRight) && !isWallRight()) ) ){
            turnLeft();
            directionLeft(&direction);
            lefts++;
            rights=0;
            //forwards=0;
            moveForward();
            movement(&x, &y, &direction);
            //forwards++;
        }
        else if(!isWallForward() && !( (timesLeft > timesRight) && !isWallRight() ) ){
            moveForward();
            lefts = 0;
            rights = 0;
            //forwards++;
            movement(&x, &y, &direction);
        }
        else if(!isWallRight()){
            turnRight();
            directionRight(&direction);
            rights++;
            lefts=0;
            //forwards=0;
            moveForward();
            //forwards++;
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
            //forwards=0;
        }
        break;
        case 1:
        if(isWallLeft()){
            timesLeft = 99;
        } else {
            timesLeft = map[y - 1][x];
        }
        if(isWallForward()){
            timesForward = 99;
        } else {
            timesForward = map[y][x + 1];
        }
        if(isWallRight()){
            timesRight = 99;
        } else {
            timesRight = map[y + 1][x];
        }
        if( !isWallLeft() && !( ((timesLeft > timesForward) && !isWallForward()) || ((timesLeft > timesRight) && !isWallRight()) ) ){
            turnLeft();
            directionLeft(&direction);
            lefts++;
            rights=0;
            //forwards=0;
            moveForward();
            movement(&x, &y, &direction);
            //forwards++;
        }
        else if(!isWallForward() && !( (timesLeft > timesRight) && !isWallRight() ) ){
            moveForward();
            lefts = 0;
            rights = 0;
            //forwards++;
            movement(&x, &y, &direction);
        }
        else if(!isWallRight()){
            turnRight();
            directionRight(&direction);
            rights++;
            lefts=0;
            //forwards=0;
            moveForward();
            //forwards++;
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
            //forwards=0;
        }
        break;
        case 2:
        if(isWallLeft()){
            timesLeft = 99;
        } else {
            timesLeft = map[y][x + 1];
        }
        if(isWallForward()){
            timesForward = 99;
        } else {
            timesForward = map[y + 1][x];
        }
        if(isWallRight()){
            timesRight = 99;
        } else {
            timesRight = map[y][x - 1];
        }
        if( !isWallLeft() && !( ((timesLeft > timesForward) && !isWallForward()) || ((timesLeft > timesRight) && !isWallRight()) ) ){
            turnLeft();
            directionLeft(&direction);
            lefts++;
            rights=0;
            //forwards=0;
            moveForward();
            movement(&x, &y, &direction);
            //forwards++;
        }
        else if(!isWallForward() && !( (timesLeft > timesRight) && !isWallRight() ) ){
            moveForward();
            lefts = 0;
            rights = 0;
            //forwards++;
            movement(&x, &y, &direction);
        }
        else if(!isWallRight()){
            turnRight();
            directionRight(&direction);
            rights++;
            lefts=0;
            //forwards=0;
            moveForward();
            //forwards++;
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
            //forwards=0;
        }
        break;
        case 3:
        if(isWallLeft()){
            timesLeft = 99;
        } else {
            timesLeft = map[y + 1][x];
        }
        if(isWallForward()){
            timesForward = 99;
        } else {
            timesForward = map[y][x - 1];
        }
        if(isWallRight()){
            timesRight = 99;
        } else {
            timesRight = map[y - 1][x];
        }
        if( !isWallLeft() && !( ((timesLeft > timesForward) && !isWallForward()) || ((timesLeft > timesRight) && !isWallRight()) ) ){
            turnLeft();
            directionLeft(&direction);
            lefts++;
            rights=0;
            //forwards=0;
            moveForward();
            movement(&x, &y, &direction);
            //forwards++;
        }
        else if(!isWallForward() && !( (timesLeft > timesRight) && !isWallRight() ) ){
            moveForward();
            lefts = 0;
            rights = 0;
            //forwards++;
            movement(&x, &y, &direction);
        }
        else if(!isWallRight()){
            turnRight();
            directionRight(&direction);
            rights++;
            lefts=0;
            //forwards=0;
            moveForward();
            //forwards++;
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
            //forwards=0;
        }
        break;
    }

    /*
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

    */

    /*
    if you're turning right
        turnRight
        moveForward
        left = 0
        right++
    else if you're moving forward
        moveForward
        left = 0
        right = 0
    else if youre turning rihgt
        turnRight
        moveForward
        right++
        left = 0
    else (going back)
        right = 0
        left = 0
        turnRight
        turnRight
        moveForward
    */

    map[y][x] += 1;

    /*
    if(forwards>2){
        lefts=0;
        rights=0;
    }
    */

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

}
