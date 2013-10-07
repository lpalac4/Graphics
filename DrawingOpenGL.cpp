/*
 * File:   DrawingOpenGL.cpp
 * Author: Luis Palacios
 * Project draws my name, a smiley face using my own line drawing algorithm(linear algebra) 
 * and fills those drawings using the Adjacent Edge Table algorithm. Use the 'a' and 'd' to 
 * switch between the name, smiley face and the filled smiley face.
 *
 * Date: Sep 26th, 2012
 *
 * Operating System: Ubuntu 32bit
 * Compiler: g++
 */


#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>


using namespace std;

void Line( int x0, int y0,int xl,int yl);
void paintFace();

/* Intialization of the sign of drawing graphics */
bool run = true;
bool drawName = true;
bool drawFace = false;
bool fillFace = false;
int page = 0;

/* Struct to hold the tuple of values representing an edge */
struct edges{
  double xmin;
  double ymax;
  double invm;
};

vector<edges> buckets[1000];

/******************************************************************/

/* output code by Mark Kilgard */
void output(int x, int y, char *string)
{
  int len, i;
  glRasterPos2f(x, y);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) 
  {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
  }
}


/*
 * This function takes coordinates for a line
 * and calculates the slope of it. This data is stored
 * in the vector edges by the minimum y value.
 */
void Line(int x0, int y0, int xl, int yl){
  
  if(xl<x0){              //This insures that the line is drawn from left to right
	int tmp = x0;
	x0 = xl;
	xl = tmp;
	tmp = y0;
	yl = y0;
	y0 = tmp;
  }
  
  double dx = xl - x0;
  double dy = yl - y0;
  double m = dy/dx;
  
  if(fillFace == true){  //adding this line will only be stored in edges if were attempting to fill
      struct edges thisEdge;  //the polygons
      int ymin;
      thisEdge.invm = 1/m;
      if(y0 < yl){
	thisEdge.xmin = x0;
	thisEdge.ymax = yl;
	ymin = y0;
      }else{
	thisEdge.xmin = xl;
	thisEdge.ymax = y0;
	ymin = yl;
      }
      buckets[ymin].push_back(thisEdge);
  }
  
  /* The following section draws the line according to its slope */
  if(m>=0 && m<=1){
    int d = 2*dy - dx;
    int incrE = 2*dy;
    int incrNE = 2*(dy - dx);
    int x = x0;
    int y = y0;
    
    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    glVertex2f(x,y);
    
    while(x < xl){
      if(d <= 0){
	d += incrE;
	x++;
      }
      else{
	d +=incrNE;
	x++;
	y++;
      }
      glVertex2f(x,y);
    } //end while loop
    
    glEnd();
    
  }
  else if(m<0 && m>=-1){
    
    int d = -2*dy - dx;
    int decrE = 2*(-dy - dx);
    int decrSE = -2*dy;
    int x = x0;
    int y = y0;
    
    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    glVertex2f(x,y);
    
    while(x < xl){
      if(d <= 0){
	d+= decrSE;
	x++;
	
      }
      else{
	d += decrE;
	x++;
	y--;
      }
      glVertex2f(x,y);
      
    }
    glEnd();
  }
  else if(m>1){
    
    int d = 2*dx - dy;
    int incrN = 2*dx;  
    int incrNE = 2*(dx - dy);
    int x = x0;
    int y = y0;
    
    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    glVertex2f(x,y);
    
    while(y < yl){
      if(d <= 0){
	d+= incrN;
	y++;
      }
      else{
	d+= incrNE;
	x++;
	y++;
      }
      glVertex2f(x,y);
    }
    glEnd();
  }
  else if(m<-1){
    
    int d = 2*dx + dy;
    int decrS = 2*dx;	   
    int decrSE = 2*(dx + dy);
    int x = x0;
    int y = y0;
    
    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    glVertex2f(x,y);
    
    while(y > yl){
      if(d <= 0){
	d += decrS;
	y--;
      }
      else{
	d+= decrSE;
	x++;
	y--;
      }
      glVertex2f(x,y);
    }
    glEnd();
  }
  
  
  //line drawn at this point
}

/* Handling keyboard inputs */
void Keyboard(unsigned char key, int x, int y)
{
  if(key == 27) exit(0);
  else if(key == 'a' && page < 3) ++page;
  else if(key == 'd' && page > 0) --page;
  
  /* sets booleans according to the page value */
  if(page == 0){
    drawName = true;
    drawFace = false;
    fillFace = false;
  }else if(page == 1){
    drawName = false;
    drawFace = true;
    fillFace = false;
  }else if(page == 2){
    drawName = false;
    drawFace = true;
    fillFace = true;
  }
  
}

/* Display method dependant on current boolean values will add points for
 * the different polygons available
 * /******************************************************************/
 
 void display(void) {
   /* clear the screen to the clear colour */
   glClear(GL_COLOR_BUFFER_BIT);
   
   
   if(drawName == true){
     
     int i,x0,y0,xl,yl;
     for(i = 0; i < 30; i++){
       if(i == 0){
	 
	 x0 = 250;
	 xl = 250;
	 y0 = 250;
	 yl = 225;
       }
       else if(i == 1){
	 x0 = 250;
	 xl = 280;
	 y0 = 225;
	 yl = 225;
       }
       
       else if(i == 2){
	 x0 = 280;
	 xl = 280;
	 y0 = 225;
	 yl = 235;
       }
       else if(i == 3){
	 x0 = 260;
	 xl = 280;
	 y0 = 235;
	 yl = 235;
       }
       else if(i == 4){
	 x0 = 260;
	 xl = 260;
	 y0 = 250;
	 yl = 235;
       }
       else if(i ==5){
	 x0 = 250;
	 xl = 260;
	 y0 = 250;
	 yl = 250;
       }
       else if(i == 6){
	 x0 = 300;
	 xl = 300;
	 y0 = 240;
	 yl = 225;
       }
       else if(i == 7){
	 x0 = 300;
	 xl = 350;
	 y0 = 225;
	 yl = 225;
       }			
       else if(i == 8){
	 x0 = 300;
	 xl = 310;
	 y0 = 240;
	 yl = 240;
       }
       else if(i == 9){
	 x0 = 310;
	 xl = 310;
	 y0 = 240;
	 yl = 230;
       }
       else if(i == 10){
	 x0 = 310;
	 xl = 330;
	 y0 = 230;
	 yl = 230;
       }
       else if(i == 11){
	 x0 = 330;
	 xl = 330;
	 y0 = 230;
	 yl = 240;
       }
       else if(i == 12){
	 x0 = 330;
	 xl = 350;
	 y0 = 240;
	 yl = 240;
       }
       else if(i == 13){
	 x0 = 350;
	 xl = 350;
	 y0 = 240;
	 yl = 225;
       }
       else if(i == 14){
	 x0 = 370;
	 xl = 370;
	 y0 = 240;
	 yl = 225;
       }
       else if(i == 15){
	 x0 = 370;
	 xl = 385;
	 y0 = 225;
	 yl = 225;
       }
       else if(i == 16){
	 x0 = 385;
	 xl = 385;
	 y0 = 225;
	 yl = 240;
       }
       else if(i == 17){
	 x0 = 370;
	 xl = 385;
	 y0 = 240;
	 yl = 240;
       }
       else if(i == 18){
	 x0 = 395;
	 xl = 395;
	 y0 = 250;
	 yl = 235;
       }
       else if(i == 19){
	 x0 = 395;
	 xl = 410;
	 y0 = 235;
	 yl = 235;
       }
       else if(i == 20){
	 x0 = 410;
	 xl = 410;
	 y0 = 235;
	 yl = 230;
       }
       else if(i == 21){
	 x0 = 395;
	 xl = 410;
	 y0 = 230;
	 yl = 230;
       }
       else if(i == 22){
	 x0 = 395;
	 xl = 395;
	 y0 = 230;
	 yl = 225;
       }
       else if(i == 23){
	 x0 = 395;
	 xl = 420;
	 y0 = 225;
	 yl = 225;
       }
       else if(i == 24){
	 x0 = 420;
	 xl = 420;
	 y0 = 225;
	 yl = 240;
       }
       else if(i == 25){
	 x0 = 405;
	 xl = 420;
	 y0 = 240;
	 yl = 240;
       }
       else if(i == 26){
	 x0 = 405;
	 xl = 405;
	 y0 = 240;
	 yl = 245;
       }
       else if(i == 27){
	 x0 = 405;
	 xl = 420;
	 y0 = 245;
	 yl = 245;
       }
       else if(i == 28){
	 x0 = 420;
	 xl = 420;
	 y0 = 245;
	 yl = 250;
       }
       else if(i == 29){
	 x0 = 395;
	 xl = 420;
	 y0 = 250;
	 yl = 250;
       }
       
       Line(x0,y0,xl,yl);
     }
   }
   
   /* Drawing the smiley face will require drawing a 1/8 of a circle and reflecting around the
    *  center.  If the circle needs to be filled we can decrement the radius length
    *  by 1 from 300.
    *  If we're filling the other polygons the method will also call a helper method that will
    *  do the filling for the polygons called FillFace().
    */
   
   if(drawFace == true){
     int rdecr = 1;
     if(fillFace) rdecr = 300;
     
     int j = 0;
     for(j; j < rdecr; j++){
       int r = 300 - j;
       int x = 500;
       int y = x + r;
       int d = 1-r;
       int deltaE = 3;
       int deltaSE = -2 * r + 5;
       
       glBegin(GL_POINTS);
       glColor3f(1.0,0.0,0.0);
       glVertex2f(x,y);
       glVertex2f(y,x);
       glVertex2f(y,(500-x) + 500);
       glVertex2f(x,(800-y) + 200);
       glVertex2f((500-x) + 500,(800-y) +200);
       glVertex2f((800-y) + 200,(500-x) + 500);
       glVertex2f((800-y) + 200,x);
       glVertex2f((500-x) + 500,y);
       while(y > x){
	 if(d<0){
	   d += deltaE;
	   deltaE += 2;
	   deltaSE += 2;
	 }
	 else{
	   d += deltaSE;
	   deltaE += 2;
	   deltaSE += 4;
	   y--;
	 }
	 x++;
	 glVertex2f(x,y);
	 glVertex2f(y,x);
	 glVertex2f(y,(500-x) + 500);
	 glVertex2f(x,(800-y) + 200);
	 glVertex2f((500-x) + 500,(800-y) + 200);
	 glVertex2f((800-y) + 200,(500-x) + 500);
	 glVertex2f((800-y) + 200,x);
	 glVertex2f((500-x) + 500,y);
       }
       glEnd();
     }
     
     int i,x0,y0,xl,yl;
     for(i=0;i<7;i++){
       if(i == 0){
	 x0 = 350;
	 xl = 400;
	 y0 = 400;
	 yl = 300;
       }
       else if(i == 1){
	 x0 = 400;
	 xl = 600;
	 y0 = 300;
	 yl = 300;
       }
       else if(i == 2){
	 x0 = 600;
	 xl = 650;
	 y0 = 300;
	 yl = 400;
       }
       else if(i == 3){
	 x0 = 350;
	 xl = 650;
	 y0 = 400;
	 yl = 400;
       }
       else if(i == 4){
	 x0 = 450;
	 xl = 500;
	 y0 = 450;
	 yl = 550;
       }
       else if(i == 5){
	 x0 = 450;
	 xl = 550;
	 y0 = 450;
	 yl = 450;
       }	
       else if(i == 6){
	 x0 = 500;
	 xl = 550;
	 y0 = 550;
	 yl = 450;
       }
       Line(x0,y0,xl,yl);
       
     }//end of for loop drawing trapezoid and triangle
     
     //start drawing left star reflected across 500,500
     
     for(i = 0; i < 10; i++){
       switch(i){
	 case 0:
	   x0 = 338;
	   y0 = 662;
	   xl = 350;
	   yl = 700;
	   break;
	 case 1:
	   x0 = 298;
	   y0 = 662;
	   xl = 338;
	   yl = 662;
	   break;
	 case 2:
	   x0 = 298;
	   y0 = 662;
	   xl = 331;
	   yl = 639;
	   break;
	 case 3:
	   x0 = 318;
	   y0 = 597;
	   xl = 331;
	   yl = 639;
	   break;
	 case 4:
	   x0 = 318;
	   y0 = 597;
	   xl = 350;
	   yl = 621;
	   break;
	 case 5:
	   x0 = 350;
	   y0 = 621;
	   xl = 382;
	   yl = 597;
	   break;
	 case 6:
	   x0 = 369;
	   y0 = 639;
	   xl = 382;
	   yl = 597;
	   break;
	 case 7:
	   x0 = 369;
	   y0 = 639;
	   xl = 402;
	   yl = 662;
	   break;
	 case 8:
	   x0 = 362;
	   y0 = 662;
	   xl = 402;
	   yl = 662;
	   break;
	 case 9:
	   x0 = 350;
	   y0 = 700;
	   xl = 362;
	   yl = 662;
	   break;
	   
       }
       Line(x0,y0,xl,yl);
       Line(x0+300,y0,xl+300,yl);
       
     }
     if(fillFace)
       paintFace();
     
     }//end of drawFace
     
     /* swap buffers */
     glutSwapBuffers();
     }
     
     
     void paintFace(){
       //sort the buckets(Edge Table) by x coord of ymin.
       int i = 0, j = 0;
       vector<edges> AET;  //initialize empty AET
       
       for(i = 0; i<1000; i++){
	 if(buckets[i].size() == 0) continue;
	 while(j < buckets[i].size()){
	   if(j+1 < buckets[i].size() && buckets[i].at(j).xmin > buckets[i].at(j+1).xmin){
	     edges swap = buckets[i].at(j);
	     buckets[i].at(j) = buckets[i].at(j+1);
	     buckets[i].at(j+1) = swap;
	     if(j != 0) j--;
	     
	   }
	   else{
	     j++;
	   }
	 }
       }
       
       glBegin(GL_POINTS);
       glColor3f(1.0,0.0,1.0);
       
       bool parity;
       i = 0;
       while(buckets[i].size() == 0){
	 i++;
       }
       for(i; i < 1000; i++){
	 if(buckets[i].size() != 0){
	   for(j = 0; j < buckets[i].size(); j++){
	     AET.push_back(buckets[i].at(j));
	   }
	 }
	 buckets[i].clear();
	 
	 int k;
	 for(k=0; k<AET.size(); k++){
	   if(AET.at(k).ymax <= i){
	     AET.erase(AET.begin()+k);
	   }
	 }
	 j = 0;
	 while(j < AET.size()){
	   if(j+1 < AET.size() && AET.at(j).xmin > AET.at(j+1).xmin){
	     edges swap = AET.at(j);
	     AET.at(j) = AET.at(j+1);
	     AET.at(j+1) = swap;
	     if(j != 0) j--;
	   }
	   else{
	     j++;
	   }
	 }
	 
	 parity = false;
	 for(k = 0; k < AET.size(); k++){
	   parity = !parity;
	   if(k+1 < AET.size()){
	     int a = AET.at(k).xmin;
	     int b = AET.at(k+1).xmin;
	     if(AET.at(k).ymax == i)
	       parity = !parity;
	     while(parity && a < b){
	       glVertex2f(a,i);
	       a++;
	     }
	     
	   }
	   
	 }
	 
	 for(k=0; k<AET.size(); k++){
	   AET.at(k).xmin += AET.at(k).invm;
	 }
	 //cout << "size:" << AET.size() << endl;
       }
       
       glEnd();
       
       
     }
     
     void reshape (int w, int h) {
       /* set the viewport */
       glViewport (0, 0, (GLsizei) w, (GLsizei) h);
       
       /* Matrix for projection transformation */
       glMatrixMode (GL_PROJECTION);
       
       /* replaces the current matrix with the identity matrix */
       glLoadIdentity ();
       
       /* Define a 2d orthographic projection matrix */
       glOrtho (0.0, (GLdouble) w, 0.0, (GLdouble) h, -1.0, 0.0);
     }
     
     /*******************************************************************/
     
     int main(int argc, char** argv) {
       
       /* deal with any GLUT command Line options */
       glutInit(&argc, argv);
       //myslope = atof(argv[0]);
       /* create an output window */
       glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
       glutInitWindowSize(1000, 1000);
       
       /* set the name of the window and try to create it */
       glutCreateWindow("Smiley Face");
       
       /* specify clear values for the color buffers */
       glClearColor (0.0, 0.0, 0.0, 1.0);
       
       /* Receive keyboard inputs */
       glutKeyboardFunc (Keyboard);
       
       /* assign the display function */
       glutDisplayFunc(display);
       
       /* assign the idle function */
       glutIdleFunc(display);
       
       /* sets the reshape callback for the current window */
       glutReshapeFunc(reshape);
       
       /* enters the GLUT event processing loop */
       glutMainLoop();
       
       return (EXIT_SUCCESS);
     }
     
     