#include "mouse.h"

#include "qscrollbar.h"

Mouse::Mouse(QWidget *parent)
    : QGraphicsView(parent) {
}

void Mouse::wheelEvent(QWheelEvent *event) {
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::SmoothPixmapTransform);

    event->accept();

    verticalScrollBar()->setDisabled(true);
    const ViewportAnchor anchor = transformationAnchor();
    setTransformationAnchor(AnchorUnderMouse);

    const int angle = event->angleDelta().y();
    const qreal factor = (angle > 0) ? 1.1 : 0.9;
    scale(factor, factor);
    setTransformationAnchor(anchor);
}

void Mouse::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastMousePosition = event->pos();
        setDragMode(ScrollHandDrag);
    }
    QGraphicsView::mousePressEvent(event);
}

void Mouse::mouseMoveEvent(QMouseEvent *event) {
    if (dragMode() == ScrollHandDrag) {
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() -
                                        (event->pos().x() - lastMousePosition.x()));
        verticalScrollBar()->setValue(verticalScrollBar()->value() -
                                      (event->pos().y() - lastMousePosition.y()));
        lastMousePosition = event->pos();
    }
    QGraphicsView::mouseMoveEvent(event);
}

void Mouse::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        setDragMode(NoDrag);
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void Mouse::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        fitInView(sceneRect(), Qt::KeepAspectRatio);
    }
    QGraphicsView::mouseDoubleClickEvent(event);
}
