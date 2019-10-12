#pragma once
#include "D:\Qt5\5.13.0\msvc2017_64\include\QtWidgets\qwidget.h"
#include<QWidget>
#include<QtGui>
#include<QMouseEvent>
#include<QPaintEvent>
#include<QResizeEvent>
#include<QColor>
#include<QPixmap>
#include<QPoint>
#include<QPainter>
#include<QPalette>
#include<QString>
#include<QVector>

class PaintArea :
	public QWidget
{
	Q_OBJECT
public:
	enum Shape { Line, Polygon, Ellipse, Circle, Erase};
	explicit PaintArea(QWidget* parent = 0);
	void loadPixmap(QString);
	void savePixmap(QString);
	bool isChange();
protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent*);
	void mousePressEvent(QMouseEvent*);
	void mouseMoveEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);
signals:
public slots:
	void setShape(Shape);
	void setColor(QColor);
	void setStyle(int);
	void setWidth(int);
	void clear();
	void setEdgeNumber(int);
	
private:
	Shape shape;
	QPixmap pix;
	QColor color;
	QPoint startPos;
	QPoint endPos;
	QPixmap tempPix;
	QVector<QPoint> points;
	int style;
	int weight;
	int edgeNumber;
	bool isDrawing;
	bool isChanged;
};

