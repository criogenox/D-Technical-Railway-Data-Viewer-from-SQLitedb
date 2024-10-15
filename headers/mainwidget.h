#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QSplitter>
#include <QWidget>

#include "customviewgroup.h"

class MainWidget : public QWidget {
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);

    QGraphicsScene *scene0;
    QGraphicsScene *scene1;
    QGraphicsScene *scene2;
    Mouse *view0;
    Mouse *view1;
    Mouse *view2;
    QGraphicsScene *targetScene;

private:
    QSplitter *h1Splitter;
    QSplitter *h2Splitter;
    CustomViewGroup *CGB0;
    CustomViewGroup *CGB1;
    CustomViewGroup *CGB2;
};

#endif // MAINWIDGET_H
