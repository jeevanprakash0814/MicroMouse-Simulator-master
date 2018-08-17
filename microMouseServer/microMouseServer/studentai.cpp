#include "string"
#include "micromouseserver.h"
#include <iostream>
#include <list>
using namespace std;

/*
 * Name: Jeevan Prakash
 * Version: 20180817
 *
*/

struct square{//A square class that is used to represent every square in the maze
public:
    int x = 0;//x coordinate of the square
    int y = 0;//y coordinate of the square
    int visits = 0;//How many times the square has been visited
    bool visited = false;//Whether it has been visited
    bool shortest = false;//Whether it is part of the shortest path

    square *previousNode;//reference to the previous square before it in the shortest path
    square *forward;//reference to the square above it
    square *right;//reference to the square right of it
    square *left;//reference to the square left of it
    square *bottom;//reference to the square below it
};

void printShortestPath(square (&map)[MAZE_HEIGHT][MAZE_WIDTH]){//simply prints out the shortest path
    for(int i=0; i<MAZE_HEIGHT; i++){
        for(int j=0; j<MAZE_HEIGHT; j++){
            if(i==19 && j==0){
                cout <<"1"<<"  ";
            } else if(map[i][j].shortest){
                cout <<"1"<<"  ";
            } else {
                cout <<"0"<<"  ";
            }
        }
        cout <<endl;
    }
}

void shortestPathCalculation(square (&map)[MAZE_HEIGHT][MAZE_WIDTH], list<square*> queue, bool *foundShortestpath, int *xFinish, int *yFinish){//calculates the shortest path given the information collected from the first run of the islanded maze algorithm
    queue.push_back(&map[MAZE_HEIGHT-1][0]);//Start the queue with the beginning position
    square* s = queue.front();//s is a variable that is used in the while loop to figure out the shortest path
    while(!queue.empty() && (s->x != *xFinish || s->y != *yFinish)){//Keep searching for the best path until you reach the end or the queue emptiesm
        s = queue.front();//Adding adjacent squares to the queue if it has not been visited or it is not null
            if(s->forward != NULL && !s->forward->visited){
                s->forward->visited = true;
                s->forward->previousNode = s;
                queue.push_back(s->forward);
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
        //Using a list data structure, references to adjacent squares starting from the start are added to the queue
        //It keeps repeating the process with the additional part of removing the front square reference in the queue
        //While moving one square at a time till it hits the end the references to the shortest path is held in the previousNode references of s the square variable
        //The next while loop takes s and retraces through all the previousNode square references found in it while setting the values of the shortest bool attribute in all of them to true
        //This allows for the mouse to trace the shortest path when it is run the second time
    }

    square* currentNode = s;
    int x = currentNode->x;
    int y = currentNode->y;

    while((x != 0) || (y != 19)){//Keep retrieving the path until you have reached the beginning
        currentNode->shortest = true;
        if(currentNode->previousNode != NULL){//ensures that the previous node is not null
            currentNode = currentNode->previousNode;//sets the currentNode square to the previous node
        }
        x = currentNode->x;//sets the x that is being used to check if the while loop should continue
        y = currentNode->y;//sets the y that is being used to check if the while loop should continue
    }

    *foundShortestpath = true;
    cout <<endl;
    printShortestPath(map);
}

void populateArray(square (&map)[MAZE_HEIGHT][MAZE_WIDTH]){//Populates the array's squares with x and y values
    for(int i=0; i<MAZE_HEIGHT; i++){
        for(int j=0; j<MAZE_HEIGHT; j++){
            map[i][j].x = j;
            map[i][j].y = i;
        }
    }
}

void printArray(square (&map)[MAZE_HEIGHT][MAZE_WIDTH]){//Printing out the main 2d array
    for(int i=0; i<MAZE_HEIGHT; i++){
        for(int j=0; j<MAZE_HEIGHT; j++){
            cout <<map[i][j].visits<<"  ";
        }
        cout <<endl;
    }
}

void directionLeft(int *direction){//Function is called when a left turn is made
    *direction=(*direction+3)%4;
}

void directionRight(int *direction){//Function is called when a right turn is made
    *direction=(*direction+1)%4;
}

void movement(int *x, int *y, int *direction){//Function is called when the mouse moves
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

void microMouseServer::studentAI(){
    static int x = 0;//The x value of the mouse (Starting value is 0)
    static int y = MAZE_HEIGHT-1;//The y value of the mouse (Starting value is the maze height - 1)
    static int lefts = 0;//Used for identifying the end
    static int rights = 0;//Used for identifying the end

    static int xFinish = 0;//At the end of running the program the first time these two
    static int yFinish = 0;//variables represent the end coordinates at the destination

    static bool beginning = true;//Bool used to run a small of code once in the program
    static bool beginning2 = true;//Bool used to run a small of code once in the program
    static bool foundShortestPath = false;
    static bool isNull = false; //I use this variable if I need to break from the
    //if-else chain that it is being used in

    static int direction = 0;//The relational orientation of the mouse in the maze

    static list<square*> queue;//A queue used to find the shortest path
    static square map[MAZE_HEIGHT][MAZE_WIDTH];//A 2d array used to store info on the maze

    if(beginning){//Setting up for the program to start solving the maze
        populateArray(map);
        map[MAZE_HEIGHT-1][0].visits = 1;
        beginning = false;
    }    

    int timesLeft = 0;//Used to choose an action to take when solving the islanded maze
    int timesForward = 0;//Used to choose an action to take when solving the islanded maze
    int timesRight = 0;//Used to choose an action to take when solving the islanded maze

    if(!foundShortestPath){//This block of code is run the first time the code is ran
        switch(direction){//Switch statement that is setting references variables based on the current orientation of the mouse
            case 0:
            if(isWallLeft()){
                timesLeft = INT_MAX;//If there is a wall left we do not want the mouse turning left so we set timesLeft to the max
            } else {
                timesLeft = map[y][x - 1].visits;//Understanding how many times the mouse has been to the square on the left of it
                map[y][x].left = &map[y][x - 1];//Setting the references found in every square to be used when solving for the shortest path
                map[y][x-1].right = &map[y][x];//Just creating another link back to the current square so that it isn't lost
            }
            if(isWallForward()){
                timesForward = INT_MAX;//If there is a wall ahead we do not want the mouse moving forward so we set timesForward to the max
            } else {
                timesForward = map[y - 1][x].visits;//Understanding how many times the mouse has been to the square ahead of it
                map[y][x].forward = &map[y - 1][x];//Setting the references found in every square to be used when solving for the shortest path
                map[y - 1][x].bottom = &map[y][x];//Just creating another link back to the current square so that it isn't lost
            }
            if(isWallRight()){
                timesRight = INT_MAX;//If there is a wall right we do not want the mouse turning right so we set timesRight to the max
            } else {
                timesRight = map[y][x + 1].visits;//Understanding how many times the mouse has been to the square on the right of it
                map[y][x].right = &map[y][x + 1];//Setting the references found in every square to be used when solving for the shortest path
                map[y][x + 1].left = &map[y][x];//Just creating another link back to the current square so that it isn't lost
            }
            if(!(y+1>19)){
                map[y][x].bottom = &map[y + 1][x];//If the square behind is not outside the actual maze it adds the reference
            }
            break;
            case 1:
            if(isWallLeft()){
                timesLeft = INT_MAX;//If there is a wall left we do not want the mouse turning left so we set timesLeft to the max
            } else {
                timesLeft = map[y - 1][x].visits;//Understanding how many times the mouse has been to the square on the left of it
                map[y][x].forward = &map[y - 1][x];//Setting the references found in every square to be used when solving for the shortest path
                map[y - 1][x].bottom = &map[y][x];//Just creating another link back to the current square so that it isn't lost
            }
            if(isWallForward()){
                timesForward = INT_MAX;//If there is a wall ahead we do not want the mouse moving forward so we set timesForward to the max
            } else {
                timesForward = map[y][x + 1].visits;//Understanding how many times the mouse has been to the square ahead of it
                map[y][x].right = &map[y][x + 1];//Setting the references found in every square to be used when solving for the shortest path
                map[y][x + 1].left = &map[y][x];//Just creating another link back to the current square so that it isn't lost
            }
            if(isWallRight()){
                timesRight = INT_MAX;//If there is a wall right we do not want the mouse turning right so we set timesRight to the max
            } else {
                timesRight = map[y + 1][x].visits;//Understanding how many times the mouse has been to the square on the left of it
                map[y][x].bottom = &map[y + 1][x];//Setting the references found in every square to be used when solving for the shortest path
                map[y + 1][x].forward = &map[y][x];//Just creating another link back to the current square so that it isn't lost
            }
            if(!(x-1<0)){
                map[y][x].left = &map[y][x - 1];//If the square behind is not outside the actual maze it adds the reference
            }
            break;
            case 2:
            if(isWallLeft()){
                timesLeft = INT_MAX;//If there is a wall left we do not want the mouse turning left so we set timesLeft to the max
            } else {
                timesLeft = map[y][x + 1].visits;//Understanding how many times the mouse has been to the square on the left of it based on its direction
                map[y][x].right = &map[y][x + 1];//Setting the references found in every square to be used when solving for the shortest path
                map[y][x + 1].left = &map[y][x];//Just creating another link back to the current square so that it isn't lost
            }
            if(isWallForward()){
                timesForward = INT_MAX;//If there is a wall ahead we do not want the mouse moving forward so we set timesForward to the max
            } else {
                timesForward = map[y + 1][x].visits;//Understanding how many times the mouse has been to the square ahead of it
                map[y][x].bottom = &map[y + 1][x];//Setting the references found in every square to be used when solving for the shortest path
                map[y + 1][x].forward = &map[y][x];//Just creating another link back to the current square so that it isn't lost
            }
            if(isWallRight()){
                timesRight = INT_MAX;//If there is a wall right we do not want the mouse turning right so we set timesRight to the max
            } else {
                timesRight = map[y][x - 1].visits;//Understanding how many times the mouse has been to the square on the left of it
                map[y][x].left = &map[y][x - 1];//Setting the references found in every square to be used when solving for the shortest path
                map[y][x - 1].right = &map[y][x];//Just creating another link back to the current square so that it isn't lost
            }
            if(!(y-1<0)){
                map[y][x].forward = &map[y - 1][x];//If the square behind is not outside the actual maze it adds the reference
            }
            break;
            case 3:
            if(isWallLeft()){
                timesLeft = INT_MAX;//If there is a wall left we do not want the mouse turning left so we set timesLeft to the max
            } else {
                timesLeft = map[y + 1][x].visits;//Understanding how many times the mouse has been to the square on the left of it based on its direction
                map[y][x].bottom = &map[y + 1][x];//Setting the references found in every square to be used when solving for the shortest path
                map[y + 1][x].forward = &map[y][x];//Just creating another link back to the current square so that it isn't lost
            }
            if(isWallForward()){
                timesForward = INT_MAX;//If there is a wall ahead we do not want the mouse moving forward so we set timesForward to the max
            } else {
                timesForward = map[y][x - 1].visits;//Understanding how many times the mouse has been to the square ahead of it
                map[y][x].left = &map[y][x - 1];//Setting the references found in every square to be used when solving for the shortest path
                map[y][x - 1].right = &map[y][x];//Just creating another link back to the current square so that it isn't lost
            }
            if(isWallRight()){
                timesRight = INT_MAX;//If there is a wall right we do not want the mouse turning right so we set timesRight to the max
            } else {
                timesRight = map[y - 1][x].visits;//Understanding how many times the mouse has been to the square on the left of it
                map[y][x].forward = &map[y - 1][x];//Setting the references found in every square to be used when solving for the shortest path
                map[y - 1][x].bottom = &map[y][x];//Just creating another link back to the current square so that it isn't lost
            }
            if(!(x+1>19)){
                map[y][x].right = &map[y][x + 1];//If the square behind is not outside the actual maze it adds the reference
            }
            break;
        }
        //If there is no wall left turn left and move forward, unless you have been more to the left square than the forward or right squares
        if(!isWallLeft() && !(((timesLeft >= timesForward) && !isWallForward()) || ((timesLeft >= timesRight) && !isWallRight()))){
            turnLeft();
            directionLeft(&direction);
            lefts++;
            rights=0;
            moveForward();
            movement(&x, &y, &direction);
        } else if(!isWallForward() && !((timesLeft >= timesRight) && !isWallRight())){//If there is no wall forwared move forward, unless you have been more to the right square than the left squares
            moveForward();
            lefts = 0;
            rights = 0;
            movement(&x, &y, &direction);
        } else if(!isWallRight()){//If there is no wall right then turn right and move forward
            turnRight();
            directionRight(&direction);
            rights++;
            lefts=0;
            moveForward();
            movement(&x, &y, &direction);
        } else {//If all the above conditionals fail turn around and move forward
            rights = 0;
            lefts = 0;
            turnRight();
            turnRight();
            directionRight(&direction);
            directionRight(&direction);
            moveForward();
            movement(&x, &y, &direction);
        }

        map[y][x].visits += 1;

        //The following block of code determines if the mouse has reached the end based on the fact that in the 2x2 end you would take a sequence of forward and left/right turns
        if(lefts>=3){//It utilized the number of times you have turned left to determine this in this case
            printArray(map);
            foundFinish();
            xFinish = x;//providing the finish x for the next run
            yFinish = y;//providing the finish y for the next run
            shortestPathCalculation(map, queue, &foundShortestPath, &xFinish, &yFinish);
        } else if(rights>=3){//It utilized the number of times you have turned right to determine this in this case
            printArray(map);
            foundFinish();
            xFinish = x;//providing the finish x for the next run
            yFinish = y;//providing the finish y for the next run
            shortestPathCalculation(map, queue, &foundShortestPath, &xFinish, &yFinish);
        }
    } else {//This block of code is run the second time the code is ran
        if(beginning2){//Setting up to run the shortest path
            x = 0;
            y = 19;
            direction = 0;
            beginning2 = false;
        }

        switch(direction){//Switch statement that is moving the mouse based on data gained from the previous run and on the current direction
            case 0:
            if(map[y][x].forward != NULL && map[y][x].forward->shortest){//Checks the reference to forward is not null and that the forward square is part of the shortest path
                moveForward();
                movement(&x, &y, &direction);
            } else if(map[y][x].left != NULL && map[y][x].left->shortest){//Checks the reference to left is not null and that the left square is part of the shortest path
                turnLeft();
                directionLeft(&direction);
                moveForward();
                movement(&x, &y, &direction);
            } else if(map[y][x].right != NULL && map[y][x].right->shortest){//Checks the reference to right is not null and that the right square is part of the shortest path
                turnRight();
                directionRight(&direction);
                moveForward();
                movement(&x, &y, &direction);
            }
                break;
            case 1:
                if(map[y][x].forward != NULL && map[y][x].forward->shortest){//Checks the reference to forward is not null and that the forward square is part of the shortest path
                    turnLeft();
                    directionLeft(&direction);
                    moveForward();
                    movement(&x, &y, &direction);
                } else if(map[y][x].right != NULL && map[y][x].right->shortest){//Checks the reference to right is not null and that the right square is part of the shortest path
                    moveForward();
                    movement(&x, &y, &direction);
                } else if(map[y][x].bottom != NULL && map[y][x].bottom->shortest){//Checks the reference to bottom is not null and that the bottom square is part of the shortest path
                    turnRight();
                    directionRight(&direction);
                    moveForward();
                    movement(&x, &y, &direction);
                }
                break;
            case 2:
                if(map[y][x].bottom != NULL && map[y][x].bottom->shortest){//Checks the reference to bottom is not null and that the bottom square is part of the shortest path
                    moveForward();
                    movement(&x, &y, &direction);
                } else if(map[y][x].right != NULL && map[y][x].right->shortest){//Checks the reference to right is not null and that the right square is part of the shortest path
                    turnLeft();
                    directionLeft(&direction);
                    moveForward();
                    movement(&x, &y, &direction);
                } else if(map[y][x].left != NULL && map[y][x].left->shortest){//Checks the reference to left is not null and that the left square is part of the shortest path
                    turnRight();
                    directionRight(&direction);
                    moveForward();
                    movement(&x, &y, &direction);
                }
                break;
            case 3:
                if(map[y][x].bottom != NULL && map[y][x].bottom->shortest){//Checks the reference to bottom is not null and that the bottom square is part of the shortest path
                    turnLeft();
                    directionLeft(&direction);
                    moveForward();
                    movement(&x, &y, &direction);
                } else if(map[y][x].left != NULL && map[y][x].left->shortest){//Checks the reference to left is not null and that the left square is part of the shortest path
                    moveForward();
                    movement(&x, &y, &direction);
                } else if(map[y][x].forward != NULL && map[y][x].forward->shortest){//Checks the reference to forward is not null and that the forward square is part of the shortest path
                    turnRight();
                    directionRight(&direction);
                    moveForward();
                    movement(&x, &y, &direction);
                }
                break;
            }
        if(x == xFinish && y == yFinish){//Checking if the current mouse position is equal to the final position acquired in the previous time the code was ran
            printUI("Shortest Path Complete.");
            foundFinish();
        }
    }

}
