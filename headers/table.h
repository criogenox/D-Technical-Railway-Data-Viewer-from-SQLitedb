#ifndef TABLE_H
#define TABLE_H

#include <QApplication>
#include <QGroupBox>
#include <QHeaderView>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QStyledItemDelegate>
#include <QTableView>
#include <QVBoxLayout>
#include <QWidget>

class MainDelegate final : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit MainDelegate(int n, QObject *parent = nullptr);

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

private:
    int n;
};

class DynamicTableView final : public QTableView {
    Q_OBJECT

public:
    explicit DynamicTableView(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event) override;

signals:
    void cellClicked2A(const QString &value, const int &id);

public:
    bool sw{};
};

class TableDialog final : public QDialog {
    Q_OBJECT

public:
    explicit TableDialog(const QString &tableName);

    DynamicTableView *index{};
    int originalWidth{};
    int totalWidth{};

private:
    QSqlQueryModel *model{};

    QGroupBox *createBox(const QString &tableName);

    void loadTable(const QString &tableName);

    int getTotalColumnWidth(const DynamicTableView *table);
};

#endif // TABLE_H
