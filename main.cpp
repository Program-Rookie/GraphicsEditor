#include "GraphicsEditor.h"
#include <QtWidgets/QApplication>
#include<QFont>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QFont font("ZYSong18030", 10);
	a.setFont(font);
	GraphicsEditor w;
	w.show();

	return a.exec();
}
