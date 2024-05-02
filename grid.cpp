#include "grid.h"

Grid::Grid(QWidget *parent) : QWidget(parent)
{
    rows = cols = MIN_SIZE;
    activeEraser = false;
}

void Grid::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    rect_width = width()/(double)cols;
    rect_height = height()/(double)rows;

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            grid[i][j].x = i * rect_width;
            grid[i][j].y = j * rect_height;
        }
    }

    painter.setPen(Qt::lightGray);
    // Draw grid
    int x1, y1, x2, y2;
    for (int i = 0; i < rows; i++) {
        y1 = y2 = int(round(i * rect_height));
        x1 = 0;
        x2 = size().width() - 1;
        painter.drawLine(x1, y1, x2, y2);
    }

    for (int i = 0; i < cols; i++) {
        x1 = x2 = int(round(i * rect_width));
        y1 = 0;
        y2 = size().height() - 1;
        painter.drawLine(x1, y1, x2, y2);
    }

    painter.setBrush(QBrush("#000000"));
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            if (grid[i][j].fill) {
                int w = int(rect_width + 0.5);
                int h = int(rect_height + 0.5);
                painter.drawRect(grid[i][j].x, grid[i][j].y, w, h);
            }
        }
    }
}

void Grid::mousePressEvent(QMouseEvent *event)
{
    int px = event->x();
    int py = event->y();

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            int x1 = grid[i][j].x;
            int x2 = grid[i][j].x + int(round(rect_width));
            int y1 = grid[i][j].y;
            int y2 = grid[i][j].y + int(round(rect_height));
            if (px > x1 && px < x2 && py > y1 && py < y2)
                    grid[i][j].fill =  (activeEraser) ? false : true;
        }
    }
    repaint();
}

void Grid::mouseMoveEvent(QMouseEvent *event)
{
    int px = event->x();
    int py = event->y();

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            int x1 = grid[i][j].x;
            int x2 = grid[i][j].x + int(round(rect_width));
            int y1 = grid[i][j].y;
            int y2 = grid[i][j].y + int(round(rect_height));
            if (px > x1 && px < x2 && py > y1 && py < y2)
                    grid[i][j].fill =  (activeEraser) ? false : true;
        }
    }
    repaint();
}

void Grid::enableEraser(bool value) { activeEraser = value; }

QString Grid::getPicture()
{
    QString picture("");
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            picture += (grid[j][i].fill) ? "*" : ".";
        }
        if (i + 1 < cols)
            picture += "\n";
    }
    return picture;
}

void Grid::setPicture(QString picture)
{
    QStringList tokens = picture.split("\n");
    int r = tokens.size();
    int c = tokens[0].length();
    if ((r < MIN_SIZE || c < MIN_SIZE) || (r >= MAX_SIZE || c >= MAX_SIZE))
        return;

    setRows(r);
    setCols(c);

    for (int i = 0; i < tokens.size(); i++) {
        for (int j = 0; j < tokens[i].length(); j++)
            grid[j][i].fill = (tokens[i].at(j) == '*') ? true : false;
    }
    repaint();
}

void Grid::setRows(int value)
{
    rows = value;
    repaint();
}

int Grid::getRows() { return rows; }

void Grid::setCols(int value)
{
    cols = value;
    repaint();
}

int Grid::getCols() { return cols; }

bool Grid::isEraserActive() { return activeEraser; }

