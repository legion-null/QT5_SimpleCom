#include <QApplication>
#include "simplecom.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	SimpleCom w;
	w.show();

	return app.exec();
}

