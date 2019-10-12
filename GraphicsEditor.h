#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GraphicsEditor.h"
#include<QBrush>
#include<QString>
#include<PaintArea.h>
#include<QGridLayout>
#include<QLabel>
#include<QToolButton>
#include<QComboBox>
#include<QSpinBox>

class GraphicsEditor : public QMainWindow
{
	Q_OBJECT

public:
	GraphicsEditor(QWidget *parent = Q_NULLPTR);
	enum Shape { Line, Polygon, Ellipse, Round };
	void complateToolBar();
	
protected slots:
	void selectEraseShape();
	void selectLineShape();
	void selectEllipseShape();
	void selectRoundShape();
	void selectPolygonShape();
	void ShowShape();
	void ShowColor();
	void ShowStyle();
	void showOpenImage();
	void saveImage();
	void setWinTitle();
	
private:
	Ui::GraphicsEditor ui;

	QSpinBox* edgeNumberSpinBox;

	QString fileName;
	QLabel* styleLabel;
	QComboBox* styleComboBox;
	QLabel* widthLabel;
	QSpinBox* widthSpinBox;
	QToolButton* colorBtn;
	QToolButton* clearBtn;


};
