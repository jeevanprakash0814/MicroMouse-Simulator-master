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
    bool shortest = false;

    square *previousNode;
    square *forward;
    square *right;
    square *left;
    square *bottom;
};

void printShortestPath(square (&map)[MAZE_HEIGHT][MAZE_WIDTH]){
    for(int i=0; i<MAZE_HEIGHT; i++){
        for(int j=0; j<MAZE_HEIGHT; j++){
            if(map[i][j].shortest){
                cout <<"1"<<"  ";
            } else {
                cout <<"0"<<"  ";
            }
        }
        cout <<endl;
    }
}

void shortestPathCalculation(square (&map)[MAZE_HEIGHT][MAZE_WIDTH], list<square*> queue, bool *foundShortestpath, int *xFinish, int *yFinish){
    queue.push_back(&map[MAZE_HEIGHT-1][0]);
    square* s;
    while(!queue.empty() && (queue.front()->x != *xFinish || queue.front()->y != *yFinish)){
        s = queue.front();
            if(s->forward != NULL && !s->forward->visited){
                s->forward->visited = true;
                s->forward->previousNode = s;
                queue.push_back(s->forward);
                //queue.back()->previousNode = s;
        }
            if(s->right != NULL && !s->right->visited){
                s->right->visited = true;
                s->right->previousNode = s;
                queue.push_back(s->right);
        }
            if(s->left != NULL && !s->left->visited){
                s->left->visited = true;
                s->left->previousNode = s;
                queue.push_back(s->left);
        }
            if(s->bottom != NULL && !s->bottom->visited){
                s->bottom->visited = true;
                s->bottom->previousNode = s;
                queue.push_back(s->bottom);
        }
        queue.pop_front();
    }

    square* currentNode = s;
    int x = currentNode->x;
    int y = currentNode->y;

    /*
    while(currentNode->previousNode != NULL){
        shortPath.push_back(currentNode);
        currentNode = currentNode->previousNode;
    }*/

    while((x != 0) || (y != 19)){
        currentNode->shortest = true;
        if(currentNode->previousNode != NULL){
            currentNode = currentNode->previousNode;
        }
        x = currentNode->x;
        y = currentNode->y;
    }

    *foundShortestpath = true;
    printShortestPath(&map);
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

    static int xFinish = 0;
    static int yFinish = 0;

    static bool beginning = true;
    static bool beginning2 = true;
    static bool foundShortestPath = false;
    static bool isNull = false; //I USE THIS VARIABLE IF I NEED TO BREAK FROM THE IF-ELSE CHAIN
    //THAT IT IS BEING USED IN

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

    if(!foundShortestPath){
        switch(direction){
            case 0:
            if(isWallLeft()){
                timesLeft = INT_MAX;
            } else {
                timesLeft = map[y][x - 1].visits;
                map[y][x].left = &map[y][x - 1];
            }
            if(isWallForward()){
                timesForward = INT_MAX;
            } else {
                timesForward = map[y - 1][x].visits;
                map[y][x].forward = &map[y - 1][x];
            }
            if(isWallRight()){
                timesRight = INT_MAX;
            } else {
                timesRight = map[y][x + 1].visits;
                map[y][x].right = &map[y][x + 1];
            }
            if(!(y+1>19)){
                map[y][x].bottom = &map[y + 1][x];
            }
            break;
            case 1:
            if(isWallLeft()){
                timesLeft = INT_MAX;
            } else {
                timesLeft = map[y - 1][x].visits;
                map[y][x].forward = &map[y - 1][x];

            }
            if(isWallForward()){
                timesForward = INT_MAX;
            } else {
                timesForward = map[y][x + 1].visits;
                map[y][x].right = &map[y][x + 1];
            }
            if(isWallRight()){
                timesRight = INT_MAX;
            } else {
                timesRight = map[y + 1][x].visits;
                map[y][x].bottom = &map[y + 1][x];
            }
            if(!(x-1<0)){
                map[y][x].left = &map[y][x - 1];
            }
            break;
            case 2:
            if(isWallLeft()){
                timesLeft = INT_MAX;
            } else {
                timesLeft = map[y][x + 1].visits;
                map[y][x].right = &map[y][x + 1];
            }
            if(isWallForward()){
                timesForward = INT_MAX;
            } else {
                timesForward = map[y + 1][x].visits;
                map[y][x].bottom = &map[y + 1][x];
            }
            if(isWallRight()){
                timesRight = INT_MAX;
            } else {
                timesRight = map[y][x - 1].visits;
                map[y][x].left = &map[y][x - 1];
            }
            if(!(y-1<0)){
                map[y][x].forward = &map[y - 1][x];
            }
            break;
            case 3:
            if(isWallLeft()){
                timesLeft = INT_MAX;
            } else {
                timesLeft = map[y + 1][x].visits;
                map[y][x].bottom = &map[y + 1][x];
            }
            if(isWallForward()){
                timesForward = INT_MAX;
            } else {
                timesForward = map[y][x - 1].visits;
                map[y][x].left = &map[y][x - 1];
            }
            if(isWallRight()){
                timesRight = INT_MAX;
            } else {
                timesRight = map[y - 1][x].visits;
                map[y][x].forward = &map[y - 1][x];
            }
            if(!(x+1>19)){
                map[y][x].right = &map[y][x + 1];
            }
            break;
        }

        if(!isWallLeft() && !(((timesLeft >= timesForward) && !isWallForward()) || ((timesLeft >= timesRight) && !isWallRight()))){
            turnLeft();
            directionLeft(&direction);
            lefts++;
            rights=0;
            moveForward();
            movement(&x, &y, &direction);
        } else if(!isWallForward() && !((timesLeft >= timesRight) && !isWallRight())){
            moveForward();
            lefts = 0;
            rights = 0;
            movement(&x, &y, &direction);
        } else if(!isWallRight()){
            turnRight();
            directionRight(&direction);
            rights++;
            lefts=0;
            moveForward();
            movement(&x, &y, &direction);
        } else {
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
        //map[y][x].visited = true;

        if(lefts>=3){
            printArray(map);
            foundFinish();
            lefts=0;
            rights=0;
            xFinish = x;
            yFinish = y;
            shortestPathCalculation(map, queue, &foundShortestPath, &xFinish, &yFinish);
        } else if(rights>=3){
            printArray(map);
            foundFinish();
            lefts=0;
            rights=0;
            xFinish = x;
            yFinish = y;
            shortestPathCalculation(map, queue, &foundShortestPath, &xFinish, &yFinish);
        }
    } else {
        //printArray(map);
        if(beginning2){
            x = 0;
            y = 19;
            direction = 0;
        }
        beginning2 = false;

        switch(direction){
            case 0:
            if(map[y][x].forward != NULL && map[y][x].forward->shortest){
                moveForward();
                movement(&x, &y, &direction);
            } else if(map[y][x].left != NULL && map[y][x].left->shortest){
                turnLeft();
                directionLeft(&direction);
                moveForward();
                movement(&x, &y, &direction);
            } else if(map[y][x].right != NULL && map[y][x].right->shortest){
                turnRight();
                directionRight(&direction);
                moveForward();
                movement(&x, &y, &direction);
            }
                break;
            case 1:
                if(map[y][x].forward != NULL && map[y][x].forward->shortest){
                    turnLeft();
                    directionLeft(&direction);
                    moveForward();
                    movement(&x, &y, &direction);
                } else if(map[y][x].right != NULL && map[y][x].right->shortest){
                    moveForward();
                    movement(&x, &y, &direction);
                } else if(map[y][x].bottom != NULL && map[y][x].bottom->shortest){
                    turnRight();
                    directionRight(&direction);
                    turnRight();
                    directionRight(&direction);
                }
                break;
            case 2:
                if(map[y][x].bottom != NULL && map[y][x].bottom->shortest){
                    moveForward();
                    movement(&x, &y, &direction);
                } else if(map[y][x].right != NULL && map[y][x].right->shortest){
                    turnLeft();
                    directionLeft(&direction);
                    moveForward();
                    movement(&x, &y, &direction);
                } else if(map[y][x].left != NULL && map[y][x].left->shortest){
                    turnRight();
                    directionRight(&direction);
                    turnRight();
                    directionRight(&direction);
                }
                break;
            case 3:
                if(map[y][x].bottom != NULL && map[y][x].bottom->shortest){
                    turnLeft();
                    directionLeft(&direction);
                    moveForward();
                    movement(&x, &y, &direction);
                } else if(map[y][x].left != NULL && map[y][x].left->shortest){
                    moveForward();
                    movement(&x, &y, &direction);
                } else if(map[y][x].forward != NULL && map[y][x].forward->shortest){
                    turnRight();
                    directionRight(&direction);
                    turnRight();
                    directionRight(&direction);
                }
                break;
            }
        if(x == xFinish && y == yFinish){
            printUI("Shortest Path Complete.");
            foundFinish();
        }
        /*
        if(map[y][x].forward != NULL && map[y][x].forward->shortest){
            moveForward();
            movement(&x, &y, &direction);
        } else if(map[y][x].left != NULL && map[y][x].left->shortest){
            turnLeft();
            directionLeft(&direction);
            moveForward();
            movement(&x, &y, &direction);
        } else if(map[y][x].right != NULL && map[y][x].right->shortest){
            turnRight();
            directionRight(&direction);
            moveForward();
            movement(&x, &y, &direction);
        } else {
            turnRight();
            directionRight(&direction);
            turnRight();
            directionRight(&direction);
        }
        */
        /*
        if(map[y][x].left != NULL){
            if(shortPath.front()->x == map[y][x].left->x && shortPath.front()->y == map[y][x].left->y){
                turnLeft();
                moveForward();
                directionLeft(&direction);
                movement(&x, &y, &direction);
                isNull = true;
            }
        }
        else if(map[y][x].forward != NULL && !isNull){
            if(shortPath.front()->x == map[y][x].forward->x && shortPath.front()->y == map[y][x].forward->y){
                moveForward();
                movement(&x, &y, &direction);
                isNull = true;
            }
        } else if(map[y][x].right != NULL && !isNull){
            if(shortPath.front()->x == map[y][x].right->x && shortPath.front()->y == map[y][x].right->y){
                turnRight();
                moveForward();
                directionRight(&direction);
                movement(&x, &y, &direction);
                isNull = true;
            }
        } else {
            turnRight();
            turnRight();
            directionRight(&direction);
            directionRight(&direction);
            isNull = true;
        }

        isNull = false;

        //re-enact calculated shortest path
        */
    }

}
