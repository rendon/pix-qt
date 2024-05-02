#include "window.h"

Window::Window(QWidget *parent) : QMainWindow(parent)
{
    grid = new Grid();
    setCentralWidget(grid);

    About *about = new About();

    openPix = new QPixmap("picture/document-open.png");
    savePix = new QPixmap("picture/document-save.png");
    quitPix = new QPixmap("picture/application-exit.png");
    aboutPix = new QPixmap("picture/help-about.png");
    erasePix = new QPixmap("picture/draw-eraser.png");
    pencilPix = new QPixmap("picture/pencil.png");

    // File menu
    fileMenu = menuBar()->addMenu("&File");
    openAction = new QAction(*openPix, "&Open", this);
    saveAction = new QAction(*savePix, "&Save", this);
    quitAction = new QAction(*quitPix, "&Quit", this);
    eraseAction = new QAction(*erasePix, "&Eraser", this);

    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);

    // Help menu
    QMenu *helpMenu = menuBar()->addMenu("&Help");
    QAction *aboutAction = new QAction(*aboutPix, "&About", this);
    helpMenu->addAction(aboutAction);
    connect(aboutAction, SIGNAL(triggered()), about, SLOT(show()));


    // Tool bar
    QToolBar *toolbar = addToolBar("main toolbar");

    toolbar->addAction(openAction);
    toolbar->addAction(saveAction);
    toolbar->addSeparator();
    toolbar->addAction(quitAction);
    toolbar->addAction(eraseAction);

    // Actions behavior
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(openAction, SIGNAL(triggered()), this, SLOT(openPicture()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(savePicture()));
    connect(eraseAction, SIGNAL(triggered()), this, SLOT(eraserTool()));


    rowSpinbox = new QSpinBox();
    rowSpinbox->setRange(5, 80);
    rowSpinbox->setValue(10);
    connect(rowSpinbox, SIGNAL(valueChanged(int)), grid, SLOT(setRows(int)));
    toolbar->addWidget(rowSpinbox);

    colSpinbox = new QSpinBox();
    colSpinbox->setRange(5, 80);
    colSpinbox->setValue(10);
    connect(colSpinbox, SIGNAL(valueChanged(int)), grid, SLOT(setCols(int)));
    toolbar->addWidget(colSpinbox);
}

void Window::savePicture()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save picture", "~/",
                                                    "File (*.txt *.TXT)");
    QString picture = grid->getPicture();
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
        return;
    QTextStream out(&file);
    out << picture;
}

void Window::openPicture()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Save picture", "~/",
                                                    "File (*.txt *.TXT)");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream input(&file);
    grid->setPicture(input.readAll());

    rowSpinbox->setValue(grid->getRows());
    colSpinbox->setValue(grid->getCols());
}

void Window::eraserTool()
{
    if (grid->isEraserActive()) {
        eraseAction->setIcon(QIcon(*erasePix));
        grid->enableEraser(false);
    } else {
        eraseAction->setIcon(QIcon(*pencilPix));
        grid->enableEraser(true);
    }
}
