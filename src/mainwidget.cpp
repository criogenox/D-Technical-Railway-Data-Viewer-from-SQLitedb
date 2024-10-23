#include "mainwidget.h"

#include <QGridLayout>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent) {
    const QFont font("System", 8, QFont::Bold, QFont::Condensed);
    targetScene = new QGraphicsScene(this);
    // ************************************************************
    h1Splitter = new QSplitter(this);

    CGB0 = new CustomViewGroup("View N°1", font, this);
    scene0 = CGB0->getScene();
    view0 = CGB0->getView();
    h1Splitter->addWidget(CGB0->getGroupBox());

    // ************************************************************
    CGB1 = new CustomViewGroup("View N°2", font, this);
    scene1 = CGB1->getScene();
    view1 = CGB1->getView();
    h1Splitter->addWidget(CGB1->getGroupBox());

    // ************************************************************
    h2Splitter = new QSplitter(this);

    CGB2 = new CustomViewGroup("View N°3", font, this);
    scene2 = CGB2->getScene();
    view2 = CGB2->getView();
    h2Splitter->addWidget(CGB2->getGroupBox());

    // ************************************************************
    auto *vSplitter = new QSplitter(Qt::Vertical, this);
    vSplitter->addWidget(h1Splitter);
    vSplitter->addWidget(h2Splitter);
    vSplitter->setSizes(QList<int>() << 400 << 400);

    // ************************************************************
    auto *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(vSplitter);
    mainLayout->setColumnMinimumWidth(0, 500);
    mainLayout->setRowMinimumHeight(0, 500);

    // setWindowTitle(tr(" "));

    // ************************************************************
    connect(h1Splitter, &QSplitter::splitterMoved, this, [=, this]() {
        view0->fitInView(scene0->sceneRect(), Qt::KeepAspectRatio);
        view1->fitInView(scene1->sceneRect(), Qt::KeepAspectRatio);
    });

    connect(vSplitter, &QSplitter::splitterMoved, this, [=, this]() {
        view0->fitInView(scene0->sceneRect(), Qt::KeepAspectRatio);
        view1->fitInView(scene1->sceneRect(), Qt::KeepAspectRatio);
        view2->fitInView(scene2->sceneRect(), Qt::KeepAspectRatio);
    });
}
