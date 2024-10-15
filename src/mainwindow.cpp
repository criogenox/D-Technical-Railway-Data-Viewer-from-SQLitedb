#include "mainwindow.h"

#include <QGraphicsItem>
#include <QMenuBar>

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent) {
    auto *menuBar = new QMenuBar(this);
    QMenu *fileMenu = menuBar->addMenu("File");
    QMenu *viewMenu = menuBar->addMenu(tr("&View"));
    QMenu *helpMenu = menuBar->addMenu(tr("&Help"));
    setMenuBar(menuBar);

    auto *loadImageAction = new QAction("Load Image", this);
    connect(loadImageAction, &QAction::triggered, this, &MainWindow::loadImage);
    auto *loadDbAction = new QAction("Select Database", this);
    connect(loadDbAction, &QAction::triggered, this, &MainWindow::loadDatabase);
    auto *viewIndexAct = new QAction(tr("Show Index"), this);
    connect(viewIndexAct, &QAction::triggered, this, &MainWindow::showIndex);
    auto *showLastClosedDockAction = new QAction("Show Last Closed Dock", this);
    connect(showLastClosedDockAction, &QAction::triggered, this, &MainWindow::showLastClosedDock);
    auto *closeAllDocksAction = new QAction("Close All Docks", this);
    connect(closeAllDocksAction, &QAction::triggered, this, &MainWindow::closeDocks);
    auto *aboutQtAct = new QAction(tr("About App"), this);
    connect(aboutQtAct, &QAction::triggered, this, &MainWindow::showAbout);

    fileMenu->addAction(loadImageAction);
    fileMenu->addAction(loadDbAction);
    viewMenu->addAction(viewIndexAct);
    viewMenu->addAction(showLastClosedDockAction);
    viewMenu->addAction(closeAllDocksAction);
    helpMenu->addAction(aboutQtAct);

    auto *exitAction = new QAction("Exit", this);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(exitAction);

    delegateindex = new MainDelegate(0, this);
    showAll = false;
    mainwidget = new MainWidget(this);
    setCentralWidget(mainwidget);
}

MainWindow::~MainWindow() {
    delete tableDialog;
    qDeleteAll(dockList);
    dockList.clear();
    qDeleteAll(closedDocks);
    closedDocks.clear();
    db.close();
}

void MainWindow::loadDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    const QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select Database File",
        "",
        "Database Files (*.db *.sqlite *.sql);;All Files (*)" // Filter for database files
    );

    // Check if a file was selected
    if (!filePath.isEmpty()) {
        db.setDatabaseName(filePath);
    }

    if (!db.open()) {
        QMessageBox::critical(nullptr, "Database Error", db.lastError().text());
        return;
    }

    tableName = "80.001A1.2.2";
}

void MainWindow::addDock(const QString &tableName) {
    idx = false;
    for (const CustomDock *dock: dockList) {
        if (dock->objectName() == tableName) {
            // qDebug() << "Dock with the same name is already open: " << tableName;
            idx = true;
            return;
        }
    }

    for (CustomDock *dock: closedDocks) {
        if (dock->objectName() == tableName) {
            // qDebug() << "Dock with the same name is already created, moving it: " << tableName;
            closedDocks.removeOne(dock);
            dockList.append(dock);
            closedDockPositions.removeOne(dock->geometry());
            dock->show();
            return;
        } else {
            idx = false;
        }
    }

    if (!idx) {
        auto *dock = new CustomDock(tableName);
        dock->setObjectName(tableName);
        auto *data = new QGroupBox(dock);
        auto *layoutData = new QVBoxLayout();
        textEdit = new QTextEdit(dock);
        layoutData->addWidget(textEdit);
        data->setLayout(layoutData);
        dock->setWidget(data);
        dock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable |
                          QDockWidget::DockWidgetClosable);

        addDockWidget(Qt::RightDockWidgetArea, dock);

        if (!dockList.isEmpty()) {
            tabifyDockWidget(dockList.last(), dock);
        }

        dockList.append(dock);

        connect(dock, &CustomDock::closed, this, [this, dock]() {
            dockList.removeOne(dock);
            closedDocks.append(dock);
            closedDockPositions.append(dock->geometry());
        });

        connect(dock, &CustomDock::dockResized, this, &MainWindow::updateViewSize);
    }
}

void MainWindow::closeDocks() {
    for (QDockWidget *dock: dockList) {
        dock->close();
    }
}

void MainWindow::showLastClosedDock() {
    if (!closedDocks.isEmpty()) {
        CustomDock *lastClosedDock = closedDocks.takeLast();
        lastClosedDock->setGeometry(closedDockPositions.takeLast());
        lastClosedDock->show();
        dockList.append(lastClosedDock);
    }
}

void MainWindow::closeEvent(QCloseEvent *event [[maybe_unused]]) {
    QApplication::closeAllWindows();
}

void MainWindow::loadImage() {
    // QString fileName =
    //     QFileDialog::getOpenFileName(this,
    //                                  tr("Open Image"),
    //                                  "",
    //                                  tr("Images (*.png *.jpg *.jpeg *.bmp *.gif *.svg)"));

    // if (!fileName.isEmpty()) {
    //     QString fileExtension = QFileInfo(fileName).suffix().toLower();

    //     if (fileExtension == "svg") {
    //         QGraphicsSvgItem *svgItem = new QGraphicsSvgItem(fileName);
    //         mainwidget->scene->clear();
    //         mainwidget->scene->addItem(svgItem);
    //         mainwidget->scene->setSceneRect(svgItem->boundingRect());
    //     } else {
    //         QImage image(fileName);
    //         if (image.isNull()) {
    //             qDebug() << "Failed to load image:" << fileName;
    //             return;
    //         }

    //         QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    //         mainwidget->scene->clear();
    //         mainwidget->scene->addItem(item);
    //         mainwidget->scene->setSceneRect(item->boundingRect());
    //     }
    //     updateViewSize();
    // }
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    updateViewSize();
}

void MainWindow::updateViewSize() const {
    if (mainwidget->view0 && mainwidget->view1 && mainwidget->view2) {
        mainwidget->view0->fitInView(mainwidget->scene0->sceneRect(), Qt::KeepAspectRatio);
        mainwidget->view1->fitInView(mainwidget->scene1->sceneRect(), Qt::KeepAspectRatio);
        mainwidget->view2->fitInView(mainwidget->scene2->sceneRect(), Qt::KeepAspectRatio);
    }
}

void MainWindow::showAbout() {
    const QString aboutText =
            "<h2 style='color: darkgrey; text-decoration: underline; text-align: center;'>"
            "Database Technical Info Viewer</h2>"

            "<p style='font-size: 14px; font-weight: bold; text-align: left;'>"
            "Description:</p>"

            "<p style='text-align: justify; text-indent: 85px;'>"
            "This application provides a comprehensive graphical interface for managing "
            "and visualizing data from a dynamic sql table through customizable dockable windows.</p>"

            "<p style='font-size: 12px; font-style: italic; text-align: center;'>"
            "Version: 0.9</p>"

            "<p style='font-size: 14px; font-weight: bold; text-align: left;'>"
            "Key Features:</p>"

            "<ul style='text-align: justify;'>"
            "<li>Image viewing: display formats with zoom and pan capabilities.</li>"
            "<li>Dock management: create, close, and restore dock windows on demand.</li>"
            "<li>Data interaction: manipulate data directly from a SQLite database.</li>"
            "<li>Clean GUI: responsive layout adapting to multiple resize events.</li>"
            "</ul>"

            "<p style='text-align: right'>"
            "Developed by: Criogenox</p>";

    QMessageBox::about(this, "About", aboutText);
}

void MainWindow::showIndex() {
    tableDialog = new TableDialog(tableName);
    tableDialog->setWindowFlags(Qt::WindowStaysOnTopHint);

    if (tableName == "80.001A1.2.2") {
        tableDialog->index->sw = true;
        tableDialog->index->setItemDelegateForColumn(1, nullptr);
        tableDialog->index->setItemDelegateForColumn(1, delegateindex);
    }

    tableDialog->setWindowModality(Qt::NonModal);
    tableDialog->resize(static_cast<int>(tableDialog->totalWidth * 1.23), 300);
    tableDialog->setMaximumWidth(static_cast<int>(tableDialog->totalWidth * 1.23));
    tableDialog->setMinimumWidth(static_cast<int>(tableDialog->totalWidth * 1.23));
    tableDialog->raise();
    // **************
    if (!db.open()) {
        return;
    }
    // **************
    tableDialog->show();

    connect(tableDialog->index,
            &DynamicTableView::cellClicked2A,
            this,
            &MainWindow::fetchDataFromDatabase);
}

void MainWindow::fetchDataFromDatabase(const QString &tableName) {
    const QString countQueryStr = QString("SELECT COUNT(*) FROM \"%1\"").arg(tableName);
    QSqlQuery countQuery(countQueryStr);

    if (!countQuery.exec() || !countQuery.next()) {
        QMessageBox::critical(this, "Database Error", countQuery.lastError().text());
        return;
    }

    const int rowCount = countQuery.value(0).toInt();
    closeDocks();

    const QString queryStr = QString("SELECT * FROM \"%1\"").arg(tableName);
    QSqlQuery query(queryStr);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    for (int i = 0; i < rowCount; ++i) {
        if (query.next()) {
            QString text = query.value(0).toString();
            QByteArray imageData = query.value(1).toByteArray();

            addDock(tableName + QString::number(i));

            if (!dockList.isEmpty()) {
                auto *textEdit = qobject_cast<QTextEdit *>(
                    dockList.last()->widget()->findChild<QTextEdit *>());
                if (textEdit) {
                    textEdit->setText(text);
                    textEdit->setAlignment(Qt::AlignJustify);
                    textEdit->setReadOnly(true);
                }
            }

            if (!imageData.isEmpty()) {
                QImage image;
                image.loadFromData(imageData);
                showSelectedImage(i, image);
            }
        }
    }
}

void MainWindow::showSelectedImage(const int rowIndex, const QImage &image) const {
    switch (rowIndex) {
        case 1:
            mainwidget->targetScene = mainwidget->scene0;
            break;
        case 2:
            mainwidget->targetScene = mainwidget->scene1;
            break;
        case 3:
            mainwidget->targetScene = mainwidget->scene2;
            break;
        default:
            return;
    }

    if (mainwidget->targetScene) {
        auto *item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
        mainwidget->targetScene->clear();
        mainwidget->targetScene->addItem(item);
        mainwidget->targetScene->setSceneRect(item->boundingRect());
        updateViewSize();
    }
}
