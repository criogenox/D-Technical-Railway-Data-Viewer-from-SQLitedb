#include "table.h"

#include <QMainWindow>

MainDelegate::MainDelegate(int n, QObject *parent)
    : QStyledItemDelegate(parent)
      , n{n} {
}

void MainDelegate::paint(QPainter *painter,
                         const QStyleOptionViewItem &option,
                         const QModelIndex &index) const {
    const QString text = index.data(Qt::DisplayRole).toString();
    if (n == 0) {
        painter->setPen(Qt::red);
        painter->drawText(option.rect, Qt::AlignLeft | Qt::AlignVCenter, text);
    } else if (n == 1) {
        painter->drawText(option.rect, Qt::AlignRight | Qt::AlignVCenter, text);
    }
}

DynamicTableView::DynamicTableView(QWidget *parent)
    : QTableView(parent) {
}

void DynamicTableView::mousePressEvent(QMouseEvent *event) {
    const QModelIndex index = indexAt(event->pos());
    if (index.isValid() && index.column() == 1 && sw == true) {
        emit cellClicked2A(index.data().toString(), index.row());
    }
    QTableView::mousePressEvent(event);
}

TableDialog::TableDialog(const QString &tableName) {
    QGroupBox *tableBox = createBox(tableName);
    auto *gLayout = new QGridLayout();
    gLayout->addWidget(tableBox);
    setLayout(gLayout);
    setWindowTitle(tableName);
    adjustSize();
}

QGroupBox *TableDialog::createBox(const QString &tableName) {
    auto *vlayout = new QVBoxLayout(this);
    auto *table = new QGroupBox(this);
    index = new DynamicTableView(this);
    loadTable(tableName);
    vlayout->addWidget(index);
    table->setLayout(vlayout);
    return table;
}

void TableDialog::loadTable(const QString &tableName) {
    QSqlQuery query(QString("SELECT * FROM \"%1\"").arg(tableName));

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    model = new QSqlQueryModel(this);
    model->setQuery(std::move(query));

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "No Data", "No rows found in the table.");
        return;
    }

    index->setModel(model);

    index->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    index->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    index->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    index->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    index->resizeColumnsToContents();
    index->resizeRowsToContents();
    totalWidth = getTotalColumnWidth(index);
}

int TableDialog::getTotalColumnWidth(const DynamicTableView *table) {
    totalWidth = 0;
    const int columnCount0 = table->model()->columnCount();

    for (int i = 0; i < columnCount0; ++i) {
        totalWidth += table->columnWidth(i);
    }
    return totalWidth;
}
