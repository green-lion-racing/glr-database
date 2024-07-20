/********************************************************************************
** Form generated from reading UI file 'error.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERROR_H
#define UI_ERROR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Error
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *l_error;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pb_okay;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *Error)
    {
        if (Error->objectName().isEmpty())
            Error->setObjectName("Error");
        Error->resize(317, 133);
        Error->setSizeGripEnabled(false);
        verticalLayout = new QVBoxLayout(Error);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(Error);
        label->setObjectName("label");
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        l_error = new QLabel(Error);
        l_error->setObjectName("l_error");
        l_error->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(l_error);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pb_okay = new QPushButton(Error);
        pb_okay->setObjectName("pb_okay");

        horizontalLayout->addWidget(pb_okay);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Error);

        QMetaObject::connectSlotsByName(Error);
    } // setupUi

    void retranslateUi(QDialog *Error)
    {
        Error->setWindowTitle(QCoreApplication::translate("Error", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Error", "\303\204nderungen konnten nicht \303\274bernommen werden!", nullptr));
        l_error->setText(QCoreApplication::translate("Error", "Fehler", nullptr));
        pb_okay->setText(QCoreApplication::translate("Error", "Okay", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Error: public Ui_Error {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERROR_H
