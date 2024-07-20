/********************************************************************************
** Form generated from reading UI file 'tables.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLES_H
#define UI_TABLES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tables
{
public:
    QWidget *centralwidget_display_tables;
    QVBoxLayout *verticalLayout;
    QLabel *l_dialogTitle;
    QComboBox *cb_table;
    QTableView *tv_table;
    QHBoxLayout *horizontalLayout;
    QCheckBox *cb_editMode;
    QPushButton *pb_save;

    void setupUi(QMainWindow *Tables)
    {
        if (Tables->objectName().isEmpty())
            Tables->setObjectName("Tables");
        Tables->resize(753, 454);
        centralwidget_display_tables = new QWidget(Tables);
        centralwidget_display_tables->setObjectName("centralwidget_display_tables");
        verticalLayout = new QVBoxLayout(centralwidget_display_tables);
        verticalLayout->setObjectName("verticalLayout");
        l_dialogTitle = new QLabel(centralwidget_display_tables);
        l_dialogTitle->setObjectName("l_dialogTitle");

        verticalLayout->addWidget(l_dialogTitle);

        cb_table = new QComboBox(centralwidget_display_tables);
        cb_table->setObjectName("cb_table");

        verticalLayout->addWidget(cb_table);

        tv_table = new QTableView(centralwidget_display_tables);
        tv_table->setObjectName("tv_table");

        verticalLayout->addWidget(tv_table);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, -1, -1, -1);
        cb_editMode = new QCheckBox(centralwidget_display_tables);
        cb_editMode->setObjectName("cb_editMode");
        cb_editMode->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout->addWidget(cb_editMode);

        pb_save = new QPushButton(centralwidget_display_tables);
        pb_save->setObjectName("pb_save");
        QSizePolicy sizePolicy(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pb_save->sizePolicy().hasHeightForWidth());
        pb_save->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pb_save);


        verticalLayout->addLayout(horizontalLayout);

        Tables->setCentralWidget(centralwidget_display_tables);
        QWidget::setTabOrder(cb_table, tv_table);
        QWidget::setTabOrder(tv_table, pb_save);
        QWidget::setTabOrder(pb_save, cb_editMode);

        retranslateUi(Tables);

        QMetaObject::connectSlotsByName(Tables);
    } // setupUi

    void retranslateUi(QMainWindow *Tables)
    {
        Tables->setWindowTitle(QCoreApplication::translate("Tables", "Dialog", nullptr));
        l_dialogTitle->setText(QCoreApplication::translate("Tables", "Tabellen ansehen", nullptr));
        cb_table->setPlaceholderText(QCoreApplication::translate("Tables", "Tabellen...", nullptr));
        cb_editMode->setText(QCoreApplication::translate("Tables", "Bearbeitung aktivieren", nullptr));
        pb_save->setText(QCoreApplication::translate("Tables", "\303\204nderungen speichern", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Tables: public Ui_Tables {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLES_H
