#include "string"
#include "micromouseserver.h"
#include <iostream>
using namespace std;

/*
 * Name: Jeevan Prakash
 * Version: 20180811
 *
*/

struct square{
public:
    int x = 0;
    int y = 0;
    int visits = 0;
    bool visited = false;
    bool visitable = false;

    square *forward;
    square *right;
    square *left;
    square *bottom;
};

void populateArray(square (&map)[MAZE_HEIGHT][MAZE_WIDTH]){
    for(int i=0; i<MAZE_HEIGHT; i++){
        for(int j=0; j<MAZE_HEIGHT; j++){
            map[i][j].x = j;
            map[i][j].y = i;
        }
    }
}

void printArray(square (&map)[MAZE_HEIGHT][MAZE_WIDTH]){
    for(int i=0; i<MAZE_HEIGHT; i++){
        for(int j=0; j<MAZE_HEIGHT; j++){
            cout <<map[i][j].visits<<"  ";
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

    static list<square> queue;
    static square map[MAZE_HEIGHT][MAZE_WIDTH];

    if(beginning){
        populateArray(map);
        map[MAZE_HEIGHT-1][0].visits = 1;
        queue.push_back(map[MAZE_HEIGHT-1][0]);
    }
    beginning = false;
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
            timesLeft = map[y][x - 1].visits;
            map[y][x].left = &map[y][x - 1];
            map[y][x].left->visitable = true;
        }
        if(isWallForward()){
            timesForward = INT_MAX;
        } else {
            timesForward = map[y - 1][x].visits;
            map[y][x].forward = &map[y - 1][x];
            map[y][x].forward->visitable = true;
        }
        if(isWallRight()){
            timesRight = INT_MAX;
        } else {
            timesRight = map[y][x + 1].visits;
            map[y][x].right = &map[y][x + 1];
            map[y][x].right->visitable = true;
        }
        if(!(y+1>19)){
            map[y][x].bottom = &map[y + 1][x];
            map[y][x].bottom->visitable = true;
        }
        break;
        case 1:
        if(isWallLeft()){
            timesLeft = INT_MAX;
        } else {
            timesLeft = map[y - 1][x].visits;
            map[y][x].forward = &map[y - 1][x];
            map[y][x].forward->visitable = true;
        }
        if(isWallForward()){
            timesForward = INT_MAX;
        } else {
            timesForward = map[y][x + 1].visits;
            map[y][x].right = &map[y][x + 1];
            map[y][x].right->visitable = true;
        }
        if(isWallRight()){
            timesRight = INT_MAX;
        } else {
            timesRight = map[y + 1][x].visits;
            map[y][x].bottom = &map[y + 1][x];
            map[y][x].bottom->visitable = true;
        }
        if(!(x-1<0)){
            map[y][x].left = &map[y][x - 1];
            map[y][x].left->visitable = true;
        }
        break;
        case 2:
        if(isWallLeft()){
            timesLeft = INT_MAX;
        } else {
            timesLeft = map[y][x + 1].visits;
            map[y][x].right = &map[y][x + 1];
            map[y][x].right->visitable = true;
        }
        if(isWallForward()){
            timesForward = INT_MAX;
        } else {
            timesForward = map[y + 1][x].visits;
            map[y][x].bottom = &map[y + 1][x];
            map[y][x].bottom->visitable = true;
        }
        if(isWallRight()){
            timesRight = INT_MAX;
        } else {
            timesRight = map[y][x - 1].visits;
            map[y][x].left = &map[y][x - 1];
            map[y][x].left->visitable = true;
        }
        if(!(y-1<0)){
            map[y][x].forward = &map[y - 1][x];
            map[y][x].forward->visitable = true;
        }
        break;
        case 3:
        if(isWallLeft()){
            timesLeft = INT_MAX;
        } else {
            timesLeft = map[y + 1][x].visits;
            map[y][x].bottom = &map[y + 1][x];
            map[y][x].bottom->visitable = true;
        }
        if(isWallForward()){
            timesForward = INT_MAX;
        } else {
            timesForward = map[y][x - 1].visits;
            map[y][x].left = &map[y][x - 1];
            map[y][x].left->visitable = true;
        }
        if(isWallRight()){
            timesRight = INT_MAX;
        } else {
            timesRight = map[y - 1][x].visits;
            map[y][x].forward = &map[y - 1][x];
            map[y][x].forward->visitable = true;
        }
        if(!(x+1>19)){
            map[y][x].right = &map[y][x + 1];
            map[y][x].right->visitable = true;
        }
        break;
    }

    if(!queue.empty()){
        queue.pop_front();
        if(map[y][x].forward->visited == false && map[y][x].forward->visitable == true){
            queue.push_back(map[y][x].forward);
        }
        if(map[y][x].right->visited == false && map[y][x].right->visitable == true){
            queue.push_back(map[y][x].right);
        }
        if(map[y][x].left->visited == false && map[y][x].left->visitable == true){
            queue.push_back(map[y][x].left);
        }
        if(map[y][x].bottom->visited == false && map[y][x].bottom->visitable == true){
            queue.push_back(map[y][x].bottom);
        }
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

    map[y][x].visits += 1;
    map[y][x].visited = true;

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
