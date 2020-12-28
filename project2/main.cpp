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

void init(){ glClearColor(0.529, 0.808, 0.922, 0); }

void timer(int);
void OnMouseClick(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
     //store the x,y value where the click happened
    translateX--;
  }
}

void keyboard(unsigned char Key, int x, int y){

    switch(Key){
        case 'd' : translateX++;
        break;

        case 'a' : translateX--;
        break;

        case 'w' : translateY++;
        break;

        case 's' : translateY--;
        break;

        case 'f' : glutFullScreen();
        break;

        case 27 : exit(0);
        break;
    }
}

int main(int argc, char**argv){

    glutInit(&argc , argv); // initialize glut
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);// display mode / goint to use rgb colors / and going to use double buffer for animation
    //initialize window
    glutInitWindowPosition(200,0);
    glutInitWindowSize(1200,800);
    //function that creates window
    glutCreateWindow("18100322/18101712"); // takes initialization and creates window
    init();


    //function that displays my display function // function that reshapes with my reshape function
    glutDisplayFunc(display); // the parameter is my display function which is initialized before main
    glutReshapeFunc(reshape); // the parameters are my reshape function
    glutKeyboardFunc(keyboard);
    glutMouseFunc(OnMouseClick);
    glutTimerFunc(1000,timer,0); // function will wait time given, then runs the function we pointing to
     // setting back ground color;

    glutMainLoop();//looping main to update changes


}

    void display(){

        glClear(GL_COLOR_BUFFER_BIT); // buffer saves color on screen / the glclear clears cashe from previous displays
        glLoadIdentity(); // resets coordination / replace current matrix with I matrix // for example when using glTranslate or glRotate
        //(translating matrix current position not from origin so glLoadIdentity to start from origin

         glColor3f(1,0,1);
            glBegin(GL_POLYGON);
            glVertex2f(5+translateX,-5+translateY);
            glVertex2f(5+translateX,-8+translateY);
            glVertex2f(2+translateX,-8+translateY);
            glVertex2f(2+translateX,-5+translateY);
            glEnd();


    glFlush();

          glutSwapBuffers();
    }

    void reshape(int w, int h){
        glViewport(0,0,(GLsizei)w , (GLsizei)h) ;// el makan el b3red meno el shasha bt3ti

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity(); // i need to reset matrix after resize since it differs
        gluOrtho2D(-20,20,-20,20);
        glMatrixMode(GL_MODELVIEW);

    }

    void timer(int ){
        glutPostRedisplay();// function that is responsible to run display function again // display function will run again after first time and then swap buffers displaying new drawing position
        glutTimerFunc(1000/60,timer,0); // Recursion to keep looping to keep animation going // (time in second / number of frames , timer , 0)


        glutPostRedisplay();
    }

