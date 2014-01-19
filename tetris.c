#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>

struct piece{
  int x;
  int y;
  int onoff;
  int colour;
} ;
struct piece currActivePiece[16];
struct piece currDecidePiece[16];
struct piece currTempPiece[16];
struct piece nextActivePiece[16];

struct boardCell{
	int x;
	int y;
	int colour;
	int onoff;
};

/** This removes the console window **/
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

struct boardCell theBoard[20][40];
int gameMode=1;
int gameInProgress=0;
int anchorX,anchorY=1;
int mouseX,mouseY=1;
int stretchX,stretchY=1;
int pausedMode=1;
int currScore=0;
int afterDrop, beforeDrop;
int pieceColour;
char pieceColourStr[10];
int blue,green,red,yellow,darkgrey,white,black,orange,purple,rainbow,decidePiece;
int rainbowBlock;
int border1;
int border2;
int totNumOther;
int totNumOther;
int totNum1,totNum2,totNum3,totNum4;
int paused = 0;
float angle;
int moveX, moveY;
int needNewPiece=1;
#define STARTX 7
#define STARTY 33
#define xOffSet -1
int isGameMode=0;
int isTrailsMode=1;
int OKnewPiece=1;
int startCnt;
int ticks=0,fps;
float z_zoom = -10;
float gRotate = -10;
int newPieceNo,currPieceNo;
int pieceAngle=0;
int isBlendMode=1;
int isLineMode=0;
int isFogMode=0;
int arbColourR,arbColourG,arbColourB;
int totNumRowsDone;
int noL=0,noS=0,noZ=0,noO=0,noT=0,noEL=0,noLE=0;
int vIdleCnt,vRenderCnt;

GLfloat LightAmbient[]= { 0.4, 0.4, 0.4, 1.0 }; 
GLfloat LightDiffuse[]= { 0.7, 0.7, 0.7, 1.0 }; 
GLfloat LightPosition[]= { 0.0, 0.0, 2.0, 1.0 }; 

int shape_L[] = {0,1,0,0,
                 0,1,0,0,
	             0,1,0,0,
				 0,1,0,0,
				  0,0,0,0,
                  1,1,1,1,
	              0,0,0,0,
				  0,0,0,0,
                   0,1,0,0,
                   0,1,0,0,
	               0,1,0,0,
				   0,1,0,0,
                     0,0,0,0,
                     1,1,1,1,
	                 0,0,0,0,
				     0,0,0,0};

int shape_S[] = {0,1,1,0,
                 1,1,0,0,
	             0,0,0,0,
	             0,0,0,0,
				  0,1,0,0,
                  0,1,1,0,
	              0,0,1,0,
	              0,0,0,0,
                   0,1,1,0,
                   1,1,0,0,
	               0,0,0,0,
	               0,0,0,0,
                    0,1,0,0,
                    0,1,1,0,
	                0,0,1,0,
	                0,0,0,0};



int shape_Z[] = {1,1,0,0,
                 0,1,1,0,
	             0,0,0,0,
	             0,0,0,0,
				  0,1,0,0,
                  1,1,0,0,
	              1,0,0,0,
	              0,0,0,0,
                   1,1,0,0,
                   0,1,1,0,
	               0,0,0,0,
	               0,0,0,0,
				     0,1,0,0,
                     1,1,0,0,
	                 1,0,0,0,
	                 0,0,0,0};




int shape_O[] = {0,1,1,0,
                 0,1,1,0,
	             0,0,0,0,
	             0,0,0,0,
				  0,1,1,0,
                  0,1,1,0,
	              0,0,0,0,
	              0,0,0,0,
                   0,1,1,0,
                   0,1,1,0,
	               0,0,0,0,
	               0,0,0,0,
                    0,1,1,0,
                    0,1,1,0,
	                0,0,0,0,
	                0,0,0,0};

int shape_T[] = {0,0,1,0,
                 0,1,1,0,
	             0,0,1,0,
	             0,0,0,0,
                  0,0,1,0,
                  0,1,1,1,
                  0,0,0,0,
                  0,0,0,0,
                   0,0,1,0,
                   0,0,1,1,
	               0,0,1,0,
	               0,0,0,0,
                    0,0,0,0,
                    0,1,1,1,
                    0,0,1,0,
                    0,0,0,0};

int shape_EL[] = {0,0,0,1,
                  0,1,1,1,
	              0,0,0,0,
	              0,0,0,0,
                   0,0,1,0,
                   0,0,1,0,
	               0,0,1,1,
	               0,0,0,0,
                    0,1,1,1,
                    0,1,0,0,
	                0,0,0,0,
	                0,0,0,0,
                     0,1,1,0,
                     0,0,1,0,
	                 0,0,1,0,
	                 0,0,0,0};

/**int shape_LE[] = {0,1,1,1,
                  0,1,0,1,
	              0,1,0,1,
	              0,0,0,0,
				   0,1,1,1,
                   0,0,0,1,
	               0,1,1,1,
				   0,0,0,0,
                    0,1,0,1,
                    0,1,0,1,
	                0,1,1,1,
	                0,0,0,0,
				     0,1,1,1,
                     0,1,0,0,
	                 0,1,1,1,
				     0,0,0,0};**/
int shape_LE[] = {0,1,1,1,
                  0,0,0,1,
	              0,0,0,0,
	              0,0,0,0,
				   0,0,0,1,
                   0,0,0,1,
	               0,0,1,1,
				   0,0,0,0,
                    0,1,0,0,
                    0,1,1,1,
	                0,0,0,0,
	                0,0,0,0,
				     0,0,1,1,
                     0,0,1,0,
	                 0,0,1,0,
				     0,0,0,0};

void drawActivePiece(int xCnt,int yCnt,int makeActive)
{
  int i,j;
  int sx,sy;
  int bet1=0;int bet2=0;int bet3=0;

  glPushMatrix();

  j=0;
  for (i=0;i<16;i++)
  {
       if ((i>=0) && (i<=3)) 
	   {
         sx = xCnt + j;
		 sy = yCnt;
	   }
	   if ((i>=4) && (i<=7))
	   {
		   if (bet1 == 0)
		   { 
			 j = 0;
			 bet1 = 1;
		   }
		 sx = xCnt + j;
		 sy = yCnt - 1;
	   }
       if ((i>=8) && (i<=11))
	   {
         if (bet2 == 0) 
		 {
			 j = 0;
		     bet2 = 1;
		   }
		 sx = xCnt + j;
		 sy = yCnt - 2;
	   }
	   if ((i>=12) && (i<=15))
	   {
		   if (bet3 == 0)
		   {
			 j = 0;
			 bet3 = 1;
		   }
		 sx = xCnt + j;
		 sy = yCnt - 3;
	   }
       
	   if (makeActive == 1) 
	   {
	     if (currActivePiece[i].onoff == 1) 
	     {
	       glLoadIdentity();
	       glTranslatef(sx+xOffSet,sy,0);
		   glCallList(currActivePiece[i].colour);
	     }
	   }

	   if (makeActive == 2) 
	   {
	     if (nextActivePiece[i].onoff == 1) 
	     {
	       glLoadIdentity();
	       glTranslatef(sx+xOffSet,sy,0);
		   glCallList(nextActivePiece[i].colour);  
	     }
	   }
	   
	   if (makeActive == 3)
	   {
		   if (nextActivePiece[i].onoff == 1)
		   { 
            glPushMatrix();
			glLoadIdentity();
			glTranslatef(sx+xOffSet,sy,-10);
			glRotatef(angle,1.0,1.0,1.0);
		    glutSolidCube(1);
			glPopMatrix();
		   }
	   }

	   if (makeActive == 4)
	   {
		   if (currDecidePiece[i].onoff == 1)
		   {
             glPushMatrix();
			 glLoadIdentity();
			 glTranslatef(sx+xOffSet,sy,-10);
			 glCallList(12);
			 glPopMatrix();

		   }
	   }

	 j=j+1;
  }
  glPopMatrix();
}

void resetPit()
{
 for (int i=4;i<14;i++)
    {
	  for (int j=4;j<35;j++)
	  {
		  theBoard[i][j].colour = 0;
		  theBoard[i][j].onoff = 0;
	  }
	}
}

int getRotNumbers(int rotPiece)
{
  int retVal;
  switch (rotPiece) 
  {
		case 0:{ retVal = 0;
                 break; }
		case 1:{ retVal = 16;
                 break; }
		case 2:{ retVal = 32;
                 break; }
		case 3:{ retVal = 48;
                 break; }
		default:{ retVal = 0;
			     break;  }
    }
  return retVal;
}

void loadPiece(int shape[],int pieceRot,int makeActive,int theColour)
{
  int bet1=0;int bet2=0;int bet3=0;
  int i,j;
  int cntPlus;


  cntPlus = getRotNumbers(pieceRot);
  j=0;
  for (i=0;i<16;i++)
  {
	  currTempPiece[i].onoff = shape[i+cntPlus];
	  currTempPiece[i].colour = theColour;
	  
	   if ((i>=0) && (i<=3)) 
	   {
         currTempPiece[i].x = moveX +j;
		 currTempPiece[i].y = moveY;

	   }
	   if ((i>=4) && (i<=7))
	   {
		   if (bet1 == 0)
		   { 
			 j = 0;
			 bet1 = 1;
		   }
           currTempPiece[i].x = moveX + j;
		   currTempPiece[i].y =	moveY - 1;
	   }
	   if ((i>=8) && (i<=11))
	   {
         if (bet2 == 0) 
		 {
			 j = 0;
		     bet2 = 1;
		 }
		 currTempPiece[i].x = moveX + j;
		 currTempPiece[i].y = moveY - 2;
	   }
	   if ((i>=12) && (i<=15))
	   {
		   if (bet3 == 0)
		   {
			 j = 0;
			 bet3 = 1;
		   }
		 currTempPiece[i].x = moveX + j;
		 currTempPiece[i].y = moveY - 3;
	   }  

	   if (makeActive==1) {
		   currActivePiece[i].onoff  = currTempPiece[i].onoff;
		   currActivePiece[i].x      = currTempPiece[i].x;
		   currActivePiece[i].y      = currTempPiece[i].y;
		   currActivePiece[i].colour = theColour;
	   }
	    if (makeActive==2) {
		   nextActivePiece[i].onoff  = currTempPiece[i].onoff;
		   nextActivePiece[i].x      = currTempPiece[i].x;
		   nextActivePiece[i].y      = currTempPiece[i].y;
		   //nextActivePiece[i].colour = darkgrey;
		   nextActivePiece[i].colour = theColour;
	   }
   j=j+1;
  }
}

void loadNewPiece(int pieceNo,int pieceRot, int makeActive)
{
    
	switch (pieceNo)
	{
	case 0: 
		{
           loadPiece(shape_L,pieceRot,makeActive,yellow);
		   pieceColour = yellow;  
		   if (makeActive == 1) strcpy(pieceColourStr, "Yellow");
		   noL +=1;
		   break;
		}
	case 1: 
		{
          loadPiece(shape_S,pieceRot,makeActive,blue);
		  pieceColour = blue;  
		  if (makeActive == 1) strcpy(pieceColourStr, "Blue");
		  noS +=1;
		   break;
		}
	case 2: 
		{
          loadPiece(shape_Z,pieceRot,makeActive,white);
		  pieceColour = black;  
		  if (makeActive == 1) strcpy(pieceColourStr , "Black");
		  noZ +=1;
		   break;
		}
	case 3: 
		{
          loadPiece(shape_O,pieceRot,makeActive,green);
		  pieceColour = green;  
		  if (makeActive == 1) strcpy(pieceColourStr ,"Green");
		  noO +=1;
		   break;
		}
	case 4: 
		{
          loadPiece(shape_T,pieceRot,makeActive,red);
		  pieceColour = red;  
		  if (makeActive == 1) strcpy(pieceColourStr , "Red");
		  noT +=1;
		   break;
		}
	case 5: 
		{
          loadPiece(shape_EL,pieceRot,makeActive,purple);
		  pieceColour = purple; 
          if (makeActive == 1) strcpy(pieceColourStr ,"Purple");
		  noEL +=1;
		   break;
		}
	case 6: 
		{
          loadPiece(shape_LE,pieceRot,makeActive,orange);
		  pieceColour = orange;
		  if (makeActive == 1) strcpy(pieceColourStr ,"Orange");
		  noLE +=1;
		   break;
		}
	}
}

void glPrint(GLfloat xp, GLfloat yp ,void *font, char* format,...)
{
    va_list args;
	char buffer[200], *p;

	va_start(args, format);
	vsprintf(buffer, format ,args);
	va_end(args);

	glPushMatrix();
	//glTranslatef(xp,yp,0);
	glRasterPos2f(xp, yp);
	 for (p = buffer; *p; p++)
	 {
		//glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
		 glutBitmapCharacter(font,*p);
	 }
	 glPopMatrix();
}


void drawBoard()
{ 
  int i,j;
  int printit=0;
  glPushMatrix();
  glLineWidth(0.01);
/**  glColor4f(1.0, 1.0, 1.0, 0.2);
  for (i=4;i<35;i++) 
  {
	  if (i<15) { 
	    glBegin(GL_LINE_STRIP);
        glVertex2f(i,34);
        glVertex2f(i,4);
		glEnd();
	  }
	  glBegin(GL_LINE_STRIP);
        glVertex2f(4,i);
        glVertex2f(14,i);
      glEnd();
  }
**/
 glColor4f(1.0, 1.0, 1.0,1.0);
 glBegin(GL_LINE_STRIP);
        glVertex2f(3.9,34);
        glVertex2f(3.9,4);
 glEnd();
 glBegin(GL_LINE_STRIP);
		glVertex2f(14.1,4);
        glVertex2f(14.1,34);
  glEnd();
  glBegin(GL_LINE_STRIP);
		glVertex2f(4,3.9);
		glVertex2f(14,3.9);
  glEnd();

  glTranslatef(7,35,0);
  for (int i=0;i<5;i++) 
   {
	glColor4f(1.0, 1.0, 1.0 ,0.2);
	glBegin(GL_LINE_STRIP);
      glVertex2f(i,0);
      glVertex2f(i,4);
    glEnd();
    glBegin(GL_LINE_STRIP);
      glVertex2f(4,i);
      glVertex2f(0,i);
    glEnd();
  }
  glPopMatrix();

}

void loadDecidePiece(int shape[], int dAng, int xx, int yy)
{

  int bet1=0;int bet2=0;int bet3=0;
  int i,j;
  int cntPlus;

  j=0;


  cntPlus = getRotNumbers(dAng);
  for (i=0;i<16;i++)
  {
	  currDecidePiece[i].onoff = shape[i+cntPlus];
	  
	   if ((i>=0) && (i<=3)) 
	   {
         currDecidePiece[i].x = xx +j;
		 currDecidePiece[i].y = yy;

	   }
	   if ((i>=4) && (i<=7))
	   {
		   if (bet1 == 0)
		   { 
			 j = 0;
			 bet1 = 1;
		   }
           currDecidePiece[i].x = xx + j;
		   currDecidePiece[i].y =	yy - 1;
	   }
	   if ((i>=8) && (i<=11))
	   {
         if (bet2 == 0) 
		 {
			 j = 0;
		     bet2 = 1;
		 }
		 currDecidePiece[i].x = xx + j;
		 currDecidePiece[i].y = yy - 2;
	   }
	   if ((i>=12) && (i<=15))
	   {
		   if (bet3 == 0)
		   {
			 j = 0;
			 bet3 = 1;
		   }
		 currDecidePiece[i].x = xx + j;
		 currDecidePiece[i].y = yy - 3;
	   }  

	  // printf ("x %i    y%i \n",currDecidePiece[i].x,currDecidePiece[i].y);
		 //  nextActivePiece[i].onoff  = currTempPiece[i].onoff;
		 //  nextActivePiece[i].x      = currTempPiece[i].x;
		 //  nextActivePiece[i].y      = currTempPiece[i].y;


  }
   j=j+1;

}

void loadDecide(int xx, int yy, int dNum, int dAng)
{
	switch (dNum)
	{
	case 0: 
		{
	      loadDecidePiece(shape_L,dAng,xx,yy);
		  break;
		}
	case 1: 
		{
          loadDecidePiece(shape_S,dAng,xx,yy);
		  break;
		}
	case 2: 
		{
          loadDecidePiece(shape_Z,dAng,xx,yy);
		  break;
		}
	case 3: 
		{
          loadDecidePiece(shape_O,dAng,xx,yy);
		  break;
		}
	case 4: 
		{
          loadDecidePiece(shape_T,dAng,xx,yy);
		  break;
		}
	case 5: 
		{
          loadDecidePiece(shape_EL,dAng,xx,yy);
		  break;
		}
	case 6: 
		{
          loadDecidePiece(shape_LE,dAng,xx,yy);
		  break;
		}
}
}




int getLowest(int xVal,int decideNum,int decideAngle)
{
   int canMove=1;
   int retVal=35; int temp=0;

   for (int k=34;k>4;k--)
   { 
	 
     loadDecide(xVal,k,decideNum,decideAngle);
	 for (int i=0;i<30;i++)
     {
        if (currDecidePiece[i].onoff == 1)
	    {
			if (currDecidePiece[i].x <= 3) continue;
				

			if ((theBoard[currDecidePiece[i].x][currDecidePiece[i].y].onoff == 1) || 
                 (currDecidePiece[i].y <= 4))
			{
             temp = currDecidePiece[i].y;
			 if (temp < retVal) retVal = temp;
		  	 canMove = 0;
			 break;
			}
			
	    }
		if (canMove == 0) break;
      }


  }
  return retVal;
}

void initNewPiece()
{
  needNewPiece = 0;
  moveX = STARTX;
  moveY = STARTY;
  pieceAngle = 0;
  loadNewPiece(newPieceNo,0,1);
  currPieceNo = newPieceNo;
  newPieceNo=rand()%7;
  loadNewPiece(newPieceNo,0,2);
  //decide();
  currScore += 50;
}




void drawDroppedPieces()
{
  glLoadIdentity();
  glPushMatrix();

	for (int i=4;i<14;i++)
    {
	  for (int j=4;j<35;j++)
	  {
		  if (theBoard[i][j].onoff == 1)
		  {
            glLoadIdentity();
			glTranslatef(theBoard[i][j].x+xOffSet,theBoard[i][j].y,0);
			glCallList(theBoard[i][j].colour);
     	  }
	  }
	}
  glPopMatrix();
  glutPostRedisplay();
}

void moveDown(int fillLineNo)
{
	  /** first initialize theBoard's current y values to 0; **/
	theBoard[4][fillLineNo].onoff =0; theBoard[4][fillLineNo].colour = 0; theBoard[5][fillLineNo].onoff =0; theBoard[5][fillLineNo].colour =0;
 	theBoard[6][fillLineNo].onoff =0; theBoard[6][fillLineNo].colour = 0; theBoard[7][fillLineNo].onoff =0; theBoard[7][fillLineNo].colour =0;
	theBoard[8][fillLineNo].onoff =0; theBoard[8][fillLineNo].colour = 0; theBoard[9][fillLineNo].onoff =0; theBoard[9][fillLineNo].colour =0;
	theBoard[10][fillLineNo].onoff =0; theBoard[10][fillLineNo].colour = 0; theBoard[11][fillLineNo].onoff =0; theBoard[11][fillLineNo].colour =0;
	theBoard[12][fillLineNo].onoff =0; theBoard[12][fillLineNo].colour = 0; theBoard[13][fillLineNo].onoff =0; theBoard[13][fillLineNo].colour =0;

// theBoard[4][fillLineNo].colour = 4;  theBoard[5][fillLineNo].colour =4;
 //theBoard[6][fillLineNo].colour = 4; theBoard[7][fillLineNo].colour =4;
// theBoard[8][fillLineNo].colour = 4;  theBoard[9][fillLineNo].colour =4;
// theBoard[10][fillLineNo].colour = 4;  theBoard[11][fillLineNo].colour =4;
// theBoard[12][fillLineNo].colour = 4; theBoard[13][fillLineNo].colour =4;





	

	 for (int i=4;i<14;i++)
    {
	  for (int j=4;j<35;j++)
	  {
		  if (j>fillLineNo)
		  {
		    if (theBoard[i][j].onoff == 1)
		    {
			    theBoard[i][j-1].colour = theBoard[i][j].colour;
			    theBoard[i][j-1].onoff  = theBoard[i][j].onoff;
			    theBoard[i][j].colour = theBoard[i][j+1].colour;
			    theBoard[i][j].onoff  = theBoard[i][j+1].onoff;
		    }
		  }
	  }
	}
}

void checkFullRow()
{
   int isPieceReset=0;
   OKnewPiece = 0;
   int numRow=0;

   for (int  i=4;i<35;i++)
   {
	   if ((theBoard[4][i].onoff == 1) && (theBoard[5][i].onoff == 1) &&
		   (theBoard[6][i].onoff == 1) && (theBoard[7][i].onoff == 1) &&
		   (theBoard[8][i].onoff == 1) && (theBoard[9][i].onoff == 1) &&
		   (theBoard[10][i].onoff == 1) && (theBoard[11][i].onoff == 1) &&
		   (theBoard[12][i].onoff == 1) && (theBoard[13][i].onoff == 1)) 
	   {
		   moveDown(i); 
		   totNumRowsDone += 1;
		   numRow +=1;
	   }
   }
   OKnewPiece = 1;
   switch (numRow) {
	   case 1: {
		         totNum1 += 1;
                 break;
			   }
	   case 2: {
		         totNum2 += 1;
                 break;
			   }
	   case 3: {
		         totNum3 += 1;
		         break;
			   }
	   case 4: {
		         totNum4 += 1;
		         break;
			   }
   }
   if (numRow > 4) totNumOther += 1;
   numRow = 0;
}

void fillBoard()
{
  int j=0;
  for (int i=0;i<16;i++)
  {
	  if (currActivePiece[i].onoff == 1)
	  {
		  theBoard[currActivePiece[i].x][currActivePiece[i].y].colour = currActivePiece[i].colour;
		  theBoard[currActivePiece[i].x][currActivePiece[i].y].onoff = 1;
	  }      
  }

  for (int j=0;j<16;j++) 
  {
    currActivePiece[j].onoff =0;
    currActivePiece[j].colour = 0;
  }

 // checkFullRow();
}

void rotatePiece()
{
  int canMove = 1;
  int i,j;
  int tempAngle;

  tempAngle = pieceAngle + 1;
  if (tempAngle == 4) tempAngle = 0;
  loadNewPiece(currPieceNo,tempAngle,0);
  for (i=0;i<16;i++)
  {
	  if (currTempPiece[i].onoff == 1)
	  {
         if (currTempPiece[i].x+xOffSet  < 3)
			 canMove = 0;
		 if (currTempPiece[i].x+xOffSet  > 12)
			 canMove = 0;
		 if (theBoard[currTempPiece[i].x][currTempPiece[i].y].onoff == 1)
			 canMove = 0;
	  }
  }

   if (canMove == 1)
  {
	pieceAngle = pieceAngle + 1;
	if (pieceAngle == 4) pieceAngle = 0;
    for (i=0;i<16;i++)
    {
	    currActivePiece[i].onoff  = currTempPiece[i].onoff;
		currActivePiece[i].x      = currTempPiece[i].x;
		currActivePiece[i].y      = currTempPiece[i].y;
		currActivePiece[i].colour = currTempPiece[i].colour;
    }
    loadNewPiece(currPieceNo,pieceAngle,1);
  }

}

void movePieceX(int mag)
{
  int canMove = 1;
  int i,j;

  for (i=0;i<16;i++)
  {
     if (currActivePiece[i].onoff == 1)
	 {
		 if (currActivePiece[i].x+xOffSet + mag < 3)
			 canMove = 0;
		 if (currActivePiece[i].x+xOffSet + mag > 12)
			 canMove = 0;
		 if (theBoard[currActivePiece[i].x+mag][currActivePiece[i].y].onoff == 1)
			 canMove = 0;
	 }
  }

  if (canMove == 1)
  {
	moveX = moveX + mag;
    for (i=0;i<16;i++)
    {
	    currActivePiece[i].x += mag;
    }
  } 
}

void movePieceY(int mag)
{
  int canMove = 1;

   for (int i=0;i<16;i++)
   {
     if (currActivePiece[i].onoff == 1)
	 {
		 if (currActivePiece[i].y + mag <= 3)
			 canMove = 0;
		 if (theBoard[currActivePiece[i].x][currActivePiece[i].y+ mag].onoff == 1)
			 canMove = 0;
	 }
   }

   if (canMove == 0)
   {
	   fillBoard();
	   needNewPiece = 1;
   }

   if (canMove == 1)
   {
	 moveY += mag;
	 for (int i=0;i<16;i++)
     {
	   currActivePiece[i].y += mag;
     }
   }
}

void printRunningScores()
{
  glColor4f(1.0,0.0,0.0,1.0);
  glPrint(200,800,GLUT_BITMAP_HELVETICA_18,"%i",currScore);
}


void drawText()
{
  
  glPushMatrix();
	  glOrtho(0,400,0,400,0,400);
	  glMatrixMode(GL_MODELVIEW);
	  glColor4f(0.5,0.5,0.5,1.05);
	  switch (gameMode){
	  case 1:
		  {
		    glColor4f(0.5,0.5,0.5,1.05);
		    glPrint(1000,1000,GLUT_BITMAP_HELVETICA_12,"X: %i   Y: %i",mouseX, mouseY);
			glPrint(1000,800,GLUT_BITMAP_HELVETICA_12,"%i",glutGet(GLUT_ELAPSED_TIME));
		    glPrint(1000,600,GLUT_BITMAP_HELVETICA_12,"start#: %i",startCnt);

			if (startCnt == 0) glColor3f(1.0,1.0,0.0); else glColor4f(0.0,0.0,1.0,1.0);
			glPrint(3700,5400,GLUT_BITMAP_HELVETICA_18,"New Game");

			if (startCnt == 1) glColor3f(1.0,1.0,0.0); else glColor4f(0.0,0.0,1.0,1.0);
			glPrint(3700,5000,GLUT_BITMAP_HELVETICA_18,"Close");

			if (gameInProgress == 1) {
			   if (startCnt == 2) glColor3f(1.0,1.0,0.0); else glColor4f(0.0,0.0,1.0,1.0); 
               glPrint(3700,4600,GLUT_BITMAP_HELVETICA_18,"Continue");
			}

			
		    break;
		  }
	  case 2:
		  {
			glDisable(GL_LIGHTING);
			//glColor4f(0.7,0.0,1.0,alphaFader);
			//glPrint(4200,7800,GLUT_BITMAP_TIMES_ROMAN_24,"OpenGL Vendor: %s\n",glGetString(GL_VENDOR));
			//glPrint(4200,7600,GLUT_BITMAP_TIMES_ROMAN_24,"OpenGL Renderer: %s\n",glGetString(GL_RENDERER));
			//glPrint(4200,7400,GLUT_BITMAP_TIMES_ROMAN_24,"OpenGL Version: %s\n",glGetString(GL_VERSION));
			//glPrint(4200,7200,GLUT_BITMAP_9_BY_15,"Zoom %i",z_zoom);
			//glPrint(4200,7000,GLUT_BITMAP_9_BY_15,"New Piece # %i",newPieceNo);
			//glPrint(4200,6800,GLUT_BITMAP_9_BY_15,"My FPS: %i",fps);
			//glPrint(4200,6600,GLUT_BITMAP_9_BY_15,"Number Rows: %i",totNumRowsDone);
			//glPrint(4200,6400,GLUT_BITMAP_HELVETICA_18,"Colour: %i  %s",pieceColour,pieceColourStr);
			//glColor4f(1.0,0.45,0.0,1.0);
		//	
			glPrint(7000,200,GLUT_BITMAP_HELVETICA_12,"FPS :%i",fps);
			glPrint(7000,800,GLUT_BITMAP_HELVETICA_12,"pieceNo :%i   pieceAngle :%i",currPieceNo,pieceAngle);

			glPrint(3200,1000,GLUT_BITMAP_HELVETICA_12,"Level: %i",1);
			glPrint(3200,1200,GLUT_BITMAP_HELVETICA_12,"Position: %i",20);
			glPrint(3200,1400,GLUT_BITMAP_HELVETICA_12,"Speed: %i",1);
			glPrint(3200,1600,GLUT_BITMAP_HELVETICA_12,"Rows: %i",totNumRowsDone);
			glPrint(3200,1800,GLUT_BITMAP_HELVETICA_12,"Score: %i",18000000);
			glPrint(3200,2000,GLUT_BITMAP_HELVETICA_12,"1's: %i",totNum1);
			glPrint(3200,2200,GLUT_BITMAP_HELVETICA_12,"2's: %i",totNum2);
			glPrint(3200,2400,GLUT_BITMAP_HELVETICA_12,"3's: %i",totNum3);
			glPrint(3200,2600,GLUT_BITMAP_HELVETICA_12,"4's: %i",totNum4);
			glPrint(3200,2800,GLUT_BITMAP_HELVETICA_12,"Not supposed to happen: %i",totNumOther);
			glPrint(3200,3000,GLUT_BITMAP_HELVETICA_12,"start#: %i",startCnt);

			printRunningScores();

			
	        if (pausedMode == 1){
              glColor4f(1.0,1.0,1.0,1.0);
              glPrint(1800,6000,GLUT_BITMAP_TIMES_ROMAN_24,"PAUSED");
			 // glEnable(GL_LIGHTING);
	        }
			break;
		  }
	  }
			
  glPopMatrix();
}

void drawNextBlock3D()
{
  drawActivePiece(7,38,2); 
  glLoadIdentity();
  glPushMatrix();

  glTranslatef(15,34,-10);
  glRotatef(angle,1.0,1.0,1.0);
  glColor4f(0.5,0.5,0.5,0.9);
  for (int j=0;j<5;j++)
  {
  for (int i=0;i<5;i++) 
   {
	glBegin(GL_LINE_STRIP);
      glVertex3f(i,0,j);
      glVertex3f(i,4,j);
    glEnd();
	glBegin(GL_LINE_STRIP);
      glVertex3f(4,i,j);
      glVertex3f(0,i,j);
    glEnd();
	glBegin(GL_LINE_STRIP);
      glVertex3f(j,i,4);
      glVertex3f(j,i,0);
    glEnd();
   }
  }
  glPopMatrix();

}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON){
		if (state == GLUT_DOWN){
			anchorX = x;
			anchorY = y;
			stretchX = x;
			stretchY = y;

		}
        // New Game
		if ((gameMode == 1) && (mouseX <= 542) && (mouseX >= 446) && (mouseY <= 271) && (mouseY >= 251)) {
			gameMode = 2;
			pausedMode = 0;
			resetPit();
			gameInProgress = 1;
			///PlaySound("Sounds/war_cry.wav",NULL,SND_ASYNC);
			initNewPiece();
		}
        // Quit
		if ((gameMode == 1) && (mouseX <= 490) && (mouseX >= 446) && (mouseY <= 385) && (mouseY >= 363)) {
          exit(0);
		}
		//Continue
		if ((gameMode == 1) && (mouseX <= 524) && (mouseX >= 446) && (mouseY <= 231) && (mouseY >= 213) 
			 && (gameInProgress == 1)) {
            gameMode = 2;
			pausedMode = 0;
			gameInProgress = 1;
		}
        // HighScores
		if ((gameMode == 1) && (mouseX <= 524) && (mouseX >= 446) && (mouseY <= 311) && (mouseY >= 293)) {
		  gameMode = 3;
		  pausedMode = 0;
		}
	}
}

void motion(int x, int y)
{
 stretchX = x;
 stretchY = y;
}

void passive(int x, int y)
{
 mouseX = x;
 mouseY = y;

glBegin(GL_LINE_STRIP);
    glVertex2f(mouseX+20,mouseX-20);
    glVertex2f(mouseY+20,mouseY-20);
 glEnd();
 
 if ((gameMode == 1) && (mouseX <= 542) && (mouseX >= 446) && (mouseY <= 271) && (mouseY >= 251))
 {
   // New Game
   startCnt = 0;
   glutSetCursor(GLUT_CURSOR_INHERIT);
 } 

 if ((gameMode == 1) && (mouseX <= 542) && (mouseX >= 446) && (mouseY <= 311) && (mouseY >= 293))
 {
   // HighScores
   startCnt = 1;
   glutSetCursor(GLUT_CURSOR_INHERIT); 
 } 

 if ((gameMode == 1) && (mouseX <= 516) && (mouseX >= 446) && (mouseY <= 343) && (mouseY >= 330))
 {
   // Credits
   startCnt = 2;
   glutSetCursor(GLUT_CURSOR_INHERIT); 
 } 

 if ((gameMode == 1) && (mouseX <= 490) && (mouseX >= 446) && (mouseY <= 385) && (mouseY >= 363))
 {
   // Quit
   startCnt = 3;
   glutSetCursor(GLUT_CURSOR_INHERIT); 
 } 

 if ((gameMode == 1) && (gameInProgress) &&
	 (mouseX <= 524) && (mouseX >= 446) && (mouseY <= 231) && (mouseY >= 213))
 {
   // Continue
   startCnt = 4;
   glutSetCursor(GLUT_CURSOR_INHERIT);
 }
  //glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);

}
void drawStartStuff()
{
  glDisable(GL_DEPTH_TEST);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(0.01);
  glLoadIdentity();

   glViewport(0,0,1024,768);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0,1024,0,768);
   glScalef(2,2,2);
   glTranslatef(0,-768,0);

   glBegin(GL_LINE_LOOP);
      glVertex2f(anchorX,anchorY);
      glVertex2f(anchorX,stretchY);
	  glVertex2f(stretchX,stretchY);
      glVertex2f(stretchX,anchorY);
   glEnd();
   glutWireCube(5.0);
	
   glMatrixMode(GL_PROJECTION);
   gluPerspective(180,    /*degrees field of view*/
                  1024/768,   /*aspect ratio*/
                  1.0,   /*Z near*/
                  -900.0);  /*Z far*/
   glLoadIdentity();
   glOrtho(0,40, 0, 40, 0, 40);
   glMatrixMode(GL_MODELVIEW);
   gluLookAt(0.0, 0.0, 600.0, /* Eye is at */
             0.0, 0.0,  0.0, /* Center is at */
             0.0, 1.0, 0.);  /* Up is positive Y direction */
   glLoadIdentity();

   //loadNewPiece(newPieceNo,0,2);
   
   //glDisable(GL_DEPTH_TEST);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glLineWidth(1.5);
 //  glEnable(GL_LIGHTING);
 //  glEnable(GL_LIGHT0);
  // glEnable(GL_LIGHT1);
   glLineWidth(0.01);
   loadNewPiece(0,0,2); glColor4f(1.0,1.0,1.0,0.5); drawActivePiece(3,38,3);
   loadNewPiece(1,0,2); glColor4f(1.0,1.0,0.0,0.5); drawActivePiece(7,38,3);
   loadNewPiece(2,0,2); glColor4f(0.0,1.0,0.0,0.5); drawActivePiece(11,38,3);
   loadNewPiece(3,0,2); glColor4f(0.0,0.0,1.0,0.5); drawActivePiece(15,38,3);
   loadNewPiece(4,0,2); glColor4f(0.7,0.0,1.0,0.5); drawActivePiece(19,38,3);
   loadNewPiece(5,0,2); glColor4f(1.0,0.9,0.0,0.5); drawActivePiece(23,38,3);
   loadNewPiece(6,0,2); glColor4f(1.0,1.0,1.0,0.5); drawActivePiece(27,38,3);
   loadNewPiece(0,0,2); glColor4f(0.0,1.0,0.0,0.5); drawActivePiece(31,38,3);
   loadNewPiece(1,0,2); glColor4f(1.0,0.0,0.0,0.5); drawActivePiece(35,38,3);

   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   glColor4f(1.0,1.0,1.0,1.5);
   loadNewPiece(0,0,2);
   drawActivePiece(3,38,3);
   
   glColor4f(1.0,1.0,0.0,1.5);
   loadNewPiece(1,0,2);
   drawActivePiece(7,38,3);
   
   glColor4f(0.0,1.0,0.0,1.5);
   loadNewPiece(2,0,2);
   drawActivePiece(11,38,3);

   glColor4f(0.0,0.0,1.0,1.5);
   loadNewPiece(3,0,2); 
   drawActivePiece(15,38,3);
  
   glColor4f(0.7,0.0,1.0,1.5);
   loadNewPiece(4,0,2);
   drawActivePiece(19,38,3);
   
   glColor4f(1.0,0.9,0.0,1.5);
   loadNewPiece(5,0,2);
   drawActivePiece(23,38,3);
   
   glColor4f(1.0,1.0,1.0,1.5);
   loadNewPiece(6,0,2);
   drawActivePiece(27,38,3);

   glColor4f(0.0,1.0,0.0,1.5);
   loadNewPiece(0,0,2);
   drawActivePiece(31,38,3);
   
   glColor4f(1.0,0.0,0.0,0.5);
   loadNewPiece(1,0,2);
   drawActivePiece(35,38,3);

   glLoadIdentity();
   glTranslatef(20,10,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  //gllRotatef(angle,1,1,1);
   //glutSolidTeapot(2.0);
 //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
 //  glutSolidTeapot(2.0);
   //glCallList(11);
   glLoadIdentity();


}

void renderStartScreen()
{
  pausedMode = 1;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glClearColor(0.0,0.0,0.0,0.0);
  drawText();
  drawStartStuff();
}

void renderGameScreen()
{
  int temp,temp2;

  glutSetCursor(GLUT_CURSOR_NONE);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
  glClearColor(0.0,0.0,0.0,0.0);
  temp = 1024*768*3;
  if (pausedMode == 1) {
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
  }

  if (isBlendMode) { glShadeModel(GL_SMOOTH); } else { glShadeModel(GL_FLAT); }
  if (isLineMode)
  {
    glDisable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(0.01);
  } else 
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
	glLineWidth(1.0);
  }

  if (isFogMode)
  {
  }

  drawText();
  drawBoard();
  drawActivePiece(moveX,moveY,1);
  drawDroppedPieces();
  checkFullRow();
  drawNextBlock3D();
  drawText();
  if(glGetError()) printf("oops! Bad gl command!\n");
}


void renderHighScores()
{
  pausedMode = 1;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glClearColor(0.0,0.0,0.5,0.5);
  glLoadIdentity();
  drawText();
 // inputName();
}


void render(void)
{
	
    switch (gameMode) 
      {
	    case 1: {renderStartScreen(); break;} 
	    case 2: {renderGameScreen(); break;}
	    case 3: {renderHighScores(); break;}
      }
	ticks += 1;
	glutSwapBuffers();
    vRenderCnt +=1;
}

void idle(void)
{
  angle = angle+0.4;
  glutPostRedisplay();
  vIdleCnt += 1;
}

void visible(int vis)
{
 // if (vis == GLUT_VISIBLE) {
  //  if (!paused) {
      glutIdleFunc(idle);
  //  }
  //} else {
 // //  glutIdleFunc(NULL);
 // }
}



void key(unsigned char key, int px, int py)
{
	switch (key){
       case 27:  {       
		   if (gameMode == 1 && startCnt == 1) { printf("dieeee!!!\n"); exit(0); }
		   if (gameMode == 2) {
			   gameMode = 1;
			   pausedMode = 0;
			   startCnt = 4;
			   glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
		   }
		   break;
			     }
       case 13:  {       
		             if (gameMode == 1 && startCnt == 1) { printf("dieeee!!!\n"); exit(0); }
		             if ((gameMode == 1) && (startCnt == 0)) {
			             gameMode = 2;
			             pausedMode = 0;
			             resetPit();
			             gameInProgress = 1;
			             //PlaySound("Sounds/war_cry.wav",NULL,SND_ASYNC);
			             initNewPiece();
		             }
		             if ((gameMode == 1) && (startCnt == 1)) {
                         exit(0);
		             }
		             if ((gameMode == 1) && (startCnt == 2)) {
                         gameMode = 2;
			             pausedMode = 0;
			             gameInProgress = 1;
		             }
                 }
                 break;
	   case 'b':{
			     isBlendMode = !isBlendMode;
	           	 break;
				}
	   case 'l':{
			     isLineMode = !isLineMode;
	           	 break;
				}
		case 'f':{
			     isFogMode = !isFogMode;
				 break;
				}
		case 't':{
			     isTrailsMode = !isTrailsMode;
				 break;
				}
		case '\t':{
			        break;
				   }
		case 'p': {
			      if (gameMode == 2) {
			        pausedMode = !pausedMode;
				  	if (pausedMode == 1) glutIdleFunc(NULL); else glutIdleFunc(idle);
		      	    }
                  break;
			      }
		case 'x': {
			        glEnable(GL_LIGHT1);
					glEnable(GL_LIGHT0);
			        glEnable(GL_LIGHTING);
					break;
				  }
	}
}

void keyup(unsigned char key, int x, int y)
{
  
}

void special(int key, int x, int y)
{
  int i = 0;
  switch (key) 
  {
    case GLUT_KEY_RIGHT:
	{
      if (pausedMode == 0) movePieceX(1);
      i++;
    }
    break;
    case GLUT_KEY_LEFT:
	{
      if (pausedMode == 0) movePieceX(-1);
      i++;
    }
    break;
    case GLUT_KEY_DOWN:
	{
	  if ((gameMode == 2) && (pausedMode == 0)) movePieceY(-1);
	  if (gameMode == 1) {
          startCnt += 1;
          if (gameInProgress) {
              if (startCnt > 2) startCnt = 2;
          }
          else 
          {
              if (startCnt > 1) startCnt =1;
          }
      }
	  i++;
    }
    break;
    case GLUT_KEY_UP:
	{
      if ((gameMode == 2) &&(pausedMode == 0)) { rotatePiece(); break; } 
	  if (gameMode == 1) {
          startCnt -= 1;
          if (startCnt < 0) startCnt = 0;
      }
      i++;
    }
    break;
	case GLUT_KEY_F1:
	{
		if ((gameMode == 1) && (startCnt == 0)) {
			gameMode = 2;
			pausedMode = 0;
			resetPit();
			gameInProgress = 1;
			//PlaySound("Sounds/war_cry.wav",NULL,SND_ASYNC);
			initNewPiece();
		}
		
		if ((gameMode == 1) && (startCnt == 1)) {
          exit(0);
		}

		if ((gameMode == 1) && (startCnt == 2)) {
            gameMode = 2;
			pausedMode = 0;
			gameInProgress = 1;
		}
		i++;
	}
    break;
  }
  if (i) glutPostRedisplay();
}

void specialup(int key, int x, int y)
{

}

void moveColours()
{
  int tempColour;

    for (int i=4;i<14;i++)
    {
	  for (int j=4;j<35;j++)
	  {
		    if (theBoard[i][j].onoff == 1)
		    {
				if (theBoard[i][j+1].onoff == 1) 
				{
				  if (i == 13) 
				  	theBoard[i][j].colour = theBoard[1][j].colour;
				  else 
					theBoard[i][j].colour = theBoard[i][j+1].colour;
				}
		    }
	  }
	}
}

void timerFunc(int value)
{
   
	switch (value) 
	{
	  case 1:
		{
          glutTimerFunc(250,timerFunc,1);
          if ((needNewPiece == 1) && (OKnewPiece == 1))
          {
	       initNewPiece();
          } else
          {
            if (pausedMode == 0) movePieceY(-1);
          }
	      break;
		}
	  case 2:
		{
          glutTimerFunc(1000,timerFunc,2);
		  fps = ticks;
		  ticks = 0;

		//  moveColours();
          break;
	    }
	  case 3:
		{
          glutTimerFunc(50,timerFunc,3);
          break;
	    }

   }

}




void initDisplayLists()
{
  border1=glGenLists(11);
  glNewList(border1,GL_COMPILE);
      glBegin(GL_QUADS);
	    glColor3f(1,0,0);
	    glVertex3f(2,0,0);
		glColor3f(0,1,1);
        glVertex3f(2,1,0);
		glColor3f(0,0,1);
		glVertex3f(1,1,0);
		glColor3f(1,1,1);
		glVertex3f(1,0,0);
	  glEnd();
   glEndList();
  border2=border1+1;
  glNewList(border2,GL_COMPILE);
      glBegin(GL_QUADS);
	    glColor3f(0,0,1);
	    glVertex3f(2,0,0);
		glColor3f(1.0,1.0,1.0);
        glVertex3f(2,1,0);
		glColor3f(1,1,1);
		glVertex3f(1,1,0);
		glColor3f(1.0,1.0,1.0);
		glVertex3f(1,0,0);
	  glEnd();
   glEndList();
   blue=border2+1;
   glNewList(blue,GL_COMPILE);
      glBegin(GL_QUADS);
	    glColor4f(0.0,0.0,0.3,1.0);
	    glVertex3f(2,0,0);
		glColor4f(0.0,0.0,0.3,1.0);
        glVertex3f(2,1,0);
		glColor4f(0.0,0.0,1.0,1.0);
		glVertex3f(1,1,0);
		glColor4f(0.0,0.0,0.3,1.0);
		glVertex3f(1,0,0);
	  glEnd();
   glEndList();
   darkgrey=blue+1;
   glNewList(darkgrey,GL_COMPILE);
      glBegin(GL_QUADS);
	    glColor3f(0.7,0.7,0.7);
	    glVertex3f(2,0,0);
		glColor3f(0.7,0.7,0.7);
        glVertex3f(2,1,0);
		glColor3f(1,1,1);
		glVertex3f(1,1,0);
		glColor3f(0.7,0.7,0.7);
		glVertex3f(1,0,0);
	  glEnd();
   glEndList();
   yellow=darkgrey+1;
   glNewList(yellow,GL_COMPILE);
      glBegin(GL_QUADS);
	    glColor4f(0.7,0.7,0.0,1.0);
	    glVertex3f(2,0,0);
		glColor4f(0.7,0.7,0.0,1.0);
        glVertex3f(2,1,0);
		glColor4f(1.0,1.0,0.0,1.0);
		glVertex3f(1,1,0);
		glColor4f(0.7,0.7,0.0,1.0);
		glVertex3f(1,0,0);
	  glEnd();
   glEndList();
   white=yellow+1;
   glNewList(white,GL_COMPILE);
      glBegin(GL_QUADS);
	    glColor3f(1.0,1.0,1.0);
	    glVertex3f(2,0,0);
		glColor3f(1.0,1.0,1.0);
        glVertex3f(2,1,0);
		glColor3f(0.6,0.6,0.6);
		glVertex3f(1,1,0);
		glColor3f(1.0,1.0,1.0);
		glVertex3f(1,0,0);
	  glEnd();
   glEndList();
   green=white+1;
   glNewList(green,GL_COMPILE);
      glBegin(GL_QUADS);
	    glColor4f(0.0,0.2,0.0,1.0);
	    glVertex3f(2,0,0);
		glColor4f(0.0,0.2,0.0,1.0);
        glVertex3f(2,1,0);
		glColor4f(0.0,0.7,0.0,1.0);
		glVertex3f(1,1,0);
		glColor4f(0.0,0.2,0.0,1.0);
		glVertex3f(1,0,0);
	  glEnd();
   glEndList();
   red=green+1;
   glNewList(red,GL_COMPILE);
      glBegin(GL_QUADS);
	    glColor3f(0.4,0.0,0.0);
	    glVertex3f(2,0,0);
		glColor3f(0.4,0.0,0.0);
        glVertex3f(2,1,0);
		glColor3f(1.0,0.0,0.0);
		glVertex3f(1,1,0);
		glColor3f(0.4,0.0,0.0);
		glVertex3f(1,0,0);
	  glEnd();
   glEndList();
   black=red+1;
   glNewList(black,GL_COMPILE);
      glBegin(GL_QUADS);
	    glColor3f(0.0,0.0,0.0);
	    glVertex3f(2,0,0);
		glColor3f(0.0,0.0,0.0);
        glVertex3f(2,1,0);
		glColor3f(0.3,0.3,0.3);
		glVertex3f(1,1,0);
		glColor3f(0.0,0.0,0.0);
		glVertex3f(1,0,0);
	  glEnd();
   glEndList();
   orange=black+1;
   glNewList(orange,GL_COMPILE);
      glBegin(GL_QUADS);
	    glColor4f(1.0,0.45,0.0,1.0);
	    glVertex3f(2,0,0);
		glColor4f(1.0,0.45,0.0,1.0);
        glVertex3f(2,1,0);
		glColor4f(1.0,0.9,0.0,1.0);
		glVertex3f(1,1,0);
		glColor4f(1.0,0.45,0.0,1.0);
		glVertex3f(1,0,0);
	  glEnd();
   glEndList();
   purple=orange+1;
   glNewList(purple,GL_COMPILE);
      glBegin(GL_QUADS);
	    glColor4f(0.5,0.0,1.0,1.5);
	    glVertex3f(2,0,0);
		glColor4f(0.5,0.0,1.0,1.5);
        glVertex3f(2,1,0);
		glColor4f(0.7,0.0,1.0,1.0);
		glVertex3f(1,1,0);
		glColor4f(0.5,0.0,1.0,1.5);
		glVertex3f(1,0,0);
	  glEnd();
	//  glColor4f(0.7,0.0,1.0,1.0);
	 // glTranslatef(1.5,0.5,0.0);
	//  glutWireCube(1.0);
   glEndList();
   decidePiece=purple+1;
   glNewList(decidePiece,GL_COMPILE);
     glBegin(GL_QUADS);
	    glColor4f(0.8,0.8,0.8,1.0);
	    glVertex3f(2,0,0);
        glColor4f(0.8,0.8,0.8,1.0);
        glVertex3f(2,1,0);
        glColor4f(0.8,0.8,0.8,1.0);
		glVertex3f(1,1,0);
        glColor4f(0.8,0.8,0.8,1.0);
		glVertex3f(1,0,0);
	  glEnd();
   glEndList();


}

void initWindow(void)
{
  //glutIgnoreKeyRepeat(1);
  glutDisplayFunc(render);
  glutVisibilityFunc(visible);
  glutKeyboardFunc(key);
  glutKeyboardUpFunc(keyup);
  glutSpecialFunc(special);
  glutSpecialUpFunc(specialup);  
  glutTimerFunc(1000,timerFunc,1);
  glutTimerFunc(1000,timerFunc,2);
  glutTimerFunc(300,timerFunc,3);
  glPointSize(3.0);
  glEnable(GL_BLEND);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_NORMALIZE);
 // glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	
  //glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);	
  glEnable(GL_ALPHA_TEST);
  //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_POLYGON_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_ALWAYS); 
  glEnable(GL_CULL_FACE);
  glClearColor(0.0,0.0,0.0,1.0);
 

  glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient); // Setup The Ambient Light
  glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse); // Setup The Diffuse Light
  glLightfv(GL_LIGHT1, GL_POSITION,LightPosition); // Position The Light
  glEnable(GL_LIGHT1); // Enable Light One
  glEnable(GL_COLOR_MATERIAL); // Enable Coloring Of Material ( NEW )

  glMatrixMode(GL_PROJECTION);
  gluPerspective(80,    /*degrees field of view*/
                 800/600,   /*aspect ratio*/
                 1.0,   /*Z near*/
                 -900.0);  /*Z far*/
 glLoadIdentity();
 glOrtho(0,40, 0, 40, 0, 40);
 glMatrixMode(GL_MODELVIEW);
 gluLookAt(0.0, 0.0, 600.0, /* Eye is at */
           0.0, 0.0,  0.0, /* Center is at */
           0.0, 1.0, 0.);  /* Up is positive Y direction */


  for (int i=3;i<14;i++)
  {
	for (int j=4;j<35;j++)
	{
       theBoard[i][j].x = i;
	   theBoard[i][j].y = j;
	   theBoard[i][j].onoff = 0;
	   theBoard[i][j].colour = 0;
	}
  }
  newPieceNo=rand()%7;
  getRotNumbers(0);

}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH| GLUT_STENCIL);
  if (isGameMode) {
	 glutGameModeString("1024x768:32");            
	 if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE))
		  glutEnterGameMode();                     
	 else isGameMode = 0;                     
	}
  if (!isGameMode) {
	  glutInitWindowSize(1024, 768);                
	  glutCreateWindow("tetris");
	}
 
  initWindow();
  initDisplayLists();

  glutMainLoop();
  return 0;          
}

