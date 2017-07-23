#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/freeglut.h>
#include <math.h>
#define maxx 4
#define maxy 4
#define dx 100
#define dy 100

using namespace std;

struct Move
{
    int row, col;
};

void display();
bool isMovesLeft(char board[3][3]);
int evaluate(char b[3][3]);
Move findBestMove(char board[3][3]);

GLfloat x[maxx]={0.0};
GLfloat x0=100,y0=100;
GLint i,j;
char player = 'x', opponent = 'o';
char WinState='X';
int WinStateCol=999,WinStateRow=999;
char board[3][3] =
{
    { '_', '_', '_' },
    { '_', '_', '_' },
    { '_', '_', '_' }
};

void ShowStatus(){
    glLineWidth(30);
    glColor3ub(0x54,0x54,0x54);
    if(WinState == '\\' )
    {
        glBegin(GL_LINES);
            glVertex2f(x[3],x[0]);
            glVertex2f(x[0],x[3]);
        glEnd();
        cout<<WinState<<endl;
    }
    else if(WinState=='/'){
        glBegin(GL_LINES);
            glVertex2f(x[0],x[0]);
            glVertex2f(x[3],x[3]);
        glEnd();
        cout<<WinState<<endl;
    }
    else if(WinState=='-'){
        glBegin(GL_LINES);
            glVertex2f(x[0],x[WinStateRow]+50);
            glVertex2f(x[3],x[WinStateRow]+50);
        glEnd();
        cout<<WinState<<endl;
    }
    else if(WinState=='|'){
        glBegin(GL_LINES);
            glVertex2f(x[WinStateCol]+50,x[0]);
            glVertex2f(x[WinStateCol]+50,x[3]);
        glEnd();
        cout<<WinState<<endl;
    }
}

void gamePlay()
{
    if(isMovesLeft(board) && evaluate(board)==0){
        Move bestMove = findBestMove(board);
        cout<<"The Optimal Move is :n \n";
        cout<<"ROW: "<<bestMove.row<<endl<<"COL: "<<bestMove.col<<endl;
        board[bestMove.row][bestMove.col]=player;
        if(evaluate(board)>0){
            cout<<"player wins!\n";
        }
    }
    else{
        if(evaluate(board)<0){
            cout<<"opponent wins!\n";
        }
        else if(evaluate(board)>0){
            cout<<"player wins!\n";
        }
        else if(evaluate(board)==0){
            cout<<"draw!\n";
        }
    }
}

void myinit()
{
	glLineWidth(30);
	glClearColor(0.078125,0.73828125,0.671875,1.0);
	glColor3f(1.0,0.0,0.0);
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,499.0,0.0,499.0);
	glutPostRedisplay();
}

bool mouseBtnTest(int btn,int state){
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN && evaluate(board)==0)
        return true;
    return false;
}

void mouse(int btn,int state,int ox,int oy)
{
    int xc=ox,yc=500-oy;
    if(mouseBtnTest(btn,state) && xc > x[0] && xc < x[1] && yc > x[0] && yc < x[1] && board[0][0]=='_' ){
        board[0][0]=opponent;gamePlay();
    }
    else if(mouseBtnTest(btn,state) && xc > x[1] && xc < x[2] && yc > x[0] && yc < x[1] && board[0][1]=='_' ){
        board[0][1]=opponent;gamePlay();
    }
    else if(mouseBtnTest(btn,state) && xc > x[2] && xc < x[3] && yc > x[0] && yc < x[1] && board[0][2]=='_' ){
        board[0][2]=opponent;gamePlay();
    }
    else if(mouseBtnTest(btn,state) && xc > x[0] && xc < x[1] && yc > x[1] && yc < x[2] && board[1][0]=='_' ){
        board[1][0]=opponent;gamePlay();
    }
    else if(mouseBtnTest(btn,state) && xc > x[1] && xc < x[2] && yc > x[1] && yc < x[2] && board[1][1]=='_' ){
        board[1][1]=opponent;gamePlay();
    }
    else if(mouseBtnTest(btn,state) && xc > x[2] && xc < x[3] && yc > x[1] && yc < x[2] && board[1][2]=='_' ){
        board[1][2]=opponent;gamePlay();
    }
    else if(mouseBtnTest(btn,state) && xc > x[0] && xc < x[1] && yc > x[2] && yc < x[3] && board[2][0]=='_' ){
        board[2][0]=opponent;gamePlay();
    }
    else if(mouseBtnTest(btn,state) && xc > x[1] && xc < x[2] && yc > x[2] && yc < x[3] && board[2][1]=='_' ){
        board[2][1]=opponent;gamePlay();
    }
    else if(mouseBtnTest(btn,state) && xc > x[2] && xc < x[3] && yc > x[2] && yc < x[3] && board[2][2]=='_' ){
        board[2][2]=opponent;gamePlay();
    }
    glutPostRedisplay();
}

void drawX(int i,int j){
    glLineWidth(7);
    glColor3ub(0x54,0x54,0x54);
    glBegin(GL_LINES);
        glVertex2f(x[j]+25,x[i]+25);
        glVertex2f(x[j+1]-25,x[i+1]-25);

        glVertex2f(x[j+1]-25,x[i]+25);
        glVertex2f(x[j]+25,x[i+1]-25);
    glEnd();
}

void drawO(int i,int j){
    float xc=x[j]+dx/2,yc=x[i]+dx/2,r=dx/4,theta=0;
    glLineWidth(3);
    glColor3ub(0xf2,0xeb,0xd3);
    glBegin(GL_LINE_LOOP);
        for(int k=0;k<360;k++,theta+=(1*(3.14/180))){
            glVertex2f(xc+r*cos(theta),yc+r*sin(theta));
        }
    glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(30);
	glColor3f(0.0,0.0,1.0);
	for(i=0;i<maxx;i++)
		x[i]=x0+i*dx;
	glColor3ub(0x0d,0xa1,0x92);
    glBegin(GL_LINES);
        glVertex2f(x[0],x[2]);
        glVertex2f(x[3],x[2]);

        glVertex2f(x[0],x[1]);
        glVertex2f(x[3],x[1]);

        glVertex2f(x[1],x[0]);
        glVertex2f(x[1],x[3]);

        glVertex2f(x[2],x[0]);
        glVertex2f(x[2],x[3]);
    glEnd();
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]==opponent){
                drawO(i,j);
            }
            else if(board[i][j]==player){
                drawX(i,j);
            }
        }
    }
    if(evaluate(board)>0){
        ShowStatus();
    }
    glFlush();
}

bool isMovesLeft(char board[3][3])
{
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            if (board[i][j]=='_')
                return true;
    return false;
}

int evaluate(char b[3][3])
{
    // Checking Rows for X or O victory
    for (int row = 0; row<3; row++)
    {
        if (b[row][0]==b[row][1] &&
            b[row][1]==b[row][2])
        {
            if (b[row][0]==player){
                WinState='-';
                WinStateRow=row;
                return +10;
            }
            else if (b[row][0]==opponent)
                return -10;
        }
    }

    // Checking Columns for X or O victory
    for (int col = 0; col<3; col++)
    {
        if (b[0][col]==b[1][col] &&
            b[1][col]==b[2][col])
        {
            if (b[0][col]==player){
                WinState='|';
                WinStateCol=col;
                return +10;
            }
            else if (b[0][col]==opponent)
                return -10;
        }
    }

    // Checking Diagonals for X or O victory
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2])
    {
        if (b[0][0]==player){
            WinState='/';
            return +10;
        }
        else if (b[0][0]==opponent)
            return -10;
    }

    if (b[0][2]==b[1][1] && b[1][1]==b[2][0])
    {
        if (b[0][2]==player){
            WinState='\\';
            return +10;
        }
        else if (b[0][2]==opponent)
            return -10;
    }

    // Else if none of them have won then return 0
    return 0;
}

// This is the minimax function.
//It considers all the possible ways the game can go and returns value of the board
int minimax(char board[3][3], int depth, bool isMax)
{
    int score = evaluate(board);

    // If Maximizer won the game return his/her evaluated score
    if (score == 10)
        return score-depth;

    // If Minimizer has won game return his/her evaluated score
    if (score == -10)
        return score+depth;

    // If there are no more moves and no winner then it is a tie
    if (isMovesLeft(board)==false)
        return 0;

    // If maximizer's move
    if (isMax)
    {
        int best = -1000;
        // Traverse all cells
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if cell is empty
                if (board[i][j]=='_')
                {
                    // Make the move
                    board[i][j] = player;
                    // Call minimax recursively and choose the maximum value
                    best = max( best,minimax(board, depth+1, !isMax) );
                    // Undo the move
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }

    // If minimizer's move
    else
    {
        int best = 1000;
        // Traverse all cells
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if cell is empty
                if (board[i][j]=='_')
                {
                    // Make the move
                    board[i][j] = opponent;
                    // Call minimax recursively and choose the minimum value
                    best = min(best,minimax(board, depth+1, !isMax));
                    // Undo the move
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}

// Returns the best possible move for the player
Move findBestMove(char board[3][3])
{
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    // Traverse all cells, evalutae minimax function for all empty cells. And return the cell with optimal value
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            // Check if celll is empty
            if (board[i][j]=='_')
            {
                // Make the move
                board[i][j] = player;
                // compute evaluation function for this move
                int moveVal = minimax(board, 0, false);
                // Undo the move
                board[i][j] = '_';
                //update the best
                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    cout<<"The value of the best Move is :"<<bestVal<<endl;
    return bestMove;
}

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("TicTacToe");

	myinit();
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	glutMainLoop();
}
