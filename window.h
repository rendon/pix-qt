#ifndef WINDOW_H
#define WINDOW_H

#include <QApplication>
#include <QTextStream>
#include <QMainWindow>
#include <QFrame>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolBar>
#include <QPushButton>
#include <QLabel>
#include <QIcon>
#include <QPixmap>
#include <QFileDialog>
#include <QByteArray>
#include <QSpinBox>

#include "grid.h"
#include "about.h"

class Window : public QMainWindow
{
    Q_OBJECT
    public:
        Window(QWidget *parent = 0);

    public slots:
        void savePicture();
        void openPicture();
        void eraserTool();


    private:
        QPushButton *openButton;
        QPushButton *saveButton;
        QPushButton *quitButton;
        QSpinBox    *rowSpinbox;
        QSpinBox    *colSpinbox;
        Grid *grid;

        QPixmap *openPix;
        QPixmap *savePix;
        QPixmap *quitPix;
        QPixmap *aboutPix;
        QPixmap *erasePix;
        QPixmap *pencilPix;

        QMenu *fileMenu;
        QAction *openAction;
        QAction *saveAction;
        QAction *quitAction;
        QAction *eraseAction;
};

#endif // WINDOW_H
