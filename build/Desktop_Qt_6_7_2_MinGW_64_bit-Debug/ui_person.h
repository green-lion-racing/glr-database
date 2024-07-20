/********************************************************************************
** Form generated from reading UI file 'person.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERSON_H
#define UI_PERSON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Person
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *l_dialogTitle;
    QFormLayout *formLayout;
    QLabel *label_11;
    QComboBox *cb_person;
    QLabel *label_1;
    QComboBox *cb_company;
    QLabel *label_8;
    QLineEdit *le_title;
    QLabel *label_2;
    QLineEdit *le_first_name;
    QLabel *label_3;
    QLineEdit *le_surname;
    QLineEdit *le_phone;
    QLabel *label_4;
    QLineEdit *le_position;
    QLabel *label_10;
    QLineEdit *le_email;
    QLabel *label_6;
    QLabel *label_7;
    QComboBox *cb_you;
    QLabel *label_9;
    QLineEdit *le_language;
    QCheckBox *cb_active;
    QLabel *label_12;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pb_okay;

    void setupUi(QDialog *Person)
    {
        if (Person->objectName().isEmpty())
            Person->setObjectName("Person");
        Person->resize(495, 390);
        verticalLayout = new QVBoxLayout(Person);
        verticalLayout->setObjectName("verticalLayout");
        l_dialogTitle = new QLabel(Person);
        l_dialogTitle->setObjectName("l_dialogTitle");

        verticalLayout->addWidget(l_dialogTitle);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(-1, -1, 100, -1);
        label_11 = new QLabel(Person);
        label_11->setObjectName("label_11");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_11);

        cb_person = new QComboBox(Person);
        cb_person->setObjectName("cb_person");

        formLayout->setWidget(0, QFormLayout::FieldRole, cb_person);

        label_1 = new QLabel(Person);
        label_1->setObjectName("label_1");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_1);

        cb_company = new QComboBox(Person);
        cb_company->setObjectName("cb_company");

        formLayout->setWidget(1, QFormLayout::FieldRole, cb_company);

        label_8 = new QLabel(Person);
        label_8->setObjectName("label_8");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_8);

        le_title = new QLineEdit(Person);
        le_title->setObjectName("le_title");

        formLayout->setWidget(2, QFormLayout::FieldRole, le_title);

        label_2 = new QLabel(Person);
        label_2->setObjectName("label_2");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_2);

        le_first_name = new QLineEdit(Person);
        le_first_name->setObjectName("le_first_name");

        formLayout->setWidget(3, QFormLayout::FieldRole, le_first_name);

        label_3 = new QLabel(Person);
        label_3->setObjectName("label_3");

        formLayout->setWidget(4, QFormLayout::LabelRole, label_3);

        le_surname = new QLineEdit(Person);
        le_surname->setObjectName("le_surname");

        formLayout->setWidget(4, QFormLayout::FieldRole, le_surname);

        le_phone = new QLineEdit(Person);
        le_phone->setObjectName("le_phone");

        formLayout->setWidget(6, QFormLayout::FieldRole, le_phone);

        label_4 = new QLabel(Person);
        label_4->setObjectName("label_4");

        formLayout->setWidget(6, QFormLayout::LabelRole, label_4);

        le_position = new QLineEdit(Person);
        le_position->setObjectName("le_position");

        formLayout->setWidget(5, QFormLayout::FieldRole, le_position);

        label_10 = new QLabel(Person);
        label_10->setObjectName("label_10");

        formLayout->setWidget(5, QFormLayout::LabelRole, label_10);

        le_email = new QLineEdit(Person);
        le_email->setObjectName("le_email");

        formLayout->setWidget(7, QFormLayout::FieldRole, le_email);

        label_6 = new QLabel(Person);
        label_6->setObjectName("label_6");

        formLayout->setWidget(7, QFormLayout::LabelRole, label_6);

        label_7 = new QLabel(Person);
        label_7->setObjectName("label_7");

        formLayout->setWidget(8, QFormLayout::LabelRole, label_7);

        cb_you = new QComboBox(Person);
        cb_you->setObjectName("cb_you");
        cb_you->setEditable(false);
        cb_you->setIconSize(QSize(16, 16));
        cb_you->setFrame(true);

        formLayout->setWidget(8, QFormLayout::FieldRole, cb_you);

        label_9 = new QLabel(Person);
        label_9->setObjectName("label_9");

        formLayout->setWidget(9, QFormLayout::LabelRole, label_9);

        le_language = new QLineEdit(Person);
        le_language->setObjectName("le_language");

        formLayout->setWidget(9, QFormLayout::FieldRole, le_language);

        cb_active = new QCheckBox(Person);
        cb_active->setObjectName("cb_active");

        formLayout->setWidget(10, QFormLayout::FieldRole, cb_active);

        label_12 = new QLabel(Person);
        label_12->setObjectName("label_12");

        formLayout->setWidget(10, QFormLayout::LabelRole, label_12);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pb_okay = new QPushButton(Person);
        pb_okay->setObjectName("pb_okay");
        pb_okay->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout->addWidget(pb_okay);


        formLayout->setLayout(11, QFormLayout::FieldRole, horizontalLayout);


        verticalLayout->addLayout(formLayout);

        QWidget::setTabOrder(cb_person, cb_company);
        QWidget::setTabOrder(cb_company, le_title);
        QWidget::setTabOrder(le_title, le_first_name);
        QWidget::setTabOrder(le_first_name, le_surname);
        QWidget::setTabOrder(le_surname, le_position);
        QWidget::setTabOrder(le_position, le_phone);
        QWidget::setTabOrder(le_phone, le_email);
        QWidget::setTabOrder(le_email, cb_you);
        QWidget::setTabOrder(cb_you, le_language);
        QWidget::setTabOrder(le_language, cb_active);
        QWidget::setTabOrder(cb_active, pb_okay);

        retranslateUi(Person);

        QMetaObject::connectSlotsByName(Person);
    } // setupUi

    void retranslateUi(QDialog *Person)
    {
        Person->setWindowTitle(QCoreApplication::translate("Person", "Dialog", nullptr));
        l_dialogTitle->setText(QCoreApplication::translate("Person", "Person hinzuf\303\274gen", nullptr));
        label_11->setText(QCoreApplication::translate("Person", "Person", nullptr));
        cb_person->setPlaceholderText(QCoreApplication::translate("Person", "Person...", nullptr));
        label_1->setText(QCoreApplication::translate("Person", "Unternehmen", nullptr));
        cb_company->setPlaceholderText(QCoreApplication::translate("Person", "Unternehmen...", nullptr));
        label_8->setText(QCoreApplication::translate("Person", "Titel", nullptr));
        label_2->setText(QCoreApplication::translate("Person", "Vorname", nullptr));
        label_3->setText(QCoreApplication::translate("Person", "Nachname", nullptr));
        label_4->setText(QCoreApplication::translate("Person", "Telefon", nullptr));
        label_10->setText(QCoreApplication::translate("Person", "Position", nullptr));
        label_6->setText(QCoreApplication::translate("Person", "E-Mail", nullptr));
        label_7->setText(QCoreApplication::translate("Person", "Du/Sie", nullptr));
        cb_you->setCurrentText(QString());
        cb_you->setPlaceholderText(QCoreApplication::translate("Person", "Anrede...", nullptr));
        label_9->setText(QCoreApplication::translate("Person", "Sprache", nullptr));
        cb_active->setText(QString());
        label_12->setText(QCoreApplication::translate("Person", "Aktiv", nullptr));
        pb_okay->setText(QCoreApplication::translate("Person", "Okay", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Person: public Ui_Person {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERSON_H
