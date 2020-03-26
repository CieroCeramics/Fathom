#include <stdlib.h>
#include <time.h>
#include <iostream>
 #include"Lighting.h"

using namespace std;

//#include<GL/glu.h>
#include"include.h"
#include "Matrix.h"
#include "FBO.h"
#include"Shader.h"

unsigned int TE;
static const char *thisProgram ="Fathom Eternity Test";
//variables
//shwoop da woop
static double fps = 30.0;
static double spf = 1.0 / fps;
  Vector3f axis, vect;

unsigned int WINDOW_LOCATION_X;// = glutGet(GLUT_SCREEN_WIDTH) * 0.1; //Sets window location x to middle of screen based off of the above 80%
unsigned int WINDOW_LOCATION_Y;// = glutGet(GLUT_SCREEN_HEIGHT) * 0.1; //Sets window location y to middle of screen based off of the above 80%

	float MAIN_WINDOW_WIDTH = 400;// glutGet(GLUT_SCREEN_WIDTH) * 0.8;
	float MAIN_WINDOW_HEIGHT = 400;//glutGet(GLUT_SCREEN_HEIGHT) * 0.8;
	float aspectRatio = MAIN_WINDOW_WIDTH / MAIN_WINDOW_HEIGHT;
	float fovy = 30.0;
	float SIDE_WINDOW_WIDTH = 0.0f; //Side window is for the one thats supposed to render the sample object
	float SIDE_WINDOW_HEIGHT = MAIN_WINDOW_HEIGHT;

  ///////////////////////////////////////////////////
  //fbo
  FBO aFBO;
  Shader aShader;
  unsigned int sceneFBO;

  //lighting handles
unsigned int sceneColour[2];	// colour(0) and normals(1)
unsigned int sceneDepth;
//progrAms
// unsigned int lightingProgram;
// int toon_inputImage;
// int toon_qmap;
// int lpMVP;
// int lp_globAmb;
// int lp_lightCol;
// int lp_lightPos;
// int lp_eyePos;
// int lp_colourTex;
 int amb, diff,spec,shin;

// unsigned int edgeProgram;
// int edge_inputColour;
// int edge_inputNormal;
// int edge_inputDepth;
// int edge_pixelSize;


////////////////////////////////////////////////////////////
// static Matrix projMatrix;

//   Matrix translateMatrix, rotateMatrix,
//         modelMatrix, viewMatrix,
//         modelViewMatrix, modelViewProjMatrix;


static float eyeHeight = 0.0f;    /* Vertical height of light. */
static float eyeAngle  = 0.53f;   /* Angle in radians eye rotates around monkey. */
static float lightAngle = -0.4;   /* Angle light rotates around scene. */
static float lightHeight = 1.0f;  /* Vertical height of light. */

static float globalAmbient[3]={0.1,0.1,0.1};//dim
static float lightColour[3]= { 0.95, 0.95, 0.95 };  /* White */

static float headSpin = 0.0f;  /* Head spin in degrees. */
static float shininess = 8.9f;

static float Kd[4] = { 0.8f, 0.6f, 0.2f, 1.0f }; /* Diffuse color */
static float Ks[4] = { 0.3f, 0.3f, 4.0f, 0.0f }; /* Specular color */

void initImageLibrary() //Initializes DevIL
{
	
	glEnable(GL_TEXTURE_2D);
	ilInit(); //Inits Il
	iluInit(); //Inits Ilu
	ilutRenderer(ILUT_OPENGL); //Uses OpenGL to render?
}
struct Object///////temporary//////////////
{
	float tx, ty, tz;	// translation
	float rx, ry, rz;	// rotation
	float time;			// animation parameter
};

Object camera = { 0 };

static void Display(void);
static void reshape(int width, int height);
static void idle(void);
static void Timer(int value);

static void Keyboard(unsigned char c, int x, int y);
static void KeyboardUp(unsigned char c, int x, int y);
static void menu(int item);
static void Mouse(int button, int state, int x, int y);
static void Motion(int x, int y);

unsigned int passThruProgram;
unsigned int fixedColourProgram;
unsigned int uniformColourProgram;
unsigned int textureProgram;
unsigned int pvLightingProgram;
unsigned int textureHandle;


int uniformColourHandle;
int uniformTextureHandle;

unsigned int aTexture;

//Lighting light1;
int mode = 0;


void Init();
void Update(double dt);
void Render();
//void InitGL(int argc, char** argv);

int main(int argc, char **argv)
{
		//GLUT Initialization
	glutInit(&argc, argv);
	

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //Double buffer with RGBA colors and depth
	glutInitWindowPosition(WINDOW_LOCATION_X, WINDOW_LOCATION_Y); //Where the window starts on your screen
	glutInitWindowSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT); //Window size. Temp
	//glShadeModel(GL_FLAT); //Used for texturing I guess
	glutCreateWindow(thisProgram); //Window title

	WINDOW_LOCATION_X= glutGet(GLUT_SCREEN_WIDTH) * 0.1; //Sets window location x to middle of screen based off of the above 80%

	WINDOW_LOCATION_Y = glutGet(GLUT_SCREEN_HEIGHT) * 0.1; //Sets window location y to middle of screen based off of the above 80%

	
	glutDisplayFunc(Display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutTimerFunc(0, Timer, 1);

	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	


	

	//initImageLibrary();

	
	glEnable(GL_DEPTH_TEST);         /* Hidden surface removal. */
	glEnable(GL_CULL_FACE);


glClearColor(0.1, 0.1, 0.1, 0);  /* Gray background. */
	//glEnable(GL_TEXTURE_2D);




	  if (glewInit()!=GLEW_OK || !GLEW_VERSION_1_1) {
    fprintf(stderr, "%s: failed to initialize GLEW, OpenGL 1.1 required.\n", thisProgram);    
    exit(1);
  }
	  const unsigned char *version = glGetString(GL_VERSION);

	Init();


	glutMainLoop();
	//return 0;
}
void Display()
{
}

void reshape(int x, int y)
{

	MAIN_WINDOW_HEIGHT = x;
	MAIN_WINDOW_WIDTH = y;
	aspectRatio = (double)x / (double)y;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, aspectRatio, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	// glViewport(0,0,(GLsizei) newWidth, (GLsizei) newHeight);
	// glMatrixMode(GL_PROJECTION);
	// glLoadIdentity();
	// glOrtho (-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
	// glMatrixMode(GL_MODELVIEW);
	// glLoadIdentity();


}

void Timer(int value)
{
	Update(spf);
	Render();

	glutTimerFunc(1000.0*spf, Timer, value);
	glutPostRedisplay();
}

void Keyboard(unsigned char c, int x, int y)
{
static int animating = 0;
  static int wireframe = 0;

  switch (c) {
  case 32:
    animating = !animating; /* Toggle */
    if (animating) {
      glutIdleFunc(idle);
    } else {
      glutIdleFunc(NULL);
    }    
    break;
  case '+':
    shininess *= 1.05;
    printf("shininess = %f\n", shininess);
	//glUniform1f(light1.setBrassMaterial.
    glutPostRedisplay();
    break;
  case '-':
    shininess /= 1.05;
    printf("shininess = %f\n", shininess);
   // cgSetParameter1f(myCgVertexParam_shininess, shininess);
    glutPostRedisplay();
    break;
  case 'w':
    wireframe = !wireframe; /* Toggle */
    // if (wireframe) {
    //   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // } else {
    //   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // }
    glutPostRedisplay();
    break;
  case 27:  /* Esc key */
    /* Demonstrate proper deallocation of Cg runtime data structures.
       Not strictly necessary if we are simply going to exit. */
    exit(0);
    break;
  }
}
void KeyboardUp(unsigned char key, int x, int y)
{
	switch (key)
	{
		// switch shader
	case 'M':
		mode = (mode + 1) % 6;
		printf("Changed mode?\n");
		break;
	}
}

static int beginx, beginy;
static int moving = 0;
static int movingLight = 0;
static int xLightBegin, yLightBegin;
void Mouse(int button, int state, int x, int y)
{
	  const int spinButton = GLUT_LEFT_BUTTON,
            lightButton = GLUT_MIDDLE_BUTTON;

  if (button == spinButton && state == GLUT_DOWN) {
    moving = 1;
    beginx = x;
    beginy = y;
	printf("mousedown");
  }
  if (button == spinButton && state == GLUT_UP) {
    moving = 0;
  }
  if (button == lightButton && state == GLUT_DOWN) {
  //  movingLight = 1;
    xLightBegin = x;
    yLightBegin = y;
  }
  if (button == lightButton && state == GLUT_UP) {
    movingLight = 0;
  }
}

void Motion(int x, int y)
{
	  const float heightBound = 8;

  if (moving) {
    eyeAngle += 0.005*(beginx - x);
    eyeHeight += 0.01*(y - beginy);
    if (eyeHeight > heightBound) {
      eyeHeight = heightBound;
    }
    if (eyeHeight < -heightBound) {
      eyeHeight = -heightBound;
    }
    beginx = x;
    beginy = y;
    glutPostRedisplay();
  }
  if (movingLight) {
    lightAngle += 0.005*(x - xLightBegin);
    lightHeight += 0.03*(yLightBegin - y);
    xLightBegin = x;
    yLightBegin = y;
    glutPostRedisplay();
  }
}

static void idle(void)
{
	  headSpin -= 0.5;
  if (headSpin < -360) {
    headSpin += 360;
  }

  glutPostRedisplay();
}

	
void Init()
{
{
		const char* vert = "Resource/passThru_v.glsl";
		const char* frag = "Resource/passThru_f.glsl";
	//	unsigned int vrt = GLSLVertexShaderFromFile(vert);

			passThruProgram = aShader.GLSLProgram(aShader.GLSLVertexShaderFromFile(vert), aShader.GLSLFragmentShaderFromFile(frag));//GLSLProgramFromFiles(1, &vert, 0, 1, &frag, 0);
	}

	// fixed colour
	{
		const char* frag = "Resource/fixedColour_f.glsl";
		fixedColourProgram  = aShader.GLSLProgram(0, aShader.GLSLFragmentShaderFromFile(frag));// GLSLProgramFromFiles(0, 0, 0, 1, &frag, 0);
	}

	// uniform colour
	{
		const char* frag = "Resource/uniformColour_f.glsl";
		uniformColourProgram = aShader.GLSLProgram(0, aShader.GLSLFragmentShaderFromFile(frag));// GLSLProgramFromFiles(0, 0, 0, 1, &frag, 0);
		uniformColourHandle = glGetUniformLocation(uniformColourProgram, "colour");
	}

	// texture
	{
		const char* frag = "Resource/texture_f.glsl";
		textureProgram = aShader.GLSLProgram(0, aShader.GLSLFragmentShaderFromFile(frag)); //GLSLProgramFromFiles(0, 0, 0, 1, &frag, 0);
		uniformTextureHandle = glGetUniformLocation(textureProgram, "tex");
	}

	// per-vertex lighting
	{
		const char* vert = "Resource/perVertexLighting_v.glsl";
		pvLightingProgram = aShader.GLSLProgram(aShader.GLSLVertexShaderFromFile(vert),0);// GLSLProgramFromFiles(1, &vert, 0, 0, 0, 0);
	}
	{
		glEnable(GL_TEXTURE_2D);

		glGenTextures(1, &textureHandle);
		glBindTexture(GL_TEXTURE_2D, textureHandle);

		unsigned char textureData[] = {
			// black		// red
			0,0,0,255,		255,0,0,255,
			// green		// yellow
			0,255,0,255,	255,255,0,255,
		};
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	//init image library and load images
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);

}

void Update(double dt)
{
	camera.time += 0.25f * dt;
	camera.tx = 25.0f * cosf(camera.time);
	camera.ty = 25.0f;
	camera.tz = -25.0f * sinf(camera.time);
}


void setBrassMaterial(unsigned int program)
{
	float brassEmmisive = 0.0;

	float  brassAmbient[3] = { 0.33, 0.22, 0.03 };
	float brassDiffuse[3] = { 0.78, 0.57, 0.11 };
	float brassSpecular[3] = { 0.99, 0.91, 0.81 };
	float brassShininess = 27.8;


	glUniform3f(amb, brassAmbient[0], brassAmbient[1], brassAmbient[2]);
	glUniform3f(diff, brassDiffuse[0], brassDiffuse[1], brassDiffuse[2]);
	glUniform3f(spec, brassSpecular[0], brassSpecular[1], brassSpecular[2]);
	glUniform1f(shin, brassShininess);
}
void Render()
{

	static float r;
	r += 1.0f;

	//Vector3f eye;
	//	eye.set(8*sin(eyeAngle), eyeHeight, 8*cos(eyeAngle));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0, 0, -5.0f);
	//shadersss?/
	//setBrassMaterial(lightingProgram);
	switch (mode)
	{
		// no effect
	case 0:
		break;

		// pass-through
	case 1:
		glUseProgram(passThruProgram);
		//printf("passthruProgram\n");
		;
		break;

		// fixed colour
	case 2:
		glUseProgram(fixedColourProgram);
		//printf("fixedColour\n");
		break;

		// uniform colour
	case 3:
		glUseProgram(uniformColourProgram);
		glUniform4f(uniformColourHandle, 0.25f, 0.5f, 1.0f, 1.0f);
		
		break;

		// texture
	case 4:
		glUseProgram(textureProgram);
		glBindTexture(GL_TEXTURE_2D, textureHandle);
		glUniform1i(uniformTextureHandle, 0);
		
		break;

		// per-vertex lighting
	case 5:
		glUseProgram(pvLightingProgram);
		
		break;
	}
	// render objects
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glRotatef(r, 1.0f, 0.0f, 0.0f);
	glRotatef(r, 0.0f, 1.0f, 0.0f);
	glRotatef(r, 0.0f, 0.0f, 1.0f);
	glutSolidTeapot(1.0);
	glPopMatrix();



	glUseProgram(0);
	glBindTexture(GL_TEXTURE_2D, 0);


	// finished, swap buffers
	glutSwapBuffers();

}
void RenderTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TE);
}

//void setUniformLocations (unsigned int program)
//{
//	amb = glGetUniformLocation(program,"Ka" );
//	diff = glGetUniformLocation(program,"Kd" );
//	spec = glGetUniformLocation(program,"Ks" );
//	shin = glGetUniformLocation(program, "shininess");
//
//}



