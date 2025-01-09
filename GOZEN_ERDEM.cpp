
/**************************************************
   CTIS164 - Homework
**************************************************/
/*STUDENT :Erdem Gözen
 NUMBER : 22103098
SECTION :164 - 04
HOMEWORK:1
----------
PROBLEMS:
----------
ADDITIONAL FEATURES: Left mouse click change climate and space bar stop and continue the animation
***/

//I USE MACOS. THUS, I CHANGED vsprintf FUNCTIONS!!

#define GL_SILENCE_DEPRECATION
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <iostream>


#define WINDOW_WIDTH   960
#define WINDOW_HEIGHT 1280
#define PI 3.1415

int carX = -30; // Initial position of the car
int carY = -450;// Initial y position of the car
int carDirection = 1; // 1 for moving right, -1 for moving left
int CarMoving = 1; // Flag to track car movement
int leftWindowVisible = 1; // Flag to track left window visibility
int rightWindowVisible = 1;// Flag to track right window visibility
bool spring = true;
bool color = true;
// To draw a filled circle, centered at (x,y) with radius r
void circle( int x, int y, int r ) {
   float angle ;
   glBegin( GL_POLYGON );
       for ( int i = 0 ; i < 100 ; i++ ) {
          angle = 2*PI*i/100;
          glVertex2f( x+r*cos(angle), y+r*sin(angle)) ;
       }
   glEnd();
}




void drawCar(float xC, float yC, int color)
{
    if(color){
        glColor3ub(255, 0, 0);
    }
    else
        glColor3ub(0, 0, 255);
    glRectf(xC, yC, xC+60, yC+100);
    
    //wheel
    glColor3ub(0, 0, 0);
    glRectf(xC-6, yC+4, xC, yC+25);
    glRectf(xC-6, yC+94, xC, yC+69);
    glRectf(xC+66, yC+94, xC+60, yC+69);
    glRectf(xC+66, yC+4, xC+60, yC+25);
    
    //glass bottom
    glRectf(xC+10, yC+10, xC+50, yC+23);
    //glass top
    glRectf(xC+8, yC+50, xC+52, yC+75);
    
    //lamp
    glColor3f(255, 255, 255);
    circle(xC, yC, 3);
    circle(xC+55, yC+95, 3);
    circle(xC, yC+95, 3);
    circle(xC+55, yC, 3);
    glRectf(xC, yC, xC+5, yC+5);
    glRectf(xC+55, yC+95, xC+60, yC+100);
    glRectf(xC, yC+95, xC+5, yC+100);
    glRectf(xC+55, yC+5, xC+60, yC);
    
    glColor3f(0.6, 0.2, 0.2);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xC+17, yC+80);
    glVertex2f(xC+13, yC+92);
    glEnd();
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xC+40, yC+80);
    glVertex2f(xC+44, yC+92);
    glEnd();

}



void vprint(int x, int y, void *font, const char *string , ...) {
   va_list ap;
   va_start ( ap, string );
   char str[1024] ;
   vsprintf( str, string, ap ) ;
   va_end(ap) ;
   
   int len, i ;
   glRasterPos2f( x, y );
   len = (int) strlen( str );
   for ( i =0; i<len; i++ )
      glutBitmapCharacter( font, str[i]);
}

void vprint2(int x, int y, float size, const char *string, ...) {
   va_list ap;
   va_start(ap, string);
   char str[1024];
   vsprintf(str, string, ap);
   va_end(ap);
   glPushMatrix();
   glTranslatef(x, y, 0);
   glScalef(size, size, 1);
      
   int len, i;
   len = (int)strlen(str);
   for (i = 0; i<len; i++)
      glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
   glPopMatrix();
}

void display()
{
    
    //wall
    glColor3ub(220, 220, 200);
    glRectf(-700, -700, 700, 700);
    
    for(int i=0;i<1400;i+=50){
    glColor3f(0.7, 0.7, 0);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    
    glVertex2f(-700+i, 700);
    glVertex2f(-700+i, -700);
    
    glEnd();
}
    glColor3f(0.9, 0.9, 0.9);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-200, 200);
    glVertex2f(-200, -200);
    glEnd();
    glColor3f(0.9, 0.9, 0.9);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-100, 100);
    glVertex2f(-100, -100);
    glEnd();
    
    //window
    glColor3ub(139, 69, 19);
    glRectf(-450, -525, 450, 525);
    glColor3ub(150, 80, 20);
    glRectf(-400, -500, 400, 500);
    glColor3f(0.4, 0.2, 0.2);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-400, -500);
    glVertex2f(-400, 500);
    glEnd();
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex2f(400, -500);
    glVertex2f(-400, -500);
    glEnd();
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex2f(400, -500);
    glVertex2f(400, 500);
    glEnd();
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-400, 500);
    glVertex2f(400, 500);
    glEnd();
    
    
    if(spring){
        //green
        glColor3ub(0, 155, 0.0);
        glRectf(-350, -475, 350, 475);
        //road
        glColor3ub(75, 75, 70);
        glRectf(-175, -475, 175, 475);
        //strips
        for(int i =50 ; i<900; i+=100){
            glColor3ub(255, 255, 255);
            glRectf(-10, -425+i, 10, -475+i);
            
        }
        //left tree
        glColor3ub(139, 69, 19);
        glRectf(-265, 110, -295, 190);
        glColor3ub(0, 100, 0);
        circle(-280, 250, 30);
        circle(-250, 220, 30);
        circle(-310, 220, 30);
        circle(-280, 190, 30);
        circle(-310, 190, 30);
        circle(-250, 190, 30);
        
        //right bottom tree
        glColor3ub(139, 69, 19);
        glRectf(265, -170, 295, -250);
        glColor3ub(0, 100, 0);
        circle(280, -100, 30);
        circle(250, -130, 30);
        circle(310, -130, 30);
        circle(280, -160, 30);
        circle(310, -160, 30);
        circle(250, -160, 30);
    }
    else{
        glColor3ub(255, 255, 255);
        glRectf(-350, -475, 350, 475);
        glColor3ub(75, 75, 70);
        glRectf(-175, -475, 175, 475);
        //strips
        for(int i =50 ; i<900; i+=100){
            glColor3ub(255, 255, 255);
            glRectf(-10, -425+i, 10, -475+i);
            
        }
        //left tree
        glColor3ub(139, 69, 19);
        glRectf(-265, 110, -295, 190);
        glColor3ub(120, 120, 120);
        circle(-280, 250, 30);
        circle(-250, 220, 30);
        circle(-310, 220, 30);
        circle(-280, 190, 30);
        circle(-310, 190, 30);
        circle(-250, 190, 30);
        
        //right bottom tree
        glColor3ub(139, 69, 19);
        glRectf(265, -170, 295, -250);
        glColor3ub(120, 120, 120);
        circle(280, -100, 30);
        circle(250, -130, 30);
        circle(310, -130, 30);
        circle(280, -160, 30);
        circle(310, -160, 30);
        circle(250, -160, 30);
        
        //snowman
        circle(290, 260, 40);
        circle(290, 190, 50);
        for(int i=0; i<3;i++){
            glColor3ub(0, 0, 0);
            circle(290, 170+i*20, 5);
            
            //snowflake
            glColor3f(0.8, 0.8, 0.8);
            srand(time(NULL));
            for(int i =0; i<100; i++){
                int random = (rand()%700) -350;
                int random1= (rand()%700)-350;
                circle(random, random1, 3);
            }

        }
        
        
        
        glColor3ub(0, 0, 0);
        circle(270, 280, 5);
        circle(310, 280, 5);
        glColor3ub(200, 100, 0);
        glRectf(242, 200, 190, 195);
        glRectf(338, 200, 350, 195);
    }
    //window button
    glColor3ub(220, 220, 200);
    glRectf(325, -5, 375, 5);
    circle(375,0,6);
    drawCar(carX, carY, color);
    
        //bright grey
   glColor3ub(200, 200, 200);
   glRectf(-200, -475, -175, 475);
    
    glColor3ub(200, 200, 200);
    glRectf(175, -475, 200, 475);
    
    glColor3ub(255, 175, 128);
    glRectf(-250, 490, 250, 535);
    
    glColor3ub(0, 0, 0);
    vprint(-350, -350, GLUT_BITMAP_HELVETICA_18, "Left Click : Changing Climate");
    vprint(-350, -330, GLUT_BITMAP_HELVETICA_18, "spacebar : Stop / Continue");
    vprint(-350, -370, GLUT_BITMAP_HELVETICA_18, "esc : End");
    
    //TABLE
    glColor3ub(255, 255, 0);
    vprint(-55, 515, GLUT_BITMAP_HELVETICA_18, "2D Car Driving");
    vprint(-140, 495, GLUT_BITMAP_HELVETICA_18, "View Through a Window by Erdem Gozen");
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-250, 535);
    glVertex2f(0, 565);
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP);
    glVertex2f(250, 535);
    glVertex2f(0, 565);
    glEnd();
    circle(0, 565, 8);
    
    
    
    
    glutSwapBuffers();
    
}

void carAnimation(int value) {
    if (CarMoving) {
        if(CarMoving)
            carY += carDirection *5;
        
        if(carY>475)
            carY = -475;
        else if(carY <-475)
            carY = 475;
    }

    glutPostRedisplay();
    glutTimerFunc(20, carAnimation, 0); // speed of the car
}

void onKeyDown(unsigned char key, int x, int y) {
    // Exit when ESC is pressed
    if (key == 27)
        exit(0);
    if(key == 32)
        CarMoving = !CarMoving;
    
    
    // To refresh the window it calls display() function
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        leftWindowVisible = !leftWindowVisible;// left window visibility
        spring=!spring;//winter-spring
        color=!color;//red-blue car
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        rightWindowVisible = !rightWindowVisible; //right window visibility
    }

    glutPostRedisplay();
}

void onResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Erdem Gozen 2D Car Animation");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);
    glutKeyboardFunc(onKeyDown);
    glutMouseFunc(mouse); // Mouse function to control window
    glutTimerFunc(20, carAnimation, 0);

    glutMainLoop();
    return 0;
}
