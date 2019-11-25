#include <bits/stdc++.h>
#include <windows.h>
#include "glut.h"
using namespace std;

#define pi (2*acos(0.0))

double cameraAngle,cameraHeight , angle , max_len , len , slices, stacks;

int drawgrid , drawaxes;

struct point
{
	double x, y, z;
};

struct point p, l, r, u;

struct point add(struct point a, struct point b)
{
	struct point ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;

	return ret;
}

struct point sub(struct point a, struct point b)
{
	struct point ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;

	return ret;
}

struct point rotate(struct point vec, struct point ref, double sign)
{
	struct point n, ret;
	double angle = 0.05 * sign;

	n.x = ref.y*vec.z - ref.z*vec.y;
	n.y = ref.z*vec.x - ref.x*vec.z;
	n.z = ref.x*vec.y - ref.y*vec.x;

	ret.x = vec.x * cos(angle) + n.x * sin(angle);
	ret.y = vec.y * cos(angle) + n.y * sin(angle);
	ret.z = vec.z * cos(angle) + n.z * sin(angle);

	return ret;
}

void drawAxes()
{
	if (drawaxes == 1)
	{
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINES); {
			glVertex3f(100, 0, 0);
			glVertex3f(-100, 0, 0);

			glVertex3f(0, -100, 0);
			glVertex3f(0, 100, 0);

			glVertex3f(0, 0, 100);
			glVertex3f(0, 0, -100);
		}glEnd();
	}
}


void drawGrid()
{
	int i;
	if (drawgrid == 1)
	{
		glColor3f(0.6, 0.6, 0.6);	//grey
		glBegin(GL_LINES); {
			for (i = -8; i <= 8; i++) {

				if (i == 0)
					continue;	//SKIP the MAIN axes

								//lines parallel to Y-axis
				glVertex3f(i * 10, -90, 0);
				glVertex3f(i * 10, 90, 0);

				//lines parallel to X-axis
				glVertex3f(-90, i * 10, 0);
				glVertex3f(90, i * 10, 0);
			}
		}glEnd();
	}
}

void drawSquare(double a)
{
	//glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS); {
		glVertex3f(a, a, 0);
		glVertex3f(a, -a, 0);
		glVertex3f(-a, -a, 0);
		glVertex3f(-a, a, 0);
	}glEnd();
}

void Draw_1_8_OfSphere(double radius)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*pi/2);
			points[i][j].y=r*sin(((double)j/(double)slices)*pi/2);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
       // glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
       glColor3f(1,0,0);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{

			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere

			}glEnd();
		}
	}
}

void DrawSphere()
{
	double d = len , r = max_len - len ;

	glPushMatrix();
	{
		glTranslatef(d, d, d);
		Draw_1_8_OfSphere(r);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-d, d, d);
		glRotated(90, 0, 0, 1);
		Draw_1_8_OfSphere(r);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-d, -d, d);
		glRotated(180, 0, 0, 1);
		Draw_1_8_OfSphere(r);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(d, -d, d);
		glRotated(-90, 0, 0, 1);
		Draw_1_8_OfSphere(r);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(d, d, -d);
		glRotated(180, 1, 1, 0);
		Draw_1_8_OfSphere(r);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-d, d, -d);
		glRotated(90, 0, 0, 1);
		glRotated(180, 1, 1, 0);
		Draw_1_8_OfSphere(r);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-d, -d, -d);
		glRotated(180, 0, 0, 1);
		glRotated(180, 1, 1, 0);
		Draw_1_8_OfSphere(r);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(d, -d, -d);
		glRotated(-90, 0, 0, 1);
		glRotated(180, 1, 1, 0);
		Draw_1_8_OfSphere(r);
	}
	glPopMatrix();

}

void draw6Squares()
{
	glColor3f(1, 1, 1);

    glPushMatrix();
	{
        glTranslated(0, 0, max_len);
        drawSquare(len);
	}
    glPopMatrix();

    glPushMatrix();
	{
        glTranslated(0, 0, -max_len);
        drawSquare(len);
	}
    glPopMatrix();

    glPushMatrix();
	{
        glRotated(90, 1, 0, 0);
        glTranslated(0, 0, max_len);
        drawSquare(len);
	}
    glPopMatrix();

    glPushMatrix();
	{
        glRotated(-90, 1, 0, 0);
        glTranslated(0, 0, max_len);
        drawSquare(len);
	}
    glPopMatrix();


	glPushMatrix();
	{
        glRotated(90, 0, 1, 0);
        glTranslated(0, 0, max_len);
        drawSquare(len);
	}
    glPopMatrix();

	glPushMatrix();
	{
        glRotated(-90, 0, 1, 0);
        glTranslated(0, 0, max_len);
        drawSquare(len);
	}
	glPopMatrix();
}

void drawOneFourthCylinder(double radius, double height)
{
	struct point points[100][100];
	int i, j;
	double h, r;
	//generate points
	for (i = 0; i <= stacks; i++)
	{
		h = height * sin(((double)i / (double)stacks)*(pi / 2));
		//r=radius*cos(((double)i/(double)stacks)*(pi/2));
		//h = height;
		r = radius;
		for (j = 0; j <= slices; j++)
		{
			points[i][j].x = r * cos(((double)j / (double)slices)*.5*pi);
			points[i][j].y = r * sin(((double)j / (double)slices)*.5*pi);
			points[i][j].z = h;
		}
	}
	//draw quads using generated points
	for (i = 0; i<stacks; i++)
	{
		glColor3f(0, 1, 0);
		for (j = 0; j<slices; j++)
		{
			glBegin(GL_QUADS); {
				//upper hemisphere
				glVertex3f(points[i][j].x, points[i][j].y, points[i][j].z);
				glVertex3f(points[i][j + 1].x, points[i][j + 1].y, points[i][j + 1].z);
				glVertex3f(points[i + 1][j + 1].x, points[i + 1][j + 1].y, points[i + 1][j + 1].z);
				glVertex3f(points[i + 1][j].x, points[i + 1][j].y, points[i + 1][j].z);
				//lower hemisphere
				glVertex3f(points[i][j].x, points[i][j].y, -points[i][j].z);
				glVertex3f(points[i][j + 1].x, points[i][j + 1].y, -points[i][j + 1].z);
				glVertex3f(points[i + 1][j + 1].x, points[i + 1][j + 1].y, -points[i + 1][j + 1].z);
				glVertex3f(points[i + 1][j].x, points[i + 1][j].y, -points[i + 1][j].z);
			}glEnd();
		}
	}

}


void draw12Cylinders()
{
	double r = max_len - len;

    ///back right
	glPushMatrix();
	{
		glTranslatef(-len, -len,0);
		glRotated(180, 0, 0, 1);
		drawOneFourthCylinder(r, len);
	}
	glPopMatrix();

    ///back left
	glPushMatrix();
	{
		glTranslatef(len, -len,0);
		glRotated(-90, 0, 0, 1);
		drawOneFourthCylinder(r, len);
	}
	glPopMatrix();

    ///bottom back
	glPushMatrix();
	{
		glTranslatef(0, -len, -len);
		glRotated(-90, 1, 0, 0);
		glRotated(90, 0, 1, 0);
		drawOneFourthCylinder(r, len);
	}
	glPopMatrix();

    /// top back
	glPushMatrix();
	{
		glTranslatef(0, -len, len);
		glRotated(90, 1, 0, 0);
		glRotated(-90, 0, 1, 0);
		drawOneFourthCylinder(r, len);
	}
	glPopMatrix();

    /// top left
	glPushMatrix();
	{
		glTranslatef(len, 0, len);
		glRotated(90, 1, 0, 0);
		drawOneFourthCylinder(r, len);
	}
	glPopMatrix();
    ///bottom left
	glPushMatrix();
	{
		glTranslatef(len, 0, -len);
		glRotated(-90, 1, 0, 0);
		drawOneFourthCylinder(r, len);
	}
	glPopMatrix();

    ///top right
	glPushMatrix();
	{
		glTranslatef(-len, 0,  len);
		glRotated(-90, 0, 1, 0);
		glRotated(90, 1, 0, 0);
		drawOneFourthCylinder(r, len);
	}
	glPopMatrix();

    ///bottom right
	glPushMatrix();
	{
		glTranslatef(-len, 0, -len);
		glRotated(90, 0, 1, 0);
		glRotated(-90, 1, 0, 0);
		drawOneFourthCylinder(r, len);
	}
	glPopMatrix();

	///front left
	glPushMatrix();
	{
		glTranslatef(len, len,0);
		drawOneFourthCylinder(r, len);
	}
	glPopMatrix();

    /// front right
	glPushMatrix();
	{
		glTranslatef(-len, len,0);
		glRotated(90, 0, 0, 1);
		drawOneFourthCylinder(r, len);
	}
	glPopMatrix();


    /// front top
	glPushMatrix();
	{
		glTranslatef(0, len, len);
		glRotated(-90, 0, 1, 0);
		drawOneFourthCylinder(r, len);
	}
	glPopMatrix();

    /// front bottom
	glPushMatrix();
	{
		glTranslatef(0, len, -len);
		glRotated(90, 0, 1, 0);
		drawOneFourthCylinder(r, len);
	}
	glPopMatrix();
}


void keyboardListener(unsigned char key, int x, int y)
{

	switch (key)
	{
	case '1':
		l = rotate(l, u, 1);
		r = rotate(r, u, 1);
		break;
	case '2':
		l = rotate(l, u, -1);
		r = rotate(r, u, -1);
		break;
	case '3':
		u = rotate(u, r, -1);
		l = rotate(l, r, -1);
		break;
	case '4':
		u = rotate(u, r, 1);
		l = rotate(l, r, 1);
		break;
	case '5':
		u = rotate(u, l, -1);
		r = rotate(r, l, -1);
		break;
	case '6':
		u = rotate(u, l, 1);
		r = rotate(r, l, 1);
		break;
	default:
		break;
	}
}


void specialKeyListener(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_DOWN:
		p = sub(p, l);
		break;
	case GLUT_KEY_UP:
		p = add(p, l);
		break;
	case GLUT_KEY_RIGHT:
		p = sub(p, r);
		break;
	case GLUT_KEY_LEFT:
		p = add(p, r);
		break;
	case GLUT_KEY_PAGE_UP:
		p = add(p, u);
		break;
	case GLUT_KEY_PAGE_DOWN:
		p = sub(p, u);
		break;
	case GLUT_KEY_INSERT:
		break;
	case GLUT_KEY_HOME:
		len -= 0.2;
		len = max(len, 0.0);
		break;
	case GLUT_KEY_END:
		len += 0.2;
		len = min(len, max_len);
		break;
	default:
		break;
	}
}


void mouseListener(int button, int state, int x, int y) {	//x, y is the x-y of the screen (2D)
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {		// 2 times?? in ONE click? -- solution is checking DOWN or UP
			drawaxes = 1 - drawaxes;
		}
		break;

	case GLUT_RIGHT_BUTTON:
		//........
		break;

	case GLUT_MIDDLE_BUTTON:
		//........
		break;

	default:
		break;
	}
}


void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(p.x, p.y, p.z, p.x + l.x, p.y + l.y, p.z + l.z, u.x, u.y, u.z);
	glMatrixMode(GL_MODELVIEW);
	drawAxes();
	drawGrid();

	DrawSphere();
    draw6Squares();
	draw12Cylinders();

	glutSwapBuffers();
}


void animate() {
	angle += 0.05;
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init() {
	//codes for initialization

	max_len = 10;
	len = 10;
	slices = stacks = 50.0;

	p = { 0.0, 50.0, 0.0 };
	l = { 0.0, -1.0, 0.0 };
	r = { 1.0, 0.0, 0.0 };
	u = { 0.0, 0.0, 1.0 };

	drawgrid = 0;
	drawaxes = 1;
	cameraHeight = 150.0;
	cameraAngle = 1.0;
	angle = 0;

	//clear the screen
	glClearColor(0, 0, 0, 0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80, 1, 1, 1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}

