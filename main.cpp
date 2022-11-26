
#include <GL/glut.h>
#include <math.h>
#include <sstream>
#include <string.h>
#define pi 3.142857

int r,c,win1=0,win2=0,draw=0;
int pos[3][3];
int currplayer;
char* message = (char*) "Use WASD keys to move and Enter to Select.";
char* message1;
std::string temp;

bool iscomplete()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(pos[i][j] == 0)
				return 0;
		}
	}
	return 1;
}

int checkwinner()
{
	int ret;
	for(int i=0;i<3;i++)
	{
		//horizontal
		if(pos[i][0]==pos[i][1] && pos[i][1]==pos[i][2] && pos[i][2]!=0)
			return pos[i][0];
			
		//vertical
		else if(pos[0][i]==pos[1][i] && pos[1][i]==pos[2][i] && pos[2][i]!=0)
			return pos[0][i];
	}
	
	//diagonal
		if(pos[0][0]==pos[1][1] && pos[1][1]==pos[2][2] && pos[2][2]!=0)
			return pos[0][0];
			
		else if(pos[0][2]==pos[1][1] && pos[1][1]==pos[2][0] && pos[2][0]!=0)
			return pos[1][1];
	
	return 0;
}

void changeplayer()
{
	if(currplayer == 1)
	{
		currplayer = 2;
		message = (char*) "Player 2 turn.";
	}
	else
	{
		currplayer = 1;
		message = (char*) "Player 1 turn.";
	}
}


void gameinit()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			pos[i][j] = 0;
			currplayer = 1;
		}
	}
}

void game()
{
	if(pos[r][c]==0)
	{
		pos[r][c] = currplayer;
		changeplayer();
	}
	else
	message = (char*) "Can'not place here.";
	
	int winner = checkwinner();
	if(winner==1)
	{
		message = (char*) "Player 1 won.";
		win1++;
		gameinit();
		
	}
	else if(winner==2)
	{
		message = (char*) "Player 2 won.";
		win2++;
		gameinit();
	}
	else
	{
		if(iscomplete())
		{
			message = (char*) "Game Draw.";
			draw++;
			gameinit();
		}
	}
	
	
	
}

void drawBitmapText(char* text, float x, float y, float z) {
    char* c;

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f(x, y, z);

    for(c = text; *c != '\0'; c++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}
void msg(){
	temp = "Winnings : Player 1 = " + std::to_string(win1) + "  Player 2 = " + std::to_string(win2) + "  Draw = " + std::to_string(draw);
	message1 = (char*) temp.c_str();
	drawBitmapText(message1, -450.0f, 460.0f, -0.0f);
	drawBitmapText(message, -450.0f, -490.0f, -0.0f);
}


void circle(int xtrans,int ytrans,int radius=100)
{
	glBegin(GL_POINTS);
	float x, y, i;
	glColor3f(1.0f, 0.0f, 0.0f);
	
	for ( i = 0; i < (2 * pi); i += 0.001)
	{
		x = xtrans + (radius * cos(i));
		y = ytrans + (radius * sin(i));
		for(int j = 0;j<10;j++)
		{
			glVertex2i(x - j, y-j);
			glVertex2i(x + j, y+j);
		}
	}
	glEnd();
}

void cross(int x, int y)
{
	glColor3f(0.06f, 1.0f, 0.06f);
	glRotatef(45, 0.0, 0.0, 1.0);
	glRectf(x-10,y-130, x+10,y+130);
	glRectf(x-130,y-10, x+130,y+10);
	glRotatef(-45, 0.0, 0.0, 1.0);
	
}

void crosscircle()
{
	int x,y,xc,yc;
	//draw circles
	
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(pos[i][j]==1)
			{
				if(i==0)
				{
					y=300;
				}
				else if(i==1)
				{
					y=0;
				}
				else
				{
					y=-300;
				}
				
				if(j==0)
				{
					x=-300;
				}
				else if(j==1)
				{
					x=0;
				}
				else
				{
					x=300;
				}
				circle(x,y);
			}
			if(pos[i][j]==2)
			{
				if(i==0)
				{
					if(j==0)
						cross(0,424);
					else if(j==1)
						cross(212,212);
					else
						cross(424,0);
				}
				else if(i==1)
				{
					if(j==0)
						cross(-212,212);
					else if(j==1)
						cross(0,0);
					else
						cross(212,-212);
				}
				else
				{
					if(j==0)
						cross(-424,0);
					else if(j==1)
						cross(-212,-212);
					else
						cross(0,-424);
				}
				
					
				
			}
		}
	}
	glColor3f(0.0f, 1.0f, 0.0f);
	//cross(212,-212);
}

void highlight(int i,int j)
{
	int x1,x2,y1,y2;
	
	switch(i)
	{
		case 0:
			y1 =450;
			y2 =155;
			break;
		case 1:
			y1 =145;
			y2 =-145;
			break;
		case 2:
			y1 =-155;
			y2 =-450;
			break;
	}
	
	switch(j)
	{
		case 0:
			x1=-450;
			x2=-155;
			break;
		case 1:
			x1=-145;
			x2=145;
			break;
		case 2:
			x1=155;
			x2=450;
			break;
	}
	
	glColor3f(5.0f,5.0f,0.0f); 
	glRectf(x1,y1, x2, y2);
	
}


void myInit (void)
{
	// making background color black as first
	// 3 arguments all are 0.0
	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	// making picture color green (in RGB mode), as middle argument is 1.0
	glColor3f(0.0, 1.0, 0.0);
	
	// breadth of picture boundary is 1 pixel
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// setting window dimension in X- and Y- direction
	gluOrtho2D(-500, 500, -500, 500);
}


void display (void)
{
	float x, y, i;
	glClear(GL_COLOR_BUFFER_BIT);
	//draw square
	glColor3f(0.9, 0.9, 0.9);
	glRectf(-450.0f,450.0f, 450.0f, -450.0f);
	
	glColor3f(0.0f,0.0f,0.0f); 
	
//mesh
	glRectf(-155.0f,450.0f, -145.0f, -450.0f);
	glRectf(155.0f,450.0f, 145.0f, -450.0f);
	glRectf(-450.0f,155.0f, 450.0f, 145.0f);
	glRectf(-450.0f,-155.0f, 450.0f, -145.0f);
	
	
	highlight(r,c);
	crosscircle();
	
	msg();
	
	glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
	message = (char*) "";
	if(key == 's')
	{
		r = (r+1)%3;
	}
	
	if(key == 'd')
	{
		c = (c+1)%3;
	}
	if(key == 'w')
	{
		r = (r+2)%3;
	}
	
	if(key == 'a')
	{
		c = (c+2)%3;
	}
	//enter
	if(key == 13)
	{
		game();
		
	}
	
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	gameinit();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("TIC TAC TOE");
    
	myInit();
	
	
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMainLoop();
	
	return 0;
}


