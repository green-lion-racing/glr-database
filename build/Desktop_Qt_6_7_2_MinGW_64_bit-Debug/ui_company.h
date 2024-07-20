/********************************************************************************
** Form generated from reading UI file 'company.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPANY_H
#define UI_COMPANY_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Company
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *l_dialogTitle;
    QFormLayout *formLayout;
    QLabel *label_11;
    QComboBox *cb_company;
    QLabel *label_1;
    QLineEdit *le_name;
    QLabel *label_6;
    QLineEdit *le_info;
    QLabel *label_2;
    QLineEdit *le_address;
    QLabel *label_12;
    QHBoxLayout *hl_changes;
    QListWidget *lw_changes;
    QVBoxLayout *verticalLayout_3;
    QToolButton *tb_add;
    QToolButton *tb_remove;
    QSpacerItem *verticalSpacer;
    QLineEdit *le_since;
    QLineEdit *le_until;
    QLabel *label_13;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *rb_gold;
    QRadioButton *rb_silver;
    QRadioButton *rb_bronze;
    QRadioButton *rb_supporter;
    QLabel *label_5;
    QLineEdit *le_typ;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pb_okay;
    QLabel *label_4;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_2;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *Company)
    {
        if (Company->objectName().isEmpty())
            Company->setObjectName("Company");
        Company->resize(495, 392);
        verticalLayout = new QVBoxLayout(Company);
        verticalLayout->setObjectName("verticalLayout");
        l_dialogTitle = new QLabel(Company);
        l_dialogTitle->setObjectName("l_dialogTitle");

        verticalLayout->addWidget(l_dialogTitle);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(-1, -1, 100, -1);
        label_11 = new QLabel(Company);
        label_11->setObjectName("label_11");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_11);

        cb_company = new QComboBox(Company);
        cb_company->setObjectName("cb_company");

        formLayout->setWidget(0, QFormLayout::FieldRole, cb_company);

        label_1 = new QLabel(Company);
        label_1->setObjectName("label_1");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_1);

        le_name = new QLineEdit(Company);
        le_name->setObjectName("le_name");

        formLayout->setWidget(1, QFormLayout::FieldRole, le_name);

        label_6 = new QLabel(Company);
        label_6->setObjectName("label_6");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_6);

        le_info = new QLineEdit(Company);
        le_info->setObjectName("le_info");

        formLayout->setWidget(2, QFormLayout::FieldRole, le_info);

        label_2 = new QLabel(Company);
        label_2->setObjectName("label_2");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_2);

        le_address = new QLineEdit(Company);
        le_address->setObjectName("le_address");

        formLayout->setWidget(3, QFormLayout::FieldRole, le_address);

        label_12 = new QLabel(Company);
        label_12->setObjectName("label_12");

        formLayout->setWidget(4, QFormLayout::LabelRole, label_12);

        hl_changes = new QHBoxLayout();
        hl_changes->setSpacing(0);
        hl_changes->setObjectName("hl_changes");
        hl_changes->setSizeConstraint(QLayout::SetMinimumSize);
        lw_changes = new QListWidget(Company);
        lw_changes->setObjectName("lw_changes");

        hl_changes->addWidget(lw_changes);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout_3->setContentsMargins(-1, 0, 0, -1);
        tb_add = new QToolButton(Company);
        tb_add->setObjectName("tb_add");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/icon_add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        tb_add->setIcon(icon);

        verticalLayout_3->addWidget(tb_add);

        tb_remove = new QToolButton(Company);
        tb_remove->setObjectName("tb_remove");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/icon_remove.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        tb_remove->setIcon(icon1);

        verticalLayout_3->addWidget(tb_remove);

        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        hl_changes->addLayout(verticalLayout_3);


        formLayout->setLayout(4, QFormLayout::FieldRole, hl_changes);

        le_since = new QLineEdit(Company);
        le_since->setObjectName("le_since");

        formLayout->setWidget(5, QFormLayout::FieldRole, le_since);

        le_until = new QLineEdit(Company);
        le_until->setObjectName("le_until");

        formLayout->setWidget(6, QFormLayout::FieldRole, le_until);

        label_13 = new QLabel(Company);
        label_13->setObjectName("label_13");

        formLayout->setWidget(7, QFormLayout::LabelRole, label_13);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        rb_gold = new QRadioButton(Company);
        buttonGroup = new QButtonGroup(Company);
        buttonGroup->setObjectName("buttonGroup");
        buttonGroup->addButton(rb_gold);
        rb_gold->setObjectName("rb_gold");

        horizontalLayout_3->addWidget(rb_gold);

        rb_silver = new QRadioButton(Company);
        buttonGroup->addButton(rb_silver);
        rb_silver->setObjectName("rb_silver");

        horizontalLayout_3->addWidget(rb_silver);

        rb_bronze = new QRadioButton(Company);
        buttonGroup->addButton(rb_bronze);
        rb_bronze->setObjectName("rb_bronze");

        horizontalLayout_3->addWidget(rb_bronze);

        rb_supporter = new QRadioButton(Company);
        buttonGroup->addButton(rb_supporter);
        rb_supporter->setObjectName("rb_supporter");

        horizontalLayout_3->addWidget(rb_supporter);


        formLayout->setLayout(7, QFormLayout::FieldRole, horizontalLayout_3);

        label_5 = new QLabel(Company);
        label_5->setObjectName("label_5");

        formLayout->setWidget(8, QFormLayout::LabelRole, label_5);

        le_typ = new QLineEdit(Company);
        le_typ->setObjectName("le_typ");

        formLayout->setWidget(8, QFormLayout::FieldRole, le_typ);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pb_okay = new QPushButton(Company);
        pb_okay->setObjectName("pb_okay");

        horizontalLayout->addWidget(pb_okay);


        formLayout->setLayout(9, QFormLayout::FieldRole, horizontalLayout);

        label_4 = new QLabel(Company);
        label_4->setObjectName("label_4");

        formLayout->setWidget(6, QFormLayout::LabelRole, label_4);

        label_3 = new QLabel(Company);
        label_3->setObjectName("label_3");

        formLayout->setWidget(5, QFormLayout::LabelRole, label_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        formLayout->setItem(10, QFormLayout::FieldRole, verticalSpacer_2);


        verticalLayout->addLayout(formLayout);

        QWidget::setTabOrder(cb_company, le_name);
        QWidget::setTabOrder(le_name, le_info);
        QWidget::setTabOrder(le_info, le_address);
        QWidget::setTabOrder(le_address, lw_changes);
        QWidget::setTabOrder(lw_changes, tb_add);
        QWidget::setTabOrder(tb_add, tb_remove);
        QWidget::setTabOrder(tb_remove, le_since);
        QWidget::setTabOrder(le_since, le_until);
        QWidget::setTabOrder(le_until, rb_gold);
        QWidget::setTabOrder(rb_gold, rb_silver);
        QWidget::setTabOrder(rb_silver, rb_bronze);
        QWidget::setTabOrder(rb_bronze, rb_supporter);
        QWidget::setTabOrder(rb_supporter, le_typ);
        QWidget::setTabOrder(le_typ, pb_okay);

        retranslateUi(Company);

        QMetaObject::connectSlotsByName(Company);
    } // setupUi

    void retranslateUi(QDialog *Company)
    {
        Company->setWindowTitle(QCoreApplication::translate("Company", "Dialog", nullptr));
        l_dialogTitle->setText(QCoreApplication::translate("Company", "Unternehmen hinzuf\303\274gen", nullptr));
        label_11->setText(QCoreApplication::translate("Company", "Unternehmen", nullptr));
        cb_company->setPlaceholderText(QCoreApplication::translate("Company", "Unternehmen...", nullptr));
        label_1->setText(QCoreApplication::translate("Company", "Firmenname", nullptr));
        label_6->setText(QCoreApplication::translate("Company", "Infos", nullptr));
        label_2->setText(QCoreApplication::translate("Company", "Anschrift", nullptr));
        label_12->setText(QCoreApplication::translate("Company", "Verlauf", nullptr));
#if QT_CONFIG(tooltip)
        tb_add->setToolTip(QCoreApplication::translate("Company", "Verlaufsangabe hinzuf\303\274gen.", nullptr));
#endif // QT_CONFIG(tooltip)
        tb_add->setText(QString());
#if QT_CONFIG(tooltip)
        tb_remove->setToolTip(QCoreApplication::translate("Company", "Verlaufsangabe entfernen.", nullptr));
#endif // QT_CONFIG(tooltip)
        tb_remove->setText(QString());
        label_13->setText(QCoreApplication::translate("Company", "Rang", nullptr));
        rb_gold->setText(QCoreApplication::translate("Company", "Gold", nullptr));
        rb_silver->setText(QCoreApplication::translate("Company", "Silber", nullptr));
        rb_bronze->setText(QCoreApplication::translate("Company", "Bronze", nullptr));
        rb_supporter->setText(QCoreApplication::translate("Company", "Supporter", nullptr));
        label_5->setText(QCoreApplication::translate("Company", "Leistungstyp", nullptr));
        pb_okay->setText(QCoreApplication::translate("Company", "Okay", nullptr));
        label_4->setText(QCoreApplication::translate("Company", "Bis", nullptr));
        label_3->setText(QCoreApplication::translate("Company", "Seit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Company: public Ui_Company {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPANY_H
