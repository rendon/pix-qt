#include <QtGui>
#include <QDesktopWidget>

#include "grid.h"
#include "window.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Window window;
    window.setWindowTitle("Pix");
    window.setGeometry(0, 0, 500, 400);

    QDesktopWidget *desktop = QApplication::desktop();
    int w = window.frameGeometry().width(),
        h = window.frameGeometry().height();

    int screenWidth = desktop->width(),
        screenHeight= desktop->height();

    int x = (screenWidth - w)/2,
        y = (screenHeight - h)/2;
    window.move(x, y);
    window.show();

    return app.exec();
}

