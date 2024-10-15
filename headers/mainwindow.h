#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QList>
#include <QMainWindow>
#include <QTextEdit>

#include "customdock.h"
#include "mainwidget.h"
#include "table.h"

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QMainWindow *parent = nullptr);

    ~MainWindow() override;

    QString tableName;

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void showSelectedImage(int rowIndex, const QImage &image) const;

    void showAbout();

    static void loadImage();

    void updateViewSize() const;

    void showIndex();

    void fetchDataFromDatabase(const QString &tableName);

    void addDock(const QString &tableName);

    void closeDocks();

    void showLastClosedDock();

    void loadDatabase();

private:
    QSqlDatabase db;
    MainWidget *mainwidget;
    MainDelegate *delegateindex;
    TableDialog *tableDialog{};
    QTextEdit *textEdit{};
    QList<CustomDock *> dockList;
    QList<CustomDock *> closedDocks;
    QList<QRect> closedDockPositions;

    void closeEvent(QCloseEvent *event) override;

    bool idx{};
    bool showAll;
};
#endif // MAINWINDOW_H
