#include "about.h"

About::About(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout  *hlayout = new QHBoxLayout(this);
    QPixmap pixmap("picture/applications-graphics.png");
    QLabel *label = new QLabel();
    label->setPixmap(pixmap);
    hlayout->addWidget(label);

    QVBoxLayout *vlayout = new QVBoxLayout();
    QLabel *program = new QLabel("Pix 1.0");
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    program->setFont(font);

    QLabel *copyright = new QLabel("Copyright (C) 2011 Rafael Rendon Pablo.");

    vlayout->addWidget(program, 0, Qt::AlignTop);
    vlayout->addWidget(copyright, 0, Qt::AlignTop);
    vlayout->addStretch(1);


    QPushButton *close = new QPushButton("&Close", this);
    connect(close, SIGNAL(clicked()), this, SLOT(close()));
    QHBoxLayout *hlayout2 = new QHBoxLayout();
    hlayout2->addWidget(close, 0, Qt::AlignRight);
    vlayout->addLayout(hlayout2);

    hlayout->addLayout(vlayout);
    setLayout(hlayout);


    setGeometry(0, 0, 300, 130);
    QDesktopWidget *desktop = QApplication::desktop();
    int w = frameGeometry().width(),
        h = frameGeometry().height();

    int screenWidth = desktop->width(),
        screenHeight= desktop->height();

    int x = (screenWidth - w)/2,
        y = (screenHeight - h)/2;
    move(x, y);
}

