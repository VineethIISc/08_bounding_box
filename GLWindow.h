#ifndef GL_WINDOW_H
#define GL_WINDOW_H

#include <QtWidgets/qopenglwidget.h>
#include <QtCore/qtimer.h>

class TestPlyModel;
class Vector2f;


class GLWindow: public QOpenGLWidget
{
public:
	GLWindow(QWidget * parent);
	~GLWindow();

protected:
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int w, int h) override;
	void mousePressEvent(QMouseEvent* buttonPress) override;

private:
	TestPlyModel* plyModel;
	
private:
	void sendDataToGPU();
	void drawObjects();
	void screenToClip(Vector2f& screenCoordinate);

private:
	//screen properties
	int screenWidth, screenHeight;
	float aspectRatio;


	//qtimer 
	QTimer* myTimer;

private slots:
	void myUpdate();
};
#endif

