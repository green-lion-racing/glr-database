/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpenDatabase;
    QAction *actionPasswordAdd;
    QAction *actionPasswordChange;
    QAction *actionPasswordRemove;
    QAction *actionCloseDatabase;
    QAction *actionAbout;
    QWidget *centralwidget_main_menu;
    QVBoxLayout *verticalLayout_3;
    QStackedWidget *sw_main;
    QWidget *page_main;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QLabel *l_TilteTeamManagement;
    QToolButton *tb_createMember;
    QToolButton *tb_modifyMember;
    QVBoxLayout *verticalLayout_2;
    QLabel *l_TitleSponsorManagement;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *tb_createCompany;
    QToolButton *tb_modifyCompany;
    QHBoxLayout *horizontalLayout_9;
    QToolButton *tb_createPerson;
    QToolButton *tb_modifyPerson;
    QHBoxLayout *horizontalLayout_8;
    QToolButton *tb_createCommunication;
    QToolButton *tb_modifyCommunication;
    QHBoxLayout *horizontalLayout_5;
    QToolButton *tb_createActivity;
    QToolButton *tb_modifyActivity;
    QVBoxLayout *verticalLayout;
    QLabel *l_TitleManagement;
    QToolButton *tb_displayTables;
    QToolButton *tb_modifyTables;
    QWidget *page_logIn;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer;
    QLabel *l_logo;
    QHBoxLayout *horizontalLayout_3;
    QLabel *l_title;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLineEdit *le_password;
    QSpacerItem *horizontalSpacer_2;
    QLabel *l_error;
    QSpacerItem *verticalSpacer_2;
    QMenuBar *menubar;
    QMenu *menuDatei;
    QMenu *menuPassword;
    QMenu *menuAbout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1500, 1000);
        MainWindow->setMinimumSize(QSize(1120, 650));
        actionOpenDatabase = new QAction(MainWindow);
        actionOpenDatabase->setObjectName("actionOpenDatabase");
        actionPasswordAdd = new QAction(MainWindow);
        actionPasswordAdd->setObjectName("actionPasswordAdd");
        actionPasswordChange = new QAction(MainWindow);
        actionPasswordChange->setObjectName("actionPasswordChange");
        actionPasswordRemove = new QAction(MainWindow);
        actionPasswordRemove->setObjectName("actionPasswordRemove");
        actionCloseDatabase = new QAction(MainWindow);
        actionCloseDatabase->setObjectName("actionCloseDatabase");
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        centralwidget_main_menu = new QWidget(MainWindow);
        centralwidget_main_menu->setObjectName("centralwidget_main_menu");
        verticalLayout_3 = new QVBoxLayout(centralwidget_main_menu);
        verticalLayout_3->setObjectName("verticalLayout_3");
        sw_main = new QStackedWidget(centralwidget_main_menu);
        sw_main->setObjectName("sw_main");
        page_main = new QWidget();
        page_main->setObjectName("page_main");
        horizontalLayout_6 = new QHBoxLayout(page_main);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        l_TilteTeamManagement = new QLabel(page_main);
        l_TilteTeamManagement->setObjectName("l_TilteTeamManagement");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(l_TilteTeamManagement->sizePolicy().hasHeightForWidth());
        l_TilteTeamManagement->setSizePolicy(sizePolicy);

        verticalLayout_5->addWidget(l_TilteTeamManagement);

        tb_createMember = new QToolButton(page_main);
        tb_createMember->setObjectName("tb_createMember");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tb_createMember->sizePolicy().hasHeightForWidth());
        tb_createMember->setSizePolicy(sizePolicy1);
        tb_createMember->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        verticalLayout_5->addWidget(tb_createMember);

        tb_modifyMember = new QToolButton(page_main);
        tb_modifyMember->setObjectName("tb_modifyMember");
        sizePolicy1.setHeightForWidth(tb_modifyMember->sizePolicy().hasHeightForWidth());
        tb_modifyMember->setSizePolicy(sizePolicy1);
        tb_modifyMember->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        verticalLayout_5->addWidget(tb_modifyMember);


        horizontalLayout_6->addLayout(verticalLayout_5);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        l_TitleSponsorManagement = new QLabel(page_main);
        l_TitleSponsorManagement->setObjectName("l_TitleSponsorManagement");
        sizePolicy.setHeightForWidth(l_TitleSponsorManagement->sizePolicy().hasHeightForWidth());
        l_TitleSponsorManagement->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(l_TitleSponsorManagement);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        tb_createCompany = new QToolButton(page_main);
        tb_createCompany->setObjectName("tb_createCompany");
        sizePolicy1.setHeightForWidth(tb_createCompany->sizePolicy().hasHeightForWidth());
        tb_createCompany->setSizePolicy(sizePolicy1);
        tb_createCompany->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        horizontalLayout_4->addWidget(tb_createCompany);

        tb_modifyCompany = new QToolButton(page_main);
        tb_modifyCompany->setObjectName("tb_modifyCompany");
        sizePolicy1.setHeightForWidth(tb_modifyCompany->sizePolicy().hasHeightForWidth());
        tb_modifyCompany->setSizePolicy(sizePolicy1);
        tb_modifyCompany->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        horizontalLayout_4->addWidget(tb_modifyCompany);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        tb_createPerson = new QToolButton(page_main);
        tb_createPerson->setObjectName("tb_createPerson");
        sizePolicy1.setHeightForWidth(tb_createPerson->sizePolicy().hasHeightForWidth());
        tb_createPerson->setSizePolicy(sizePolicy1);
        tb_createPerson->setIconSize(QSize(16, 16));
        tb_createPerson->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
        tb_createPerson->setAutoRaise(false);

        horizontalLayout_9->addWidget(tb_createPerson);

        tb_modifyPerson = new QToolButton(page_main);
        tb_modifyPerson->setObjectName("tb_modifyPerson");
        sizePolicy1.setHeightForWidth(tb_modifyPerson->sizePolicy().hasHeightForWidth());
        tb_modifyPerson->setSizePolicy(sizePolicy1);
        tb_modifyPerson->setIconSize(QSize(16, 16));
        tb_modifyPerson->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
        tb_modifyPerson->setAutoRaise(false);

        horizontalLayout_9->addWidget(tb_modifyPerson);

        horizontalLayout_9->setStretch(0, 1);
        horizontalLayout_9->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        tb_createCommunication = new QToolButton(page_main);
        tb_createCommunication->setObjectName("tb_createCommunication");
        sizePolicy1.setHeightForWidth(tb_createCommunication->sizePolicy().hasHeightForWidth());
        tb_createCommunication->setSizePolicy(sizePolicy1);
        tb_createCommunication->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        horizontalLayout_8->addWidget(tb_createCommunication);

        tb_modifyCommunication = new QToolButton(page_main);
        tb_modifyCommunication->setObjectName("tb_modifyCommunication");
        sizePolicy1.setHeightForWidth(tb_modifyCommunication->sizePolicy().hasHeightForWidth());
        tb_modifyCommunication->setSizePolicy(sizePolicy1);
        tb_modifyCommunication->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        horizontalLayout_8->addWidget(tb_modifyCommunication);

        horizontalLayout_8->setStretch(0, 1);
        horizontalLayout_8->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        tb_createActivity = new QToolButton(page_main);
        tb_createActivity->setObjectName("tb_createActivity");
        sizePolicy1.setHeightForWidth(tb_createActivity->sizePolicy().hasHeightForWidth());
        tb_createActivity->setSizePolicy(sizePolicy1);
        tb_createActivity->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        horizontalLayout_5->addWidget(tb_createActivity);

        tb_modifyActivity = new QToolButton(page_main);
        tb_modifyActivity->setObjectName("tb_modifyActivity");
        sizePolicy1.setHeightForWidth(tb_modifyActivity->sizePolicy().hasHeightForWidth());
        tb_modifyActivity->setSizePolicy(sizePolicy1);
        tb_modifyActivity->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        horizontalLayout_5->addWidget(tb_modifyActivity);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout_5);


        horizontalLayout_6->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        l_TitleManagement = new QLabel(page_main);
        l_TitleManagement->setObjectName("l_TitleManagement");
        sizePolicy.setHeightForWidth(l_TitleManagement->sizePolicy().hasHeightForWidth());
        l_TitleManagement->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(l_TitleManagement);

        tb_displayTables = new QToolButton(page_main);
        tb_displayTables->setObjectName("tb_displayTables");
        sizePolicy1.setHeightForWidth(tb_displayTables->sizePolicy().hasHeightForWidth());
        tb_displayTables->setSizePolicy(sizePolicy1);
        tb_displayTables->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        verticalLayout->addWidget(tb_displayTables);

        tb_modifyTables = new QToolButton(page_main);
        tb_modifyTables->setObjectName("tb_modifyTables");
        sizePolicy1.setHeightForWidth(tb_modifyTables->sizePolicy().hasHeightForWidth());
        tb_modifyTables->setSizePolicy(sizePolicy1);
        tb_modifyTables->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        verticalLayout->addWidget(tb_modifyTables);


        horizontalLayout_6->addLayout(verticalLayout);

        horizontalLayout_6->setStretch(0, 2);
        horizontalLayout_6->setStretch(1, 5);
        horizontalLayout_6->setStretch(2, 2);
        sw_main->addWidget(page_main);
        page_logIn = new QWidget();
        page_logIn->setObjectName("page_logIn");
        verticalLayout_4 = new QVBoxLayout(page_logIn);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalSpacer = new QSpacerItem(20, 223, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout_4->addItem(verticalSpacer);

        l_logo = new QLabel(page_logIn);
        l_logo->setObjectName("l_logo");
        l_logo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(l_logo);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        l_title = new QLabel(page_logIn);
        l_title->setObjectName("l_title");
        l_title->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_3->addWidget(l_title);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        le_password = new QLineEdit(page_logIn);
        le_password->setObjectName("le_password");
        le_password->setEnabled(true);
        le_password->setMinimumSize(QSize(480, 0));
        le_password->setMaximumSize(QSize(480, 16777215));
        le_password->setEchoMode(QLineEdit::EchoMode::Password);
        le_password->setReadOnly(false);

        horizontalLayout_2->addWidget(le_password);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_4->addLayout(horizontalLayout_2);

        l_error = new QLabel(page_logIn);
        l_error->setObjectName("l_error");
        l_error->setEnabled(true);
        l_error->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(l_error);

        verticalSpacer_2 = new QSpacerItem(20, 222, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        sw_main->addWidget(page_logIn);

        verticalLayout_3->addWidget(sw_main);

        MainWindow->setCentralWidget(centralwidget_main_menu);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1500, 21));
        menuDatei = new QMenu(menubar);
        menuDatei->setObjectName("menuDatei");
        menuPassword = new QMenu(menuDatei);
        menuPassword->setObjectName("menuPassword");
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName("menuAbout");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setSizeGripEnabled(false);
        MainWindow->setStatusBar(statusbar);
        QWidget::setTabOrder(le_password, tb_createMember);
        QWidget::setTabOrder(tb_createMember, tb_modifyMember);
        QWidget::setTabOrder(tb_modifyMember, tb_createCompany);
        QWidget::setTabOrder(tb_createCompany, tb_modifyCompany);
        QWidget::setTabOrder(tb_modifyCompany, tb_createPerson);
        QWidget::setTabOrder(tb_createPerson, tb_modifyPerson);
        QWidget::setTabOrder(tb_modifyPerson, tb_createCommunication);
        QWidget::setTabOrder(tb_createCommunication, tb_modifyCommunication);
        QWidget::setTabOrder(tb_modifyCommunication, tb_createActivity);
        QWidget::setTabOrder(tb_createActivity, tb_modifyActivity);
        QWidget::setTabOrder(tb_modifyActivity, tb_displayTables);
        QWidget::setTabOrder(tb_displayTables, tb_modifyTables);

        menubar->addAction(menuDatei->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuDatei->addAction(actionOpenDatabase);
        menuDatei->addAction(actionCloseDatabase);
        menuDatei->addSeparator();
        menuDatei->addAction(menuPassword->menuAction());
        menuDatei->addSeparator();
        menuPassword->addAction(actionPasswordAdd);
        menuPassword->addAction(actionPasswordChange);
        menuPassword->addAction(actionPasswordRemove);
        menuAbout->addAction(actionAbout);

        retranslateUi(MainWindow);

        sw_main->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpenDatabase->setText(QCoreApplication::translate("MainWindow", "Datenbank \303\266ffnen", nullptr));
        actionPasswordAdd->setText(QCoreApplication::translate("MainWindow", "hinzuf\303\274gen", nullptr));
        actionPasswordChange->setText(QCoreApplication::translate("MainWindow", "\303\244ndern", nullptr));
        actionPasswordRemove->setText(QCoreApplication::translate("MainWindow", "entfernen", nullptr));
        actionCloseDatabase->setText(QCoreApplication::translate("MainWindow", "Datenbank schlie\303\237en", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "\303\234ber die Datenbank", nullptr));
        l_TilteTeamManagement->setText(QCoreApplication::translate("MainWindow", "Teamverwaltung", nullptr));
        tb_createMember->setText(QCoreApplication::translate("MainWindow", "Mitglied hinzuf\303\274gen", nullptr));
        tb_modifyMember->setText(QCoreApplication::translate("MainWindow", "Mitglied verwalten", nullptr));
        l_TitleSponsorManagement->setText(QCoreApplication::translate("MainWindow", "Sponsoringverwaltung", nullptr));
        tb_createCompany->setText(QCoreApplication::translate("MainWindow", "Unternehmen hinzuf\303\274gen", nullptr));
        tb_modifyCompany->setText(QCoreApplication::translate("MainWindow", "Unternehmen verwalten", nullptr));
        tb_createPerson->setText(QCoreApplication::translate("MainWindow", "Person hinzuf\303\274gen", nullptr));
        tb_modifyPerson->setText(QCoreApplication::translate("MainWindow", "Person verwalten", nullptr));
        tb_createCommunication->setText(QCoreApplication::translate("MainWindow", "Kommunikation hinzuf\303\274gen", nullptr));
        tb_modifyCommunication->setText(QCoreApplication::translate("MainWindow", "Kommunikation verwalten", nullptr));
        tb_createActivity->setText(QCoreApplication::translate("MainWindow", "Leistung hinzuf\303\274gen", nullptr));
        tb_modifyActivity->setText(QCoreApplication::translate("MainWindow", "Leistung verwalten", nullptr));
        l_TitleManagement->setText(QCoreApplication::translate("MainWindow", "Allgemein", nullptr));
        tb_displayTables->setText(QCoreApplication::translate("MainWindow", "Tabellen ansehen", nullptr));
        tb_modifyTables->setText(QCoreApplication::translate("MainWindow", "Tabellen bearbeiten", nullptr));
        l_logo->setText(QCoreApplication::translate("MainWindow", "l_logo", nullptr));
        l_title->setText(QCoreApplication::translate("MainWindow", "l_title", nullptr));
        le_password->setPlaceholderText(QCoreApplication::translate("MainWindow", "Passwort", nullptr));
        l_error->setText(QCoreApplication::translate("MainWindow", "l_error", nullptr));
        menuDatei->setTitle(QCoreApplication::translate("MainWindow", "Datei", nullptr));
        menuPassword->setTitle(QCoreApplication::translate("MainWindow", "Passwort", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("MainWindow", "\303\234ber", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
