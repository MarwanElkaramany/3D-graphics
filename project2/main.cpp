//first we include libraries
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<windows.h>
#include<math.h>
//#include<graphics.h>
static int slices = 16;
static int stacks = 16;
static int useFog = 0;
float moonx=0,moony=0;
float sunx=0,suny=0;
float boatx;
float cloudsx=0;
int COLOR=0;
int direction=1;
float red=0.412,green=0.412,blue=0.412,alpha;
//int flag= 1;
int sunflag = 1;
double anglesun;
int moonflag=1;
int boatflag =1;
float angle=0;
void tree(float i,float j);
void mount(float x,float y,float z , float w);
void boat(float boatx);
void sun(float sunx,float suny);
void moon(float moonx, float moony);
float x=0;
double cubesize = 0;
int flag= 1;
int rotatee=0;
int translateX=0,translateY=5;
int translateY2=-4;
void display();
double ssize = 2;
double scale;
void reshape(int w, int h);
void texture (void);
void init(){ glClearColor(0.529, 0.808, 0.922, 0); }
void idleFunc();
float xRotated = 90.0, yRotated = 0.0, zRotated = 0.0;
void timer(int);
GLfloat anglePyramid = 0.0f;  // Rotational angle for pyramid
GLfloat angleCube = 0.0f;     // Rotational angle for cube
int refreshMills = 15;        // refresh interval in milliseconds

//void OnMouseClick(int button, int state, int x, int y)
//{
//  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//  {
//     //store the x,y value where the click happened
//    translateX--;
//  }
//}

void keyboard(unsigned char Key, int x, int y){

    switch(Key){
    case 'w' :if(translateY2<-3)
                    translateY2++;


        break;

        case 's' :if(translateY2>-4)
                       translateY2--;


        break;
 case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;

        case 'F' : glutFullScreen();
        break;

        case 'f' : {
            useFog = !useFog;
            useFog ? glEnable(GL_FOG) : glDisable(GL_FOG);
            glutPostRedisplay();
            }
        break;

        case 'r' :
                    if(rotatee==1)
                    rotatee=0;
                    else
                        rotatee=1;
        break;

        case 27 : exit(0);
        break;
    }
}
void triangle(float x, float y){
    glLoadIdentity();                  // Reset the model-view matrix
    glTranslatef(x, y, -20.0f);  // Move left and into the screen
    glRotatef(anglePyramid, 0.0f, 1.0f, 0.0f);  // Rotate about the (1,1,0)-axis
    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
      // Front
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(1.0f, -1.0f, 1.0f);

      // Right
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(1.0f, -1.0f, 1.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(1.0f, -1.0f, -1.0f);

      // Back
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(1.0f, -1.0f, -1.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-1.0f, -1.0f, -1.0f);

      // Left
      glColor3f(1.0f,0.0f,0.0f);       // Red
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f,0.0f,1.0f);       // Blue
      glVertex3f(-1.0f,-1.0f,-1.0f);
      glColor3f(0.0f,1.0f,0.0f);       // Green
      glVertex3f(-1.0f,-1.0f, 1.0f);
        glEnd();   // Done drawing the pyramid


       }

void cube(){
        glLoadIdentity();
        glTranslatef(1.5f, 0.0f, -15.0f);
        glRotatef(angleCube, 1.0f, 1.0f, 1.0f);  // Rotate about (1,1,1)-axis

            glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
          // Top face (y = 1.0f)
          // Define vertices in counter-clockwise (CCW) order with normal pointing out

          glColor3f(0.0f, 1.0f, 0.0f);     // Green
          glVertex3f( 1.0f, 1.0f, -1.0f);
          glVertex3f(-1.0f, 1.0f, -1.0f);
          glVertex3f(-1.0f, 1.0f,  1.0f);
          glVertex3f( 1.0f, 1.0f,  1.0f);

          // Bottom face (y = -1.0f)
          glColor3f(1.0f, 0.5f, 0.0f);     // Orange
          glVertex3f( 1.0f, -1.0f,  1.0f);
          glVertex3f(-1.0f, -1.0f,  1.0f);
          glVertex3f(-1.0f, -1.0f, -1.0f);
          glVertex3f( 1.0f, -1.0f, -1.0f);

          // Front face  (z = 1.0f)
          glColor3f(1.0f, 0.0f, 0.0f);     // Red
          glVertex3f( 1.0f,  1.0f, 1.0f);
          glVertex3f(-1.0f,  1.0f, 1.0f);
          glVertex3f(-1.0f, -1.0f, 1.0f);
          glVertex3f( 1.0f, -1.0f, 1.0f);

          // Back face (z = -1.0f)
          glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
          glVertex3f( 1.0f, -1.0f, -1.0f);
          glVertex3f(-1.0f, -1.0f, -1.0f);
          glVertex3f(-1.0f,  1.0f, -1.0f);
          glVertex3f( 1.0f,  1.0f, -1.0f);

          // Left face (x = -1.0f)
          glColor3f(0.0f, 0.0f, 1.0f);     // Blue
          glVertex3f(-1.0f,  1.0f,  1.0f);
          glVertex3f(-1.0f,  1.0f, -1.0f);
          glVertex3f(-1.0f, -1.0f, -1.0f);
          glVertex3f(-1.0f, -1.0f,  1.0f);

          // Right face (x = 1.0f)
          glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
          glVertex3f(1.0f,  1.0f, -1.0f);
          glVertex3f(1.0f,  1.0f,  1.0f);
          glVertex3f(1.0f, -1.0f,  1.0f);
          glVertex3f(1.0f, -1.0f, -1.0f);
            glEnd();  // End of drawing color-cube

}
void sphere(){
            glLoadIdentity();
            glPushMatrix();
            glTranslatef(-3.0f, -3.0, -20.0f);  // Move left and into the screen
           // glRotatef(0, 0.0f, 1.0f, 0.0f);  // Rotate about the (1,1,0)-axis
//            glTranslatef(4.0f, 10.0f, -15.0f);
//            glRotatef(angleCube, 1.0f, 1.0f, 1.0f);
            glColor3f(1,0,0);
            glutSolidSphere(2,20,20);
            glPopMatrix();
}
void tree(int x,int y,int z){
glLoadIdentity();

   glPushMatrix();
   glColor3f(0.133, 0.545, 0.133);
    glTranslated(-4.35+x,-1.7+4.5+y,-20+z);
    glRotated(-90,1,0,0);
    glutSolidCone(0.7,1,slices,stacks);
    glPopMatrix();
 glLoadIdentity();

    glPushMatrix();
   glColor3f(0.133, 0.545, 0.133);
    glTranslated(-4.35+x,-1.7+4+y,-20+z);
    glRotated(-90,1,0,0);
    glutSolidCone(0.9,1,slices,stacks);
    glPopMatrix();
 glLoadIdentity();
    glPushMatrix();
    glColor3f(0.133, 0.545, 0.133);
    glTranslated(-4.35+x,-2.2+4+y,-20+z);
    glRotated(-90,1,0,0);
    glutSolidCone(1.2,1,slices,stacks);
    glPopMatrix();
 glLoadIdentity();
    glColor3f(0.3,0,0);
    glPushMatrix();
    //glColor3f(0.133, 0.545, 0.133);
    glTranslated(-4.35+x,-3+4+y,-20+z);
    glRotated(-90,1,0,0);
    glutSolidCone(0.5,2,slices,stacks);
    glPopMatrix();
        glPopMatrix();
}
int main(int argc, char**argv){

    glutInit(&argc , argv); // initialize glut
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE |GLUT_DEPTH);// display mode / goint to use rgb colors / and going to use double buffer for animation
    //initialize window
    glutInitWindowPosition(700,200);
    glutInitWindowSize(800,700);
    //function that creates window
    glutCreateWindow("18100322/18101712"); // takes initialization and creates window
    init();


    //function that displays my display function // function that reshapes with my reshape function
    glutDisplayFunc(display); // the parameter is my display function which is initialized before main
    glutReshapeFunc(reshape); // the parameters are my reshape function
    glutKeyboardFunc(keyboard);
//    glutMouseFunc(OnMouseClick);
   // glutTimerFunc(1000,timer,0); // function will wait time given, then runs the function we pointing to
     // setting back ground color;
    glutIdleFunc(idleFunc);
    glutTimerFunc(0, timer, 0);     // First timer call immediately
    glClearColor(0.529, 0.808, 0.922, 0);
          texture(); // function controlling light etc...
    glutMainLoop();//looping main to update changes


}
    void display(){

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // buffer saves color on screen / the glclear clears cashe from previous displays

             glLoadIdentity();
             glPushMatrix();
             glScalef(cubesize,cubesize,1);
        glTranslatef(0, 0.0f, -15.0f);
        glRotatef(angleCube, 1.0f, 1.0f, 1.0f);  // Rotate about (1,1,1)-axis

            glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
          // Top face (y = 1.0f)
          // Define vertices in counter-clockwise (CCW) order with normal pointing out

          glColor3f(0.0f, 1.0f, 0.0f);     // Green
          glVertex3f( 1.0f, 1.0f, -1.0f);
          glVertex3f(-1.0f, 1.0f, -1.0f);
          glVertex3f(-1.0f, 1.0f,  1.0f);
          glVertex3f( 1.0f, 1.0f,  1.0f);

          // Bottom face (y = -1.0f)
          glColor3f(1.0f, 0.5f, 0.0f);     // Orange
          glVertex3f( 1.0f, -1.0f,  1.0f);
          glVertex3f(-1.0f, -1.0f,  1.0f);
          glVertex3f(-1.0f, -1.0f, -1.0f);
          glVertex3f( 1.0f, -1.0f, -1.0f);

          // Front face  (z = 1.0f)
          glColor3f(1.0f, 0.0f, 0.0f);     // Red
          glVertex3f( 1.0f,  1.0f, 1.0f);
          glVertex3f(-1.0f,  1.0f, 1.0f);
          glVertex3f(-1.0f, -1.0f, 1.0f);
          glVertex3f( 1.0f, -1.0f, 1.0f);

          // Back face (z = -1.0f)
          glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
          glVertex3f( 1.0f, -1.0f, -1.0f);
          glVertex3f(-1.0f, -1.0f, -1.0f);
          glVertex3f(-1.0f,  1.0f, -1.0f);
          glVertex3f( 1.0f,  1.0f, -1.0f);

          // Left face (x = -1.0f)
          glColor3f(0.0f, 0.0f, 1.0f);     // Blue
          glVertex3f(-1.0f,  1.0f,  1.0f);
          glVertex3f(-1.0f,  1.0f, -1.0f);
          glVertex3f(-1.0f, -1.0f, -1.0f);
          glVertex3f(-1.0f, -1.0f,  1.0f);

          // Right face (x = 1.0f)
          glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
          glVertex3f(1.0f,  1.0f, -1.0f);
          glVertex3f(1.0f,  1.0f,  1.0f);
          glVertex3f(1.0f, -1.0f,  1.0f);
          glVertex3f(1.0f, -1.0f, -1.0f);
            glEnd();  // End of drawing color-cube
            glPushMatrix();
////////////////////////////////////////////////////////////////////////////////
    glLoadIdentity();
    glPushMatrix();
    glScalef(scale,scale,1);                 // Reset the model-view matrix
    glTranslatef(yRotated, 1, -20.0f);  // Move left and into the screen
    glRotatef(anglePyramid, 0.0f, 1.0f, 0.0f);  // Rotate about the (1,1,0)-axis
    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
      // Front
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(1.0f, -1.0f, 1.0f);

      // Right
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(1.0f, -1.0f, 1.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(1.0f, -1.0f, -1.0f);

      // Back
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(1.0f, -1.0f, -1.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-1.0f, -1.0f, -1.0f);

      // Left
      glColor3f(1.0f,0.0f,0.0f);       // Red
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f,0.0f,1.0f);       // Blue
      glVertex3f(-1.0f,-1.0f,-1.0f);
      glColor3f(0.0f,1.0f,0.0f);       // Green
      glVertex3f(-1.0f,-1.0f, 1.0f);
        glEnd();   // Done drawing the pyramid
    glPushMatrix();

///////////////////////////////////////////////////////////////////////////////////////////////////
//sun
            glLoadIdentity();

            glPushMatrix();
            glColor3f(1.000, 0.647, 0.000);
            glTranslatef(-7.0, 6.0f, -20.0f);
            glRotatef(anglePyramid,1,1,1);
          //glScalef(2,2,2);

           //glTranslatef(-5.0, 5.0f, -20.0f);
            glutSolidSphere(1,20,20);

            glPopMatrix();
//////////////////////////////////////////////////////////////////////////////////////////////////

            glLoadIdentity();
            glPushMatrix();  // Flat Blue Box


            glTranslatef(0.0, translateY2, -20.0f);
            //  rotate around center
            glRotatef(20.0, 1.0, 0.0, 0.0);
            glScalef(7, 1.1, 5.5); //Make the object bigger
            glColor3f(0.4, 0.5, 1.0); //change the color of the object

            glutSolidCube(2.0); // draw Flat Blue Box

            glPopMatrix();
////////////////////////////////////////////////////////////////////////////////
        glLoadIdentity();
            glPushMatrix();  // Flat Blue Box

            glTranslatef(0.0, translateY2+4, -20.0f);
            //  rotate around center
            glRotatef(40.0, 1.0, 0.0, 0.0);
            glScalef(7, 0.6, 3); //Make the object bigger
            glColor3f(0.000, 0.392, 0.000); //change the color of the object

            glutSolidCube(3.0); // draw Flat Blue Box

            glPopMatrix();
/////////////////////////////////////////////////////////////////////////////////////
   glLoadIdentity();
    tree(0,0,0);
    tree(4,-2,6);
    tree(-1,-1,5);
//    tree(4,0);
//    tree(-2,1);
//    tree(-2,-2);
//    tree(6,0);
//    tree(7,1);
        /////////////////////////////////////////////////


    glLoadIdentity();//clowd
        glColor3d(1,1,1);
        glPushMatrix();
        glTranslated(3.4+x,6,-20);
        glRotated(60,1,0,0);
        glutSolidSphere(.4,20,20);
        glPopMatrix();
        glColor3d(1,1,1);
        glPushMatrix();
        glTranslated(3.2+x,5.9,-20.1);
        glRotated(60,1,0,0);
        glutSolidSphere(.4,20,20);
        glPopMatrix();
        glColor3d(1,1,1);
        glPushMatrix();
        glTranslated(3.2+x,6.1,-19.9);
        glRotated(60,1,0,0);
        glutSolidSphere(.4,20,20);
        glPopMatrix();
        glColor3d(1,1,1);
        glPushMatrix();
        glTranslated(3+x,6,-20);
        glRotated(60,1,0,0);
        glutSolidSphere(.4,20,20);
        glPopMatrix();


        /////////////////////////////////////////////////////
        //house

            glLoadIdentity();
            glPushMatrix();  // building

            glTranslatef(3, 1, -17.0f);
            //  rotate around center
            glRotatef(-35.0, -0.4, 1.0, 0.1);

            glScalef(0.8, 0.8, 0.8); //Make the object bigger
            glColor3f(1,0,1); //change the color of the object

            glutSolidCube(3.0); // draw Flat Blue Box

            glPopMatrix();

            glPushMatrix();  // window r

            glTranslatef(3, 1.2, -15.5f);
            //  rotate around center
            glRotatef(-35.0, -0.4, 1.0, 0.1);

            glScalef(0.8, 0.8, 0.8); //Make the object bigger
            glColor3f(0,0,0); //change the color of the object

            glutSolidCube(0.8); // draw Flat Blue Box

            glPopMatrix();

            glPushMatrix();  // window l

            glTranslatef(1.8, 1.4, -16.4f);
            //  rotate around center
            glRotatef(-35.0, -0.4, 1.0, 0.1);

            glScalef(0.8, 0.8, 0.8); //Make the object bigger
            glColor3f(0,0,0); //change the color of the object

            glutSolidCube(0.8); // draw Flat Blue Box

            glPopMatrix();

            glPushMatrix();  // door

            glTranslatef(2.4, 0.3, -16.4f);
            //  rotate around center
            glRotatef(-35.0, -0.4, 1.0, 0.1);

            glScalef(0.8, 1.5, 0.8); //Make the object bigger
            glColor3f(0,0,0); //change the color of the object

            glutSolidCube(0.8); // draw Flat Blue Box

            glPopMatrix();

//////////////////////////////////////////////////////////////////////////////////
               glLoadIdentity();
               glPushMatrix();                  // Reset the model-view matrix


    glTranslatef(3, 3.1, -17.0f);  // Move left and into the screen

    glRotatef(-35.0, -0.4, 1.0, 0.1);  // Rotate about the (1,1,0)-axis
    glScalef(1.5,0.9,2);
    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
      // Front
                glColor3f(1.0f, 0.0f, 0.0f);     // Red

      glVertex3f( 0.0f, 1.0f, 0.0f);
                glColor3f(1.0f, 0.0f, 0.0f);     // Red

      glVertex3f(-1.0f, -1.0f, 1.0f);
                glColor3f(1.0f, 0.0f, 0.0f);     // Red

      glVertex3f(1.0f, -1.0f, 1.0f);

      // Right
                glColor3f(1.0f, 0.0f, 0.0f);     // Red

      glVertex3f(0.0f, 1.0f, 0.0f);
                glColor3f(1.0f, 0.0f, 0.0f);     // Red

      glVertex3f(1.0f, -1.0f, 1.0f);
                glColor3f(1.0f, 0.0f, 0.0f);     // Red

      glVertex3f(1.0f, -1.0f, -1.0f);

      // Back
                glColor3f(1.0f, 0.0f, 0.0f);     // Red

      glVertex3f(0.0f, 1.0f, 0.0f);
                glColor3f(1.0f, 0.0f, 0.0f);     // Red

      glVertex3f(1.0f, -1.0f, -1.0f);
                glColor3f(1.0f, 0.0f, 0.0f);     // Red

      glVertex3f(-1.0f, -1.0f, -1.0f);

      // Left
                glColor3f(1.0f, 0.0f, 0.0f);     // Red

      glVertex3f( 0.0f, 1.0f, 0.0f);
                glColor3f(1.0f, 0.0f, 0.0f);     // Red

      glVertex3f(-1.0f,-1.0f,-1.0f);
                glColor3f(1.0f, 0.0f, 0.0f);     // Red

      glVertex3f(-1.0f,-1.0f, 1.0f);
        glEnd();   // Done drawing the pyramid
        glPushMatrix();

//            glPushMatrix();
//            glTranslatef(0.0, -3.0, -20.0f);
//            glRecti(0,5,-5,10);
//            glPopMatrix();
//        glLoadIdentity();
//        glTranslated(-13,0,-45);
//        glRotatef(40,1,1,0);
//
//        drawgrid();

       // glLoadIdentity(); // resets coordination / replace current matrix with I matrix // for example when using glTranslate or glRotate
        //(translating matrix current position not from origin so glLoadIdentity to start from origin
       // glTranslatef(0.0,0.0,-15.0);
        //glRotatef(10,1,1,0);
//         glColor3f(1,0,1);
//            glBegin(GL_POLYGON);
//            glVertex2f(5+translateX,-5+translateY);
//            glVertex2f(5+translateX,-8+translateY);
//            glVertex2f(2+translateX,-8+translateY);
//            glVertex2f(2+translateX,-5+translateY);
//            glEnd();
// glLoadIdentity();

//        cube();
//       // sphere();
//    // Render a pyramid consists of 4 triangles
//        triangle(-5.5,0);
//        triangle(-3.5,0.5);
//        triangle(-1.5,1);


//        glLoadIdentity();
//         glTranslatef(-1.0f, -4.0f, -15.0f);
//        glRotatef(angleCube, 1.0f, 1.0f, 1.0f);
//        //glColor3f(1,0,0);
//        glutWireTeapot(1);
//
//            glPushMatrix();
//            glLoadIdentity();
//            glTranslatef(-1.5f, -3.0, -15.0f);  // Move left and into the screen
//            glColor3f(1,0,0);
//            glutSolidSphere(2,20,20);
//            glPopMatrix();
            // glFlush();

          glutSwapBuffers();

    // Update the rotational angle after each refresh [NEW]
    if(rotatee){
        anglesun+=0.05;
    }
  if(rotatee)
   anglePyramid += 0.1f;
   if(rotatee)
   angleCube -= 0.05f;
    }
    void idleFunc (void)
    {
       // zRotated += 1;
        glutPostRedisplay();
    }
    void timer(int ){
        glutPostRedisplay();// function that is responsible to run display function again // display function will run again after first time and then swap buffers displaying new drawing position
       // glutTimerFunc(1000/60,timer,0); // Recursion to keep looping to keep animation going // (time in second / number of frames , timer , 0)
        if(COLOR==1)COLOR=0;
    else COLOR=1;
     Sleep(500);
    glutPostRedisplay();
    x+=0.1*direction;
    if(x>=5)
        direction=-1;
    else if (x<=-8)direction=1;
        glutTimerFunc(refreshMills, timer, 0);
        glutPostRedisplay();
    }

    void reshape(int w, int h){
        glViewport(0,0,(GLsizei)w , (GLsizei)h) ;// el makan el b3red meno el shasha bt3ti

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity(); // i need to reset matrix after resize since it differs
       // gluOrtho2D(-20,20,-20,20);
       gluPerspective(40.0,(GLdouble)w/(GLdouble)h,0.5,20.0);
        glMatrixMode(GL_MODELVIEW);

    }


     void texture (void){

        const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
        const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
        const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

        const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
        const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
        const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
        const GLfloat high_shininess[] = { 100.0f };

            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);

            glEnable(GL_LIGHT0);
            glEnable(GL_NORMALIZE);
            glEnable(GL_COLOR_MATERIAL);
            glEnable(GL_LIGHTING);

            glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
            glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
            glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
            glLightfv(GL_LIGHT0, GL_POSITION, light_position);

            glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
        }


