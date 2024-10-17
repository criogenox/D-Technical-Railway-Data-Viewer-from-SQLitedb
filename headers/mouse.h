#ifndef MOUSE_H
#define MOUSE_H

#include <QGraphicsView>
#include <QWheelEvent>

class Mouse final : public QGraphicsView {
    Q_OBJECT

public:
    explicit Mouse(QWidget *parent = nullptr);

protected:
    void wheelEvent(QWheelEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QPoint lastMousePosition;
};

#endif // MOUSE_H
