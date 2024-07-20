/********************************************************************************
** Form generated from reading UI file 'communication.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMUNICATION_H
#define UI_COMMUNICATION_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
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

class Ui_Communication
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *l_dialogTitle;
    QFormLayout *formLayout;
    QLabel *label_5;
    QComboBox *cb_communication;
    QLabel *label_1;
    QComboBox *cb_company;
    QLabel *label_4;
    QComboBox *cb_person;
    QLabel *label_2;
    QLineEdit *le_when;
    QCalendarWidget *cw_calender;
    QLabel *label_3;
    QLineEdit *le_what;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout;
    QListWidget *lw_files;
    QVBoxLayout *verticalLayout_4;
    QToolButton *tb_add;
    QToolButton *tb_remove;
    QToolButton *tb_download;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pb_okay;

    void setupUi(QDialog *Communication)
    {
        if (Communication->objectName().isEmpty())
            Communication->setObjectName("Communication");
        Communication->resize(495, 466);
        verticalLayout = new QVBoxLayout(Communication);
        verticalLayout->setObjectName("verticalLayout");
        l_dialogTitle = new QLabel(Communication);
        l_dialogTitle->setObjectName("l_dialogTitle");

        verticalLayout->addWidget(l_dialogTitle);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(-1, -1, 100, -1);
        label_5 = new QLabel(Communication);
        label_5->setObjectName("label_5");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_5);

        cb_communication = new QComboBox(Communication);
        cb_communication->setObjectName("cb_communication");

        formLayout->setWidget(0, QFormLayout::FieldRole, cb_communication);

        label_1 = new QLabel(Communication);
        label_1->setObjectName("label_1");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_1);

        cb_company = new QComboBox(Communication);
        cb_company->setObjectName("cb_company");

        formLayout->setWidget(1, QFormLayout::FieldRole, cb_company);

        label_4 = new QLabel(Communication);
        label_4->setObjectName("label_4");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        cb_person = new QComboBox(Communication);
        cb_person->setObjectName("cb_person");

        formLayout->setWidget(2, QFormLayout::FieldRole, cb_person);

        label_2 = new QLabel(Communication);
        label_2->setObjectName("label_2");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_2);

        le_when = new QLineEdit(Communication);
        le_when->setObjectName("le_when");
        le_when->setReadOnly(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, le_when);

        cw_calender = new QCalendarWidget(Communication);
        cw_calender->setObjectName("cw_calender");

        formLayout->setWidget(4, QFormLayout::FieldRole, cw_calender);

        label_3 = new QLabel(Communication);
        label_3->setObjectName("label_3");

        formLayout->setWidget(5, QFormLayout::LabelRole, label_3);

        le_what = new QLineEdit(Communication);
        le_what->setObjectName("le_what");
        le_what->setFrame(true);

        formLayout->setWidget(5, QFormLayout::FieldRole, le_what);

        label_6 = new QLabel(Communication);
        label_6->setObjectName("label_6");

        formLayout->setWidget(6, QFormLayout::LabelRole, label_6);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        lw_files = new QListWidget(Communication);
        lw_files->setObjectName("lw_files");

        horizontalLayout->addWidget(lw_files);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        tb_add = new QToolButton(Communication);
        tb_add->setObjectName("tb_add");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/icon_add.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        tb_add->setIcon(icon);
        tb_add->setIconSize(QSize(16, 16));
        tb_add->setArrowType(Qt::NoArrow);

        verticalLayout_4->addWidget(tb_add);

        tb_remove = new QToolButton(Communication);
        tb_remove->setObjectName("tb_remove");
        tb_remove->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tb_remove->sizePolicy().hasHeightForWidth());
        tb_remove->setSizePolicy(sizePolicy);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/icon_remove.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        tb_remove->setIcon(icon1);
        tb_remove->setIconSize(QSize(16, 16));

        verticalLayout_4->addWidget(tb_remove);

        tb_download = new QToolButton(Communication);
        tb_download->setObjectName("tb_download");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/icon_download.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        tb_download->setIcon(icon2);

        verticalLayout_4->addWidget(tb_download);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout_4);


        formLayout->setLayout(6, QFormLayout::FieldRole, horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pb_okay = new QPushButton(Communication);
        pb_okay->setObjectName("pb_okay");

        horizontalLayout_2->addWidget(pb_okay);


        formLayout->setLayout(7, QFormLayout::FieldRole, horizontalLayout_2);


        verticalLayout->addLayout(formLayout);

        QWidget::setTabOrder(cb_communication, cb_company);
        QWidget::setTabOrder(cb_company, cb_person);
        QWidget::setTabOrder(cb_person, le_when);
        QWidget::setTabOrder(le_when, cw_calender);
        QWidget::setTabOrder(cw_calender, le_what);
        QWidget::setTabOrder(le_what, lw_files);
        QWidget::setTabOrder(lw_files, tb_add);
        QWidget::setTabOrder(tb_add, tb_remove);
        QWidget::setTabOrder(tb_remove, tb_download);
        QWidget::setTabOrder(tb_download, pb_okay);

        retranslateUi(Communication);

        QMetaObject::connectSlotsByName(Communication);
    } // setupUi

    void retranslateUi(QDialog *Communication)
    {
        Communication->setWindowTitle(QCoreApplication::translate("Communication", "Dialog", nullptr));
        l_dialogTitle->setText(QCoreApplication::translate("Communication", "Kommunikation hinzuf\303\274gen", nullptr));
        label_5->setText(QCoreApplication::translate("Communication", "Kommunikation", nullptr));
        cb_communication->setPlaceholderText(QCoreApplication::translate("Communication", "Kommunikation...", nullptr));
        label_1->setText(QCoreApplication::translate("Communication", "Unternehmen", nullptr));
        cb_company->setPlaceholderText(QCoreApplication::translate("Communication", "Unternehmen...", nullptr));
        label_4->setText(QCoreApplication::translate("Communication", "Ansprechpartner", nullptr));
        cb_person->setPlaceholderText(QCoreApplication::translate("Communication", "Anprechpartner...", nullptr));
        label_2->setText(QCoreApplication::translate("Communication", "Wann", nullptr));
        label_3->setText(QCoreApplication::translate("Communication", "Was", nullptr));
        label_6->setText(QCoreApplication::translate("Communication", "Dateien", nullptr));
#if QT_CONFIG(tooltip)
        tb_add->setToolTip(QCoreApplication::translate("Communication", "Kommunikation hinzuf\303\274gen", nullptr));
#endif // QT_CONFIG(tooltip)
        tb_add->setText(QString());
#if QT_CONFIG(tooltip)
        tb_remove->setToolTip(QCoreApplication::translate("Communication", "Ausgew\303\244hlte Kommunikationen l\303\266schen", nullptr));
#endif // QT_CONFIG(tooltip)
        tb_remove->setText(QString());
#if QT_CONFIG(tooltip)
        tb_download->setToolTip(QCoreApplication::translate("Communication", "Ausgew\303\244hlte Kommunikationen speichern", nullptr));
#endif // QT_CONFIG(tooltip)
        tb_download->setText(QString());
        pb_okay->setText(QCoreApplication::translate("Communication", "Okay", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Communication: public Ui_Communication {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMUNICATION_H
