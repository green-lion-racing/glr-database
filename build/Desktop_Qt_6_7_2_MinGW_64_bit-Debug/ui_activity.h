/********************************************************************************
** Form generated from reading UI file 'activity.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACTIVITY_H
#define UI_ACTIVITY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Activity
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *l_dialogTitle;
    QFormLayout *formLayout;
    QLabel *label_1;
    QComboBox *cb_company;
    QLabel *label_6;
    QComboBox *cb_person;
    QLabel *label_2;
    QLineEdit *le_when;
    QLabel *label_3;
    QLineEdit *le_value;
    QLabel *label_4;
    QLineEdit *le_what;
    QLabel *label_5;
    QTextEdit *te_info;
    QCalendarWidget *cw_calender;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pb_okay;
    QLabel *label_7;
    QComboBox *cb_activity;

    void setupUi(QDialog *Activity)
    {
        if (Activity->objectName().isEmpty())
            Activity->setObjectName("Activity");
        Activity->resize(495, 493);
        verticalLayout = new QVBoxLayout(Activity);
        verticalLayout->setObjectName("verticalLayout");
        l_dialogTitle = new QLabel(Activity);
        l_dialogTitle->setObjectName("l_dialogTitle");

        verticalLayout->addWidget(l_dialogTitle);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(-1, -1, 100, -1);
        label_1 = new QLabel(Activity);
        label_1->setObjectName("label_1");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_1);

        cb_company = new QComboBox(Activity);
        cb_company->setObjectName("cb_company");

        formLayout->setWidget(1, QFormLayout::FieldRole, cb_company);

        label_6 = new QLabel(Activity);
        label_6->setObjectName("label_6");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_6);

        cb_person = new QComboBox(Activity);
        cb_person->setObjectName("cb_person");

        formLayout->setWidget(2, QFormLayout::FieldRole, cb_person);

        label_2 = new QLabel(Activity);
        label_2->setObjectName("label_2");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_2);

        le_when = new QLineEdit(Activity);
        le_when->setObjectName("le_when");
        le_when->setReadOnly(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, le_when);

        label_3 = new QLabel(Activity);
        label_3->setObjectName("label_3");

        formLayout->setWidget(5, QFormLayout::LabelRole, label_3);

        le_value = new QLineEdit(Activity);
        le_value->setObjectName("le_value");

        formLayout->setWidget(5, QFormLayout::FieldRole, le_value);

        label_4 = new QLabel(Activity);
        label_4->setObjectName("label_4");

        formLayout->setWidget(6, QFormLayout::LabelRole, label_4);

        le_what = new QLineEdit(Activity);
        le_what->setObjectName("le_what");

        formLayout->setWidget(6, QFormLayout::FieldRole, le_what);

        label_5 = new QLabel(Activity);
        label_5->setObjectName("label_5");

        formLayout->setWidget(7, QFormLayout::LabelRole, label_5);

        te_info = new QTextEdit(Activity);
        te_info->setObjectName("te_info");

        formLayout->setWidget(7, QFormLayout::FieldRole, te_info);

        cw_calender = new QCalendarWidget(Activity);
        cw_calender->setObjectName("cw_calender");
        cw_calender->setGridVisible(false);
        cw_calender->setNavigationBarVisible(true);
        cw_calender->setDateEditEnabled(true);

        formLayout->setWidget(4, QFormLayout::FieldRole, cw_calender);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pb_okay = new QPushButton(Activity);
        pb_okay->setObjectName("pb_okay");

        horizontalLayout_2->addWidget(pb_okay);


        formLayout->setLayout(8, QFormLayout::FieldRole, horizontalLayout_2);

        label_7 = new QLabel(Activity);
        label_7->setObjectName("label_7");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_7);

        cb_activity = new QComboBox(Activity);
        cb_activity->setObjectName("cb_activity");

        formLayout->setWidget(0, QFormLayout::FieldRole, cb_activity);


        verticalLayout->addLayout(formLayout);

        QWidget::setTabOrder(cb_activity, cb_company);
        QWidget::setTabOrder(cb_company, cb_person);
        QWidget::setTabOrder(cb_person, le_when);
        QWidget::setTabOrder(le_when, cw_calender);
        QWidget::setTabOrder(cw_calender, le_value);
        QWidget::setTabOrder(le_value, le_what);
        QWidget::setTabOrder(le_what, te_info);
        QWidget::setTabOrder(te_info, pb_okay);

        retranslateUi(Activity);

        QMetaObject::connectSlotsByName(Activity);
    } // setupUi

    void retranslateUi(QDialog *Activity)
    {
        Activity->setWindowTitle(QCoreApplication::translate("Activity", "Dialog", nullptr));
        l_dialogTitle->setText(QCoreApplication::translate("Activity", "Leistung hinzuf\303\274gen", nullptr));
        label_1->setText(QCoreApplication::translate("Activity", "Unternehmen", nullptr));
        cb_company->setPlaceholderText(QCoreApplication::translate("Activity", "Unternehmen...", nullptr));
        label_6->setText(QCoreApplication::translate("Activity", "Ansprechpartner", nullptr));
        cb_person->setPlaceholderText(QCoreApplication::translate("Activity", "Ansprechpartner...", nullptr));
        label_2->setText(QCoreApplication::translate("Activity", "Wann", nullptr));
        label_3->setText(QCoreApplication::translate("Activity", "Wert", nullptr));
        label_4->setText(QCoreApplication::translate("Activity", "Was", nullptr));
        label_5->setText(QCoreApplication::translate("Activity", "Infos", nullptr));
        pb_okay->setText(QCoreApplication::translate("Activity", "Okay", nullptr));
        label_7->setText(QCoreApplication::translate("Activity", "Leistungen", nullptr));
        cb_activity->setPlaceholderText(QCoreApplication::translate("Activity", "Leistungen...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Activity: public Ui_Activity {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACTIVITY_H
