#include <QApplication>
#include <QFile>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);

    const QString theme = "Dark";

    QFile   theme_file(QString(":/%1.qss").arg(theme));
    theme_file.open(QFile::ReadOnly);

    if (theme_file.isOpen()) {
        app.setStyleSheet(theme_file.readAll());
        theme_file.close();
    } else {
        qDebug("File couldn't be opened!");
    }

    MainWindow window;
    window.showMaximized();
    return QApplication::exec();
}
