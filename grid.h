#ifndef GRID_H
#define GRID_H

#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QStringList>

#include <iostream>
#include <cmath>

using namespace std;

struct Pixel {
    int x,
        y;
    bool fill;
    Pixel()
    {
        x = y = 0;
        fill = false;
    }
};

const int MIN_SIZE = 10;
const int MAX_SIZE = 81;

class Grid : public QWidget
{
    Q_OBJECT
    public:
        Grid(QWidget *parent = 0);
        int getRows();
        int getCols();

        QString getPicture();
        void setPicture(QString picture);
        void enableEraser(bool value);
        bool isEraserActive();

        int rows, cols;
        double rect_width, rect_height;

    public slots:
        void setRows(int value);
        void setCols(int value);

    protected:
        void paintEvent(QPaintEvent *);
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);

    private:
        struct Pixel grid[MAX_SIZE][MAX_SIZE];                
        bool activeEraser;

};

#endif // GRID_H
