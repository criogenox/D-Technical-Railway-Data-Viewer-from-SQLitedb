#ifndef CUSTOMDOCK_H
#define CUSTOMDOCK_H

#include <QCloseEvent>
#include <QDockWidget>

class CustomDock final : public QDockWidget {
    Q_OBJECT

public:
    explicit CustomDock(const QString &title = "", QWidget *parent = nullptr)
        : QDockWidget(title, parent) {
    }

protected:
    void closeEvent(QCloseEvent *event) override {
        emit closed();
        QDockWidget::closeEvent(event);
    }

    void resizeEvent(QResizeEvent *event) override {
        QDockWidget::resizeEvent(event);
        emit dockResized(event->size());
    }

signals:
    void closed();

    void dockResized(QSize newSize);
};

#endif // CUSTOMDOCK_H
