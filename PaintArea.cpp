#include "PaintArea.h"
#include<QPainter>
#include<QtGui>
#include<QPen>
#include<iostream>
PaintArea::PaintArea(QWidget* parent):
	QWidget(parent)
{
	setPalette(QPalette(Qt::white));
	setAutoFillBackground(true);
	pix = QPixmap(size());
	pix.fill(Qt::white);
	isDrawing = false;
	isChanged = false;
	edgeNumber = 3;//������εı�������3��
}
void PaintArea::setShape(Shape s)
{
	shape = s;
	setCursor(Qt::CrossCursor);
}
void PaintArea::setStyle(int s)
{
	style = s;
}
void PaintArea::setWidth(int w)
{
	weight = w;
}
void PaintArea::setColor(QColor c)
{
	color = c;
	startPos = endPos;//��ֹ�ѻ�ͼ����ɫ�仯
	points.clear();//
}
void PaintArea::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	int x, y, w, h;
	x = startPos.x();
	y = startPos.y();
	w = endPos.x() - x;
	h = endPos.y() - y;
	QPen pen;
	pen.setStyle((Qt::PenStyle) style);
	pen.setWidth(weight);
	pen.setColor(color);
	QPainter painter(this);
	if (isDrawing)
	{
		tempPix = pix;
		QPainter pp(&tempPix);

		pp.setPen(pen);
		switch (shape)
		{
		case Line:
			pp.drawLine(startPos, endPos); break;
		case Polygon:
			if (points.size())
			{
				pp.drawPoint(points.last());
				if (points.size() == edgeNumber)
				{
					pp.drawPolygon(points);
				}
			}
				
			
			/*if (points.size() < edgeNumber)
			{
				pp.drawPoint(points.last());
			}
			else
				pp.drawPolygon(points.toStdList, edgeNumber);*/
				break;
		case Ellipse:
			pp.drawEllipse(x, y, w, h); break;
		case Circle:
			pp.drawEllipse(x, y, w, w); break;
		case Erase:
			pp.eraseRect(x, y, w, h); break;
		default:
			break;
		}
		painter.drawPixmap(QPoint(0, 0), tempPix);
	}
	else
	{
		QPainter pp(&pix);
		QPen pen;
		pen.setStyle((Qt::PenStyle) style);
		pen.setWidth(weight);
		pen.setColor(color);

		pp.setPen(pen);
		switch (shape)
		{
		case Line:
			if(startPos != endPos)
				pp.drawLine(startPos, endPos); 
			break;
		case Polygon:
			if (points.size())
			{
				pp.drawPoint(points.last());
				if (points.size() == edgeNumber)
				{
					pp.drawPolygon(points);
				}
			}
			break;
		case Ellipse:
			pp.drawEllipse(x, y, w, h); break;
		case Circle:
			pp.drawEllipse(x, y, w, w); break;
		case Erase:
			pp.eraseRect(x, y, w, h); break;
		default:
			break;
		}
		painter.drawPixmap(QPoint(0, 0), pix);
	}
	
}
void PaintArea::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton)
	{
		startPos = e->pos();
		endPos = startPos;
		isDrawing = true;
		isChanged = true;
		setWindowTitle(QString("GraphicsEditor") + QString("*"));
		if (shape == PaintArea::Shape::Polygon)
		{
			if (points.size() < edgeNumber)
			{
				points.append(e->pos());//��ӻ�ͼ����
				update();
			}
			else
			{
				update();
				points.clear();//�ͷ��ϸ�����εĶ�������
				points.append(e->pos());
				update();
			}
		}
	}
		
}
void PaintArea::mouseMoveEvent(QMouseEvent* e)
{
	if (e->buttons() & Qt::LeftButton)
	{
		endPos = e->pos();
		update();
	}
		
}
void PaintArea::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		endPos = event->pos();
		isDrawing = false;
		update();
	}
	
}
void PaintArea::resizeEvent(QResizeEvent *event)
{
	if (height() > pix.height() || width() > pix.width())
	{
		QPixmap newPix = QPixmap(size());
		newPix.fill(Qt::white);
		QPainter p(&newPix);
		p.drawPixmap(QPoint(0, 0), pix);
		pix = newPix;
	}
	QWidget::resizeEvent(event);
}

void PaintArea::clear()
{
	QPixmap clearPix = QPixmap(size());
	clearPix.fill(Qt::white);
	pix = clearPix;
	startPos = endPos;//��ֹupdate()���ػ��ϴε�ֱ��
	points.clear();//���ö����
	update();
}
void PaintArea::loadPixmap(QString fileName)
{
	pix.load(fileName);
	update();
	resize(pix.size());
	//������
	
}
void PaintArea::savePixmap(QString fileName)
{
	pix.save(fileName);
	isChanged = false;
	setWindowTitle("GraphicsEditor");
	//������
}
void PaintArea::setEdgeNumber(int n)
{
	edgeNumber = n;
	points.clear();
}
bool PaintArea::isChange()
{
	return isChanged;
}