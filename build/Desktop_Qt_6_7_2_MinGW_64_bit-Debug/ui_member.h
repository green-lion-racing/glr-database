/********************************************************************************
** Form generated from reading UI file 'member.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEMBER_H
#define UI_MEMBER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Member
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *l_dialogTitle;
    QFormLayout *formLayout;
    QLabel *label_13;
    QComboBox *cb_member;
    QLabel *label_8;
    QLineEdit *le_first_name;
    QLabel *label_2;
    QLineEdit *le_surname;
    QLabel *label_4;
    QLineEdit *le_student_number;
    QLabel *label_5;
    QLineEdit *le_email_glr;
    QLabel *label_6;
    QLineEdit *le_email_private;
    QLabel *label_10;
    QLineEdit *le_phone;
    QLabel *label_7;
    QLineEdit *le_address;
    QLabel *label_11;
    QLineEdit *le_shirt_size;
    QLabel *label_12;
    QLineEdit *le_vdi_number;
    QLabel *label_9;
    QLineEdit *le_language;
    QLabel *label_14;
    QHBoxLayout *horizontalLayout_2;
    QListWidget *lw_changes;
    QVBoxLayout *verticalLayout_3;
    QToolButton *tb_add;
    QToolButton *tb_remove;
    QSpacerItem *verticalSpacer;
    QLabel *label_15;
    QLineEdit *le_since;
    QLabel *label_16;
    QLineEdit *le_until;
    QLabel *label_3;
    QLineEdit *le_position;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pb_signature_export;
    QSpacerItem *horizontalSpacer;
    QPushButton *pb_okay;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *Member)
    {
        if (Member->objectName().isEmpty())
            Member->setObjectName("Member");
        Member->resize(495, 572);
        verticalLayout = new QVBoxLayout(Member);
        verticalLayout->setObjectName("verticalLayout");
        l_dialogTitle = new QLabel(Member);
        l_dialogTitle->setObjectName("l_dialogTitle");

        verticalLayout->addWidget(l_dialogTitle);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(-1, -1, 100, -1);
        label_13 = new QLabel(Member);
        label_13->setObjectName("label_13");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_13);

        cb_member = new QComboBox(Member);
        cb_member->setObjectName("cb_member");

        formLayout->setWidget(0, QFormLayout::FieldRole, cb_member);

        label_8 = new QLabel(Member);
        label_8->setObjectName("label_8");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_8);

        le_first_name = new QLineEdit(Member);
        le_first_name->setObjectName("le_first_name");

        formLayout->setWidget(1, QFormLayout::FieldRole, le_first_name);

        label_2 = new QLabel(Member);
        label_2->setObjectName("label_2");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        le_surname = new QLineEdit(Member);
        le_surname->setObjectName("le_surname");

        formLayout->setWidget(2, QFormLayout::FieldRole, le_surname);

        label_4 = new QLabel(Member);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        le_student_number = new QLineEdit(Member);
        le_student_number->setObjectName("le_student_number");

        formLayout->setWidget(3, QFormLayout::FieldRole, le_student_number);

        label_5 = new QLabel(Member);
        label_5->setObjectName("label_5");

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        le_email_glr = new QLineEdit(Member);
        le_email_glr->setObjectName("le_email_glr");

        formLayout->setWidget(4, QFormLayout::FieldRole, le_email_glr);

        label_6 = new QLabel(Member);
        label_6->setObjectName("label_6");

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        le_email_private = new QLineEdit(Member);
        le_email_private->setObjectName("le_email_private");

        formLayout->setWidget(5, QFormLayout::FieldRole, le_email_private);

        label_10 = new QLabel(Member);
        label_10->setObjectName("label_10");

        formLayout->setWidget(6, QFormLayout::LabelRole, label_10);

        le_phone = new QLineEdit(Member);
        le_phone->setObjectName("le_phone");

        formLayout->setWidget(6, QFormLayout::FieldRole, le_phone);

        label_7 = new QLabel(Member);
        label_7->setObjectName("label_7");

        formLayout->setWidget(7, QFormLayout::LabelRole, label_7);

        le_address = new QLineEdit(Member);
        le_address->setObjectName("le_address");

        formLayout->setWidget(7, QFormLayout::FieldRole, le_address);

        label_11 = new QLabel(Member);
        label_11->setObjectName("label_11");

        formLayout->setWidget(8, QFormLayout::LabelRole, label_11);

        le_shirt_size = new QLineEdit(Member);
        le_shirt_size->setObjectName("le_shirt_size");

        formLayout->setWidget(8, QFormLayout::FieldRole, le_shirt_size);

        label_12 = new QLabel(Member);
        label_12->setObjectName("label_12");

        formLayout->setWidget(9, QFormLayout::LabelRole, label_12);

        le_vdi_number = new QLineEdit(Member);
        le_vdi_number->setObjectName("le_vdi_number");

        formLayout->setWidget(9, QFormLayout::FieldRole, le_vdi_number);

        label_9 = new QLabel(Member);
        label_9->setObjectName("label_9");

        formLayout->setWidget(10, QFormLayout::LabelRole, label_9);

        le_language = new QLineEdit(Member);
        le_language->setObjectName("le_language");

        formLayout->setWidget(10, QFormLayout::FieldRole, le_language);

        label_14 = new QLabel(Member);
        label_14->setObjectName("label_14");

        formLayout->setWidget(11, QFormLayout::LabelRole, label_14);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        lw_changes = new QListWidget(Member);
        lw_changes->setObjectName("lw_changes");

        horizontalLayout_2->addWidget(lw_changes);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(-1, 0, 0, -1);
        tb_add = new QToolButton(Member);
        tb_add->setObjectName("tb_add");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/icon_add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        tb_add->setIcon(icon);

        verticalLayout_3->addWidget(tb_add);

        tb_remove = new QToolButton(Member);
        tb_remove->setObjectName("tb_remove");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/icon_remove.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        tb_remove->setIcon(icon1);

        verticalLayout_3->addWidget(tb_remove);

        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout_3);


        formLayout->setLayout(11, QFormLayout::FieldRole, horizontalLayout_2);

        label_15 = new QLabel(Member);
        label_15->setObjectName("label_15");

        formLayout->setWidget(12, QFormLayout::LabelRole, label_15);

        le_since = new QLineEdit(Member);
        le_since->setObjectName("le_since");

        formLayout->setWidget(12, QFormLayout::FieldRole, le_since);

        label_16 = new QLabel(Member);
        label_16->setObjectName("label_16");

        formLayout->setWidget(13, QFormLayout::LabelRole, label_16);

        le_until = new QLineEdit(Member);
        le_until->setObjectName("le_until");

        formLayout->setWidget(13, QFormLayout::FieldRole, le_until);

        label_3 = new QLabel(Member);
        label_3->setObjectName("label_3");

        formLayout->setWidget(14, QFormLayout::LabelRole, label_3);

        le_position = new QLineEdit(Member);
        le_position->setObjectName("le_position");

        formLayout->setWidget(14, QFormLayout::FieldRole, le_position);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(-1, 0, 0, -1);
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        pb_signature_export = new QPushButton(Member);
        pb_signature_export->setObjectName("pb_signature_export");

        verticalLayout_2->addWidget(pb_signature_export);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pb_okay = new QPushButton(Member);
        pb_okay->setObjectName("pb_okay");
        pb_okay->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout->addWidget(pb_okay);


        formLayout->setLayout(15, QFormLayout::FieldRole, horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        formLayout->setItem(16, QFormLayout::FieldRole, verticalSpacer_2);


        verticalLayout->addLayout(formLayout);

        QWidget::setTabOrder(cb_member, le_first_name);
        QWidget::setTabOrder(le_first_name, le_surname);
        QWidget::setTabOrder(le_surname, le_student_number);
        QWidget::setTabOrder(le_student_number, le_email_glr);
        QWidget::setTabOrder(le_email_glr, le_email_private);
        QWidget::setTabOrder(le_email_private, le_phone);
        QWidget::setTabOrder(le_phone, le_address);
        QWidget::setTabOrder(le_address, le_shirt_size);
        QWidget::setTabOrder(le_shirt_size, le_vdi_number);
        QWidget::setTabOrder(le_vdi_number, le_language);
        QWidget::setTabOrder(le_language, lw_changes);
        QWidget::setTabOrder(lw_changes, tb_add);
        QWidget::setTabOrder(tb_add, tb_remove);
        QWidget::setTabOrder(tb_remove, le_since);
        QWidget::setTabOrder(le_since, le_until);
        QWidget::setTabOrder(le_until, le_position);
        QWidget::setTabOrder(le_position, pb_signature_export);
        QWidget::setTabOrder(pb_signature_export, pb_okay);

        retranslateUi(Member);

        QMetaObject::connectSlotsByName(Member);
    } // setupUi

    void retranslateUi(QDialog *Member)
    {
        Member->setWindowTitle(QCoreApplication::translate("Member", "Dialog", nullptr));
        l_dialogTitle->setText(QCoreApplication::translate("Member", "Mitglied hinzuf\303\274gen", nullptr));
        label_13->setText(QCoreApplication::translate("Member", "Mitglied", nullptr));
        cb_member->setPlaceholderText(QCoreApplication::translate("Member", "Mitglied...", nullptr));
        label_8->setText(QCoreApplication::translate("Member", "Vorname", nullptr));
        label_2->setText(QCoreApplication::translate("Member", "Nachname", nullptr));
        label_4->setText(QCoreApplication::translate("Member", "Matrikelnummer", nullptr));
        label_5->setText(QCoreApplication::translate("Member", "E-Mail GLR", nullptr));
        label_6->setText(QCoreApplication::translate("Member", "E-Mail Privat", nullptr));
        label_10->setText(QCoreApplication::translate("Member", "Telefon", nullptr));
        label_7->setText(QCoreApplication::translate("Member", "Anschrift", nullptr));
        label_11->setText(QCoreApplication::translate("Member", "Hemdgr\303\266\303\237e", nullptr));
        label_12->setText(QCoreApplication::translate("Member", "VDI-Nummer", nullptr));
        label_9->setText(QCoreApplication::translate("Member", "Sprache", nullptr));
        label_14->setText(QCoreApplication::translate("Member", "Verlauf", nullptr));
#if QT_CONFIG(tooltip)
        tb_add->setToolTip(QCoreApplication::translate("Member", "Verlaufsangabe hinzuf\303\274gen", nullptr));
#endif // QT_CONFIG(tooltip)
        tb_add->setText(QString());
#if QT_CONFIG(tooltip)
        tb_remove->setToolTip(QCoreApplication::translate("Member", "Verlaufsangabe entfernen", nullptr));
#endif // QT_CONFIG(tooltip)
        tb_remove->setText(QString());
        label_15->setText(QCoreApplication::translate("Member", "Seit", nullptr));
        label_16->setText(QCoreApplication::translate("Member", "Bis", nullptr));
        label_3->setText(QCoreApplication::translate("Member", "Position", nullptr));
        pb_signature_export->setText(QCoreApplication::translate("Member", "Signatur exportieren", nullptr));
        pb_okay->setText(QCoreApplication::translate("Member", "Okay", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Member: public Ui_Member {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEMBER_H
