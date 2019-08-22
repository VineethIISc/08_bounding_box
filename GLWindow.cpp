#include "CommonHeader.h"

#include "TestPlyModel.h"


#include <QtGui/qevent.h>

#include "GLWindow.h"

GLWindow::GLWindow(QWidget* parent): QOpenGLWidget(parent), screenWidth(0), screenHeight(0)
{
	
	//3D ply object
	plyModel = new TestPlyModel;


}


GLWindow::~GLWindow()
{


	if (plyModel)
		delete plyModel;


}

void GLWindow::initializeGL()
{
	//initialise glew at first before using opengl functions
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		std::cout << "Failed to initialise the glew" << std::endl;
		exit(EXIT_FAILURE);
	}

	//opengl version and graphic card driver
	std::cout << "GL version: " << glGetString(GL_VERSION) << std::endl;
	//graphic card
	std::cout << "GL renderer: " << glGetString(GL_RENDERER) << std::endl;

	//background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	 //black color

	
	
	//load data to GPU
	sendDataToGPU();

	//set a timer
	myTimer = new QTimer;
	connect(myTimer, &QTimer::timeout, this, &GLWindow::myUpdate);
	myTimer->start(0);	//start immediately wihtout any delay

}

void GLWindow::sendDataToGPU()
{


	//load cube data
	plyModel->loadData();
}



void GLWindow::paintGL()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	
	//draw objects
	drawObjects();

	//check for any error
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		std::cerr << "OpenGL error: " << err << std::endl;
	}
	
}


void GLWindow::drawObjects()
{

	//draw 3D model
	plyModel->render();
	
}

void GLWindow::screenToClip(Vector2f& screenCoordinate)
{
	//y coordinate
	screenCoordinate.y = 1.0f - (screenCoordinate.y/ (0.5f * screenHeight) );
	screenCoordinate.x = (screenCoordinate.x / (0.5f * screenWidth)) - 1.0f;
}

void GLWindow::myUpdate()
{
	repaint();
}



void GLWindow::resizeGL(int w, int h)
{
	screenWidth = w;
	screenHeight = h;
	float ratio = (float)screenWidth / screenHeight;

	plyModel->setAspectRatio(ratio);

}

void GLWindow::mousePressEvent(QMouseEvent* buttonPress)
{
	//Dstd::cout << "Mouse is pressed" << std::endl;

	//check for left button press event
	if (buttonPress->button() == Qt::LeftButton)
	{
		//get the position
		QPoint mousePos = buttonPress->pos();

		Vector2f mPos(mousePos.x(), mousePos.y());
		screenToClip(mPos);
		
	}

	//render at the end of every event: call paintGL
	update();
}


