#include <QVBoxLayout>

#include "customviewgroup.h"

CustomViewGroup::CustomViewGroup(const QString &title, const QFont &font, QWidget *parent) {
    groupBox = new QGroupBox(parent);
    auto *layout = new QVBoxLayout(groupBox);

    auto *titleLabel = new QLabel(title, groupBox);
    titleLabel->setFont(font);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    scene = new QGraphicsScene(groupBox);
    view = new Mouse(groupBox);
    view->setScene(scene);

    layout->addWidget(view);
}

QGroupBox *CustomViewGroup::getGroupBox() const {
    return groupBox;
}

QGraphicsScene *CustomViewGroup::getScene() const {
    return scene;
}

Mouse *CustomViewGroup::getView() const {
    return view;
}
