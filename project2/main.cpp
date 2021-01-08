//first we include libraries
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<windows.h>
#include<math.h>
//#include<graphics.h>

int flag= 1;
int translateX=0,translateY=0;
void display();
void reshape(int w, int h);
void texture (void);
void init(){ glClearColor(1,1,1,0); }
void idleFunc();
float xRotated = 90.0, yRotated = 0.0, zRotated = 0.0;
void timer(int);
//void OnMouseClick(int button, int state, int x, int y)
//{
//  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//  {
//     //store the x,y value where the click happened
//    translateX--;
//  }
//}

//void keyboard(unsigned char Key, int x, int y){
//
//    switch(Key){
//        case 'd' : translateX++;
//        break;
//
//        case 'a' : translateX--;
//        break;
//
//        case 'w' : translateY++;
//        break;
//
//        case 's' : translateY--;
//        break;
//
//        case 'f' : glutFullScreen();
//        break;
//
//        case 27 : exit(0);
//        break;
//    }
//}
void triangle(){
    glPushMatrix();
    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
      // Front
   // glPushMatrix();
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( -3.0f, -2.0f, -3.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(-4.0f, -4.0f, -2.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-2.0f, -4.0f, -2.0f);

      // Right
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(-3.0f, -2.0f, -3.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-2.0f, -4.0f, -2.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(-2.0f, -4.0f, -4.0f);


        glEnd();   // Done drawing the pyramid
       glPopMatrix();

       }

void cube(){

    glColor3f(1,1,0);
    glPushMatrix();
//    glTranslated(-153,-3,-50);
//    glRotatef(190,2,2,0);
    glutSolidCube(0.5);
    glPopMatrix();
}
void sphere(){
            glPushMatrix();

            glColor3f(1,0,0);
            glutSolidSphere(2,20,20);
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
//    glutKeyboardFunc(keyboard);
//    glutMouseFunc(OnMouseClick);
    glutTimerFunc(1000,timer,0); // function will wait time given, then runs the function we pointing to
     // setting back ground color;
    glutIdleFunc(idleFunc);

    glClearColor(1,1,1,1);
    texture(); // function controlling light etc...
    glutMainLoop();//looping main to update changes


}

    void display(){

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // buffer saves color on screen / the glclear clears cashe from previous displays
        glLoadIdentity(); // resets coordination / replace current matrix with I matrix // for example when using glTranslate or glRotate
        //(translating matrix current position not from origin so glLoadIdentity to start from origin
        glTranslatef(0.0,0.0,-15.0);
        glRotatef(10,1,1,0);
//         glColor3f(1,0,1);
//            glBegin(GL_POLYGON);
//            glVertex2f(5+translateX,-5+translateY);
//            glVertex2f(5+translateX,-8+translateY);
//            glVertex2f(2+translateX,-8+translateY);
//            glVertex2f(2+translateX,-5+translateY);
//            glEnd();
//



      //  sphere();
       // triangle();
        //cube();

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

   // Render a pyramid consists of 4 triangles
   glLoadIdentity();                  // Reset the model-view matrix
   glTranslatef(-1.5f, 0.0f, -6.0f);  // Move left and into the screen

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

           // glFlush();

          glutSwapBuffers();
    }
void idleFunc (void)
{
   // zRotated += 1;
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

    void timer(int ){
        glutPostRedisplay();// function that is responsible to run display function again // display function will run again after first time and then swap buffers displaying new drawing position
        glutTimerFunc(1000/60,timer,0); // Recursion to keep looping to keep animation going // (time in second / number of frames , timer , 0)


        glutPostRedisplay();
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
