/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *l_dialogTitle;
    QLabel *label_1;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_2;

    void setupUi(QDialog *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName("About");
        About->resize(400, 300);
        verticalLayout = new QVBoxLayout(About);
        verticalLayout->setObjectName("verticalLayout");
        l_dialogTitle = new QLabel(About);
        l_dialogTitle->setObjectName("l_dialogTitle");
        l_dialogTitle->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(l_dialogTitle);

        label_1 = new QLabel(About);
        label_1->setObjectName("label_1");
        label_1->setAlignment(Qt::AlignCenter);
        label_1->setWordWrap(true);

        verticalLayout->addWidget(label_1);

        label_4 = new QLabel(About);
        label_4->setObjectName("label_4");
        label_4->setAlignment(Qt::AlignCenter);
        label_4->setOpenExternalLinks(true);

        verticalLayout->addWidget(label_4);

        label_3 = new QLabel(About);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignCenter);
        label_3->setWordWrap(true);

        verticalLayout->addWidget(label_3);

        label_2 = new QLabel(About);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);


        retranslateUi(About);

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QDialog *About)
    {
        About->setWindowTitle(QCoreApplication::translate("About", "Dialog", nullptr));
        l_dialogTitle->setText(QCoreApplication::translate("About", "Green Lion Racing Database", nullptr));
        label_1->setText(QCoreApplication::translate("About", "Dieses Programm wurde zun\303\244chst erstellt um Sponsoring Interaktionen und Aktivit\303\244ten geeignet speichern zu k\303\266nnen, sp\303\244ter wurde es ausgeweitet um auch allgemeine Teamdaten zu speichern.", nullptr));
        label_4->setText(QCoreApplication::translate("About", "<html><head/><body><p><a href=\"https://github.com/green-lion-racing/glr-database\"><span style=\" text-decoration: underline; color:#007af4;\">https://github.com/green-lion-racing/glr-database</span></a></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("About", "Erstellt von Tobias Haus & Alexander Wallrodt", nullptr));
        label_2->setText(QCoreApplication::translate("About", "\302\251 2020 - 2024", nullptr));
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
