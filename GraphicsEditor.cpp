#include "GraphicsEditor.h"
#include<QFileDialog>
#include<QFile>
#include<QIODevice>
#include<iostream>
#include<QLabel>
#include<QColorDialog>
#include<QMessageBox>
#include<QMenu>

GraphicsEditor::GraphicsEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	complateToolBar();
	setMinimumSize(600, 400);
	edgeNumberSpinBox = new QSpinBox;
	edgeNumberSpinBox->setMinimum(3);
	ui.mainToolBar->insertWidget(ui.circleAction, edgeNumberSpinBox);
	connect(edgeNumberSpinBox, SIGNAL(valueChanged(int)), ui.paintArea, SLOT(setEdgeNumber(int)));

	connect(ui.openAction, SIGNAL(triggered()), this, SLOT(showOpenImage()));
	connect(ui.saveAction, SIGNAL(triggered()), this, SLOT(saveImage()));
	
	ShowStyle();
	ui.paintArea->setWidth(widthSpinBox->value());
	ui.paintArea->setColor(Qt::black);

}
void GraphicsEditor::complateToolBar()
{
	styleLabel = new QLabel(tr("lineStyle:"));
	styleComboBox = new QComboBox;
	styleComboBox->addItem(tr("SolidLine"), static_cast<int>(Qt::SolidLine));
	styleComboBox->addItem(tr("DashLine"), static_cast<int>(Qt::DashLine));
	styleComboBox->addItem(tr("DotLine"), static_cast<int>(Qt::DotLine));
	styleComboBox->addItem(tr("DashDotLine"), static_cast<int>(Qt::DashDotLine));
	styleComboBox->addItem(tr("DashDotDotLine"), static_cast<int>(Qt::DashDotDotLine));
	connect(styleComboBox, SIGNAL(activated(int)), this, SLOT(ShowStyle()));

	widthLabel = new QLabel(tr("lineWidth:"));
	widthSpinBox = new QSpinBox;
	connect(widthSpinBox, SIGNAL(valueChanged(int)), ui.paintArea, SLOT(setWidth(int)));
	
	colorBtn = new QToolButton;
	QPixmap pixmap(20, 20);
	pixmap.fill(Qt::black);
	colorBtn->setIcon(QIcon(pixmap));
	connect(colorBtn, SIGNAL(clicked()), this, SLOT(ShowColor()));

	clearBtn = new QToolButton;
	clearBtn->setText(tr("clear"));
	connect(clearBtn, SIGNAL(clicked()), ui.paintArea, SLOT(clear()));
	ui.mainToolBar->addWidget(styleLabel);
	ui.mainToolBar->addWidget(styleComboBox);
	ui.mainToolBar->addWidget(widthLabel);
	ui.mainToolBar->addWidget(widthSpinBox);
	ui.mainToolBar->addWidget(colorBtn);
	ui.mainToolBar->addWidget(clearBtn);
}
void GraphicsEditor::ShowStyle()
{
	ui.paintArea->setStyle(styleComboBox->itemData(
		styleComboBox->currentIndex(), Qt::UserRole).toInt());
}
void GraphicsEditor::selectEraseShape()
{
	if (ui.eraseAction->isChecked())
	{
		ui.lineAction->setChecked(false);
		ui.ellipseAction->setChecked(false);
		ui.circleAction->setChecked(false);
		ui.polygonAction->setChecked(false);
		ShowShape();
	}
}
void GraphicsEditor::selectLineShape()
{
	if (ui.lineAction->isChecked())
	{
		ui.ellipseAction->setChecked(false);
		ui.circleAction->setChecked(false);
		ui.polygonAction->setChecked(false);

		ui.eraseAction->setChecked(false);
		ShowShape();
	}
}
void GraphicsEditor::selectEllipseShape()
{
	if (ui.ellipseAction->isChecked())
	{
		ui.lineAction->setChecked(false);
		ui.circleAction->setChecked(false);
		ui.polygonAction->setChecked(false);

		ui.eraseAction->setChecked(false);
		ShowShape();
	}
}
void GraphicsEditor::selectRoundShape()
{
	if (ui.circleAction->isChecked())
	{
		ui.lineAction->setChecked(false);
		ui.ellipseAction->setChecked(false);
		ui.polygonAction->setChecked(false);

		ui.eraseAction->setChecked(false);
		ShowShape();

	}
}
void GraphicsEditor::selectPolygonShape()
{
	if (ui.polygonAction->isChecked())
	{
		ui.lineAction->setChecked(false);
		ui.ellipseAction->setChecked(false);
		ui.circleAction->setChecked(false);

		ui.eraseAction->setChecked(false);
		ShowShape();
		
	}
}
void GraphicsEditor::ShowShape()
{
	PaintArea::Shape shape;
	if (ui.lineAction->isChecked())
	{
		shape = PaintArea::Shape::Line;

	}
	else if (ui.ellipseAction->isChecked())
	{
		shape = PaintArea::Shape::Ellipse;

	}
	else if (ui.circleAction->isChecked())
	{
		shape = PaintArea::Shape::Circle;
	}
	else if (ui.polygonAction->isChecked())
		shape = PaintArea::Shape::Polygon;
	else if (ui.eraseAction->isChecked())
		shape = PaintArea::Shape::Erase;
	ui.paintArea->setShape(shape);
}
void GraphicsEditor::ShowColor()
{
	QColor color = QColorDialog::getColor(static_cast<int>(Qt::black),
		this);
	if (color.isValid())
	{
		ui.paintArea->setColor(color);
		QPixmap p(20, 20);
		p.fill(color);
		colorBtn->setIcon(QIcon(p));
	}
}
void GraphicsEditor::showOpenImage()
{
	if (ui.paintArea->isChange())
	{
		QMessageBox::StandardButton res = QMessageBox::information(this, tr("Save picture"), tr("Save the drawing picture"), QMessageBox::Save |
			QMessageBox::Ignore| QMessageBox::Cancel, QMessageBox::Save
		);
		if (res == QMessageBox::Save)
		{
			saveImage();
		}
		else if (res == QMessageBox::Ignore)
		{

		}
		else if(res == QMessageBox::Cancel)
			return;
	}
		
	fileName = QFileDialog::getOpenFileName(this, tr("open Image"),"",tr("Image Files(*.png *.jpg)"));
	if (fileName.isEmpty())
		return;
	else
	{

		ui.paintArea->loadPixmap(fileName);
	}
}

void GraphicsEditor::saveImage()	//±£´æÍ¼ÐÎ
{
	fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("*.png *.jpg"));
	if (fileName.isEmpty())
		return;
	else
	{
		ui.paintArea->savePixmap(fileName);
	}
}
void GraphicsEditor::setWinTitle()
{
	setWindowTitle(ui.paintArea->windowTitle());
}