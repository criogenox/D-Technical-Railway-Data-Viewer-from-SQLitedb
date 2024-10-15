#ifndef CUSTOMVIEWGROUP_H
#define CUSTOMVIEWGROUP_H

#include <QGroupBox>
#include <QLabel>

#include "mouse.h"

class CustomViewGroup {
public:
    CustomViewGroup(const QString &title, const QFont &font, QWidget *parent = nullptr);

    [[nodiscard]] auto getGroupBox() const -> QGroupBox *;

    [[nodiscard]] auto getScene() const -> QGraphicsScene *;

    [[nodiscard]] auto getView() const -> Mouse *;

private:
    QGroupBox *groupBox;
    QGraphicsScene *scene;
    Mouse *view;
};
#endif // CUSTOMVIEWGROUP_H
