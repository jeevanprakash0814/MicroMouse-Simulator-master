#include "string"
#include "micromouseserver.h"
#include <iostream>
#include <list>
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
    bool shortest = false;

    square *previousNode;
    square *forward;
    square *right;
    square *left;
    square *bottom;
};

void shortestPathCalculation(square (&map)[MAZE_HEIGHT][MAZE_WIDTH], list<square*> queue){
    queue.push_back(&map[MAZE_HEIGHT-1][0]);
    square* s;
    while(!queue.empty()){
        s = queue.front();
        if(s->forward->visited == false && s->forward->visitable == true){
            s->forward->visited = true;
            s->forward->previousNode = queue.back();
            queue.push_back(s->forward);
            //queue.back()->previousNode = s;
        }
        if(s->right->visited == false && s->right->visitable == true){
            s->right->visited = true;
            s->right->previousNode = queue.back();
            queue.push_back(s->right);
        }
        if(s->left->visited == false && s->left->visitable == true){
            s->left->visited = true;
            s->left->previousNode = queue.back();
            queue.push_back(s->left);
        }
        if(s->bottom->visited == false && s->bottom->visitable == true){
            s->bottom->visited = true;
            s->bottom->previousNode = queue.back();
            queue.push_back(s->bottom);
        }
        queue.pop_front();
    }

    square* currentNode = s;
    int x = currentNode->x;
    int y = currentNode->y;
    square* z;
    while(x != 0 && y != 19){
        currentNode->shortest = true;
        currentNode = currentNode->previousNode;
        x = currentNode->x;
        y = currentNode->y;
    }
}

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

    static int xFinish;
    static int yFinish;

    static bool beginning = true;

    static int direction = 0;

    static list<square*> queue;
    static square map[MAZE_HEIGHT][MAZE_WIDTH];

    if(beginning){
        populateArray(map);
        map[MAZE_HEIGHT-1][0].visits = 1;
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
        xFinish = x;
        yFinish = y;
        shortestPathCalculation(map, queue);
    }
    else if(rights>=3){
        printArray(map);
        foundFinish();
        lefts=0;
        rights=0;
        xFinish = x;
        yFinish = y;
        shortestPathCalculation(map, queue);
    }

}
