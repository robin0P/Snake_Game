#include <iostream>
#include <conio.h>
#include <cstdlib> // for std::system 

using namespace std;

const int width = 20;
const int height = 10;
const int maxSnakeLength = 100;

int x, y;
int foodX, foodY;
int score = 0;
int snakeX[maxSnakeLength];
int snakeY[maxSnakeLength];
int snakeLength = 1;
char playerName;
bool gameOver = false;

void spawnFood(){
    foodX = rand() % width;
    foodY = rand() % height;
}

void draw(int x, int y, char playerName){
    system("cls");

    for(int i = 0; i < width + 2; i++){
        cout << "_";
    }

    cout << '\n';


    for(int i = 0; i < height; i++){
        cout << "|";
        for(int j = 0; j < width; j++){

            bool isSnake = false;
            for(int k = 0; k < snakeLength; k++){
                if(snakeX[k] == j && snakeY[k] == i){
                    if(k == 0) cout << playerName;
                    else cout << "o";
                    isSnake = true;
                    break;
                }
            }

            if(!isSnake){
                if(j == x && i == y){
                    cout << playerName;
                }else if(j == foodX && i == foodY){
                    cout << "+";
                }else{
                    cout << ".";
                }
            }

        }
        cout << "|" << '\n';
    }

    for(int i = 0; i < width + 2; i++){
        cout << "-";
    }
    cout << '\n';
    cout << "Score: " << score << '\n';
}

void move(){
    switch(_getch()){
        case 'w': if(y > 0) y--; else gameOver = true; break;
        case 'a': if(x > 0) x--; else gameOver = true; break;
        case 's': if(y < height - 1) y++; else gameOver = true; break;
        case 'd': if(x < width - 1) x++; else gameOver = true; break;
        case 'q': gameOver = true; return;
    }

    // move the body parts
    for(int i = snakeLength - 1; i > 0; i--){
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    // move the head to new place
    snakeX[0] = x;
    snakeY[0] = y;


    // if head collapse with any tail part, gameOver = true;
    for(int i = 1; i < snakeLength; i++){
        if(snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]){
            gameOver = true;
            return;
        }
    }

    // food control
    if(snakeX[0] == foodX && snakeY[0] == foodY){
        score++;
        snakeLength++;
        spawnFood();
    }
}

int main(){
    cout << "Enter (x, y) respectfully: "; cin >> x >> y;
    cout << "Enter your player name (a letter for now): "; cin >> playerName;

    snakeX[0] = x;
    snakeY[0] = y;

    spawnFood();
    while(!gameOver){    
        draw(x, y, playerName);
        move();
        if(gameOver){
            cout << "Game over!" << '\n';
            cout << "Your score is: " << score;
        }
    }

    return 0;
}