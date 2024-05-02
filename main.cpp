#include <QApplication>

#include "ArenaView.h"

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	ArenaView av;
	av.show();
	return app.exec();
}
