#include "reader.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Reader w;
	w.show();

	return a.exec();
}
