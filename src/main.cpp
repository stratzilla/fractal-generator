#include <GL/freeglut.h>
#include <FreeImage.h>

#include <iostream>
#include <sstream>
#include <array>

#include "Set.cpp"
#include "Fractal.cpp"
#include "Pixel.cpp"
#include "ComplexNumber.cpp"

#define WIDTH 800 // window width
#define HEIGHT 800 // window height

#define MAXDEPTH 4096 // maximum visual fidelity
#define MINDEPTH 32 // minimum

using namespace std;

Set s = Set(WIDTH, HEIGHT, ' '); // the set/fractal being visualized
bool newScene = true; // whether to draw a new scene

/**
* Save Image function
*/
void saveImage() {
	GLubyte* rgb = new GLubyte[3 * WIDTH*HEIGHT];
	glReadPixels(0, 0, WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, rgb);
	FIBITMAP* img = FreeImage_ConvertFromRawBits(rgb, WIDTH, HEIGHT, 3 * WIDTH, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
	FreeImage_Save(FIF_PNG, img, "output.png", 0);
	FreeImage_Unload(img);
}

/**
 * Keyboard Controls function
 */
void keyControls(unsigned char key, int x, int y) {
	switch (key) {
	case '1': s.setType('m'); s.resetDefaults(); break; // Mandelbrot
	case '2': s.setType('b'); s.resetDefaults(); break; // Burning Ship
	case '3': s.setType('j'); s.resetDefaults(); break; // Julia
	case '4': s.setType('t'); s.resetDefaults(); break; // Tri-Wing Mandelbrot
	case '5': s.setType('s'); s.resetDefaults(); break; // Two Squares
	case '6': s.setType('v'); s.resetDefaults(); break; // Tri-Wing Vein
	case '7': s.setType('f'); s.resetDefaults(); break; // Two Fists
	case '8': s.setType('r'); s.resetDefaults(); break; // Ring-Pops
	case '9': s.setType('x'); s.resetDefaults(); break; // Shurikens
	case '0': s.setType('c'); s.resetDefaults(); break; // Clover
	case 'r': s.resetDefaults(); break; // reset to defaults
	case 's': saveImage(); break; // save image
	}
	newScene = true; // new frame
	glutPostRedisplay(); // display new frame
}

/**
 * Mouse Controls function
 */
void mouseControls(int button, int state, int x, int y) {
	if (s.getType() != ' ') {
		// LMB is zoom-in
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			s.zoom('i', x, y); // 'i' = in, etc
			s.recalculateSet(); // redraw according to new system
			newScene = true; // it's a new frame
			glutPostRedisplay(); // so redraw it
		}
		// RMB is zoom-out
		else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
			s.zoom('o', x, y);
			s.recalculateSet();
			newScene = true;
			glutPostRedisplay();
		}
	}
}

/**
 * Display driver
 */
void display() {
	if (newScene) { // if new frame
		list<Pixel> lp = s.getPixels(); // get the list of pixels
		glClear(GL_COLOR_BUFFER_BIT); // clear the color bit
		glBegin(GL_POINTS); // begin drawing pixels
		// for each pixel
		for (list<Pixel>::iterator p = lp.begin(); p != lp.end(); ++p) {
			array<double, 3> rgb = p->getCol(); // grab rgb values
			array<int, 2> pos = p->getPos(); // grab position
			glColor3d(rgb[0], rgb[1], rgb[2]); // color accordingly
			glVertex2i(pos[0], pos[1]); // place in correct spot
		}
		glEnd(); // finish drawing pixels
		glFlush(); // flush buffer
		newScene = false; // don't continually redraw since static image
	}
}

/**
 * my attempt at not allowing resize, may not work with all window managers
 */
void windowResize(int w, int h) {
	// on resize, force resize to default
	glutReshapeWindow(WIDTH, HEIGHT);
}

/**
 * initialize glut related stuff
 */
void initGlut(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Fractal Display");
	glutKeyboardFunc(keyControls);
	glutMouseFunc(mouseControls);
	gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutReshapeFunc(windowResize);
	glutDisplayFunc(display);
	glutMainLoop();
}

/**
 * CLI Menu function
 */
void cliMenu() {
	cout << endl;
	cout << "+---------------------+" << endl;
	cout << "|  Fractal Generator  |" << endl;
	cout << "+---------------------+" << endl;
	cout << endl;
	cout << "Use keyboard controls to change fractal visual:" << endl;
	cout << endl;
	cout << "--- Traditional ---" << endl;
	cout << "1. Mandelbrot Set, 2. Burning Ship Set" << endl;
	cout << "3. Julia Set (k = -0.835 - 0.232i)" << endl;
	cout << endl;
	cout << "--- \"Custom\" ---" << endl;
	cout << "4. Tri-Winged Mandelbrot Set, 5. Two Boxes Set" << endl;
	cout << "6. Tri-Winged Vein Set, 7. Two Fists Set" << endl;
	cout << "8. Two Ring Pops Set, 9. Shuriken Set, 0. Clover Set" << endl;
	cout << "r. Reset to Defaults, s. Save Image" << endl;
	cout << endl;
	cout << "Use mouse controls to zoom:" << endl;
	cout << "LMB = Zoom In, RMB = Zoom Out" << endl;
	cout << endl;
}

/**
 * Main Driver
 */
int main(int argc, char** argv) {
	int depth = 128; // if Windows
	if (argc != 1) { // if Linux execution
		istringstream input(argv[1]);
		if (!(input >> depth)) { // if wrong type
			cout << "Invalid depth. Please use integer value 32..4096 as argument." << endl;
			return 0;
		} 
		if (depth < MINDEPTH || depth > MAXDEPTH) { // if bad range
			cout << "Invalid depth. Please use integer value 32..4096 as argument." << endl;
			return 0;
		}
	}
	s.setDepth(depth);
	cliMenu();
	initGlut(argc, argv);
	return 0; 
}