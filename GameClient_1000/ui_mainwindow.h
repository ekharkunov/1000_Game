/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu 30. Jun 02:18:33 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *chatWidget;
    QTextEdit *chatView;
    QLineEdit *messageLineEdit;
    QLabel *label_3;
    QPushButton *sendButton;
    QWidget *listAndLogingWidget;
    QWidget *loginWidget;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QLineEdit *loginLineEdit;
    QWidget *widget;
    QTabWidget *tabWidget;
    QWidget *allGames;
    QListWidget *allGamesView;
    QWidget *newGames;
    QListWidget *allNewGamesView;
    QPushButton *startButton;
    QPushButton *createGameButton;
    QPushButton *exitButton;
    QGraphicsView *graphicsView;
    QTableView *statisticsView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(981, 747);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8("QWidget {\n"
"	    border: 1px solid #000000;\n"
"	    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"	                                   stop: 0 #95581f, \n"
"	                                   stop: 0.5 #b38522, stop: 1 #3a1c00);\n"
"	    color: #FFFFFF;\n"
"	    font: bold 14px;\n"
"	    min-width: 80px;\n"
"                       	}\n"
"QLineEdit\n"
"{\n"
"   background-color: rgba(255, 255, 255, 0);  \n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"    border: 0px;\n"
"    background-color: #dedede\n"
"}\n"
""));
        chatWidget = new QWidget(centralwidget);
        chatWidget->setObjectName(QString::fromUtf8("chatWidget"));
        chatWidget->setGeometry(QRect(10, 10, 221, 431));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(chatWidget->sizePolicy().hasHeightForWidth());
        chatWidget->setSizePolicy(sizePolicy);
        chatWidget->setMouseTracking(true);
        chatWidget->setAcceptDrops(true);
        chatWidget->setStyleSheet(QString::fromUtf8(""));
        chatView = new QTextEdit(chatWidget);
        chatView->setObjectName(QString::fromUtf8("chatView"));
        chatView->setGeometry(QRect(10, 40, 201, 301));
        chatView->setStyleSheet(QString::fromUtf8("background-color: #f7f7f4;\n"
"color: rgb(0, 0, 0);\n"
"   "));
        chatView->setReadOnly(false);
        messageLineEdit = new QLineEdit(chatWidget);
        messageLineEdit->setObjectName(QString::fromUtf8("messageLineEdit"));
        messageLineEdit->setGeometry(QRect(10, 350, 201, 31));
        QFont font;
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        messageLineEdit->setFont(font);
        messageLineEdit->setStyleSheet(QString::fromUtf8("background-color: #f7f7f4;\n"
"color: rgb(0, 0, 0);\n"
""));
        label_3 = new QLabel(chatWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 10, 161, 21));
        label_3->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"color: rgb(0, 0, 0);\n"
"font: 18pt \"Cooper Black\";"));
        sendButton = new QPushButton(chatWidget);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(10, 390, 201, 31));
        sendButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	    border: 1px solid #000000;\n"
"        border-radius: 10px;\n"
"	    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"	                                   stop: 0 #95581f, stop: 0.5 #331900, stop: 1 #95581f);\n"
"	    color: #FFFFFF;\n"
"	    font: bold 14px;\n"
"	    min-width: 80px;\n"
"                       	}\n"
"QPushButton:pressed {\n"
"	    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"	                                   stop: 0 #cfcccc, stop: 0.5 #333232,\n"
"	                                   stop: 0.51 #000000, stop: 1 #585c5f);\n"
"	    color: #00CC00;\n"
"	}\n"
"	 \n"
"QPushButton:flat {\n"
"	    border: none;\n"
"	}"));
        messageLineEdit->raise();
        label_3->raise();
        chatView->raise();
        sendButton->raise();
        listAndLogingWidget = new QWidget(centralwidget);
        listAndLogingWidget->setObjectName(QString::fromUtf8("listAndLogingWidget"));
        listAndLogingWidget->setGeometry(QRect(740, 10, 231, 731));
        listAndLogingWidget->setFont(font);
        listAndLogingWidget->setMouseTracking(true);
        listAndLogingWidget->setAcceptDrops(true);
        loginWidget = new QWidget(listAndLogingWidget);
        loginWidget->setObjectName(QString::fromUtf8("loginWidget"));
        loginWidget->setGeometry(QRect(10, 10, 221, 251));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(loginWidget->sizePolicy().hasHeightForWidth());
        loginWidget->setSizePolicy(sizePolicy1);
        loginWidget->setMouseTracking(true);
        loginWidget->setAutoFillBackground(false);
        label = new QLabel(loginWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 80, 23));
        label->setAutoFillBackground(false);
        label->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"font: 15pt \"Cooper Black\";\n"
"color: rgb(0, 0, 0);"));
        label_2 = new QLabel(loginWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 80, 106, 23));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"font: 15pt \"Cooper Black\";\n"
"color: rgb(0, 0, 0);"));
        passwordLineEdit = new QLineEdit(loginWidget);
        passwordLineEdit->setObjectName(QString::fromUtf8("passwordLineEdit"));
        passwordLineEdit->setGeometry(QRect(20, 110, 181, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font1.setPointSize(11);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        passwordLineEdit->setFont(font1);
        passwordLineEdit->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 11pt \"MS Shell Dlg 2\";\n"
"background-color: #f7f7f4"));
        loginButton = new QPushButton(loginWidget);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        loginButton->setGeometry(QRect(30, 160, 161, 31));
        loginButton->setMouseTracking(true);
        loginButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	    border: 1px solid #000000;\n"
"        border-radius: 10px;\n"
"	    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"	                                   stop: 0 #95581f, stop: 0.5 #331900, stop: 1 #95581f);\n"
"	    color: #FFFFFF;\n"
"	    font: bold 14px;\n"
"	    min-width: 80px;\n"
"                       	}\n"
"QPushButton:pressed {\n"
"	    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"	                                   stop: 0 #cfcccc, stop: 0.5 #333232,\n"
"	                                   stop: 0.51 #000000, stop: 1 #585c5f);\n"
"	    color: #00CC00;\n"
"	}\n"
"	 \n"
"QPushButton:flat {\n"
"	    border: none;\n"
"	}"));
        loginButton->setAutoDefault(false);
        registerButton = new QPushButton(loginWidget);
        registerButton->setObjectName(QString::fromUtf8("registerButton"));
        registerButton->setGeometry(QRect(30, 200, 161, 31));
        registerButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	    border: 1px solid #000000;\n"
"        border-radius: 10px;\n"
"	    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"	                                   stop: 0 #95581f, stop: 0.5 #331900, stop: 1 #95581f);\n"
"	    color: #FFFFFF;\n"
"	    font: bold 14px;\n"
"	    min-width: 80px;\n"
"                       	}\n"
"QPushButton:pressed {\n"
"	    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"	                                   stop: 0 #cfcccc, stop: 0.5 #333232,\n"
"	                                   stop: 0.51 #000000, stop: 1 #585c5f);\n"
"	    color: #00CC00;\n"
"	}\n"
"	 \n"
"QPushButton:flat {\n"
"	    border: none;\n"
"	}"));
        registerButton->setDefault(false);
        loginLineEdit = new QLineEdit(loginWidget);
        loginLineEdit->setObjectName(QString::fromUtf8("loginLineEdit"));
        loginLineEdit->setGeometry(QRect(20, 40, 181, 31));
        loginLineEdit->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 11pt \"MS Shell Dlg 2\";\n"
"background-color: #f7f7f4"));
        widget = new QWidget(listAndLogingWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 270, 221, 451));
        tabWidget = new QTabWidget(widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 201, 311));
        tabWidget->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        allGames = new QWidget();
        allGames->setObjectName(QString::fromUtf8("allGames"));
        allGames->setStyleSheet(QString::fromUtf8("color: rgba(255, 255, 255, 0)"));
        allGamesView = new QListWidget(allGames);
        allGamesView->setObjectName(QString::fromUtf8("allGamesView"));
        allGamesView->setGeometry(QRect(0, 0, 201, 281));
        tabWidget->addTab(allGames, QString());
        newGames = new QWidget();
        newGames->setObjectName(QString::fromUtf8("newGames"));
        allNewGamesView = new QListWidget(newGames);
        allNewGamesView->setObjectName(QString::fromUtf8("allNewGamesView"));
        allNewGamesView->setGeometry(QRect(0, 0, 191, 281));
        tabWidget->addTab(newGames, QString());
        startButton = new QPushButton(widget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(20, 330, 181, 31));
        startButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	    border: 1px solid #000000;\n"
"        border-radius: 10px;\n"
"	    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"	                                   stop: 0 #95581f, stop: 0.5 #331900, stop: 1 #95581f);\n"
"	    color: #FFFFFF;\n"
"	    font: bold 14px;\n"
"	    min-width: 80px;\n"
"                       	}\n"
"QPushButton:pressed {\n"
"	    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"	                                   stop: 0 #cfcccc, stop: 0.5 #333232,\n"
"	                                   stop: 0.51 #000000, stop: 1 #585c5f);\n"
"	    color: #00CC00;\n"
"	}\n"
"	 \n"
"QPushButton:flat {\n"
"	    border: none;\n"
"	}"));
        createGameButton = new QPushButton(widget);
        createGameButton->setObjectName(QString::fromUtf8("createGameButton"));
        createGameButton->setGeometry(QRect(21, 370, 181, 31));
        createGameButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	    border: 1px solid #000000;\n"
"        border-radius: 10px;\n"
"	    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"	                                   stop: 0 #95581f, stop: 0.5 #331900, stop: 1 #95581f);\n"
"	    color: #FFFFFF;\n"
"	    font: bold 14px;\n"
"	    min-width: 80px;\n"
"                       	}\n"
"QPushButton:pressed {\n"
"	    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"	                                   stop: 0 #cfcccc, stop: 0.5 #333232,\n"
"	                                   stop: 0.51 #000000, stop: 1 #585c5f);\n"
"	    color: #00CC00;\n"
"	}\n"
"	 \n"
"QPushButton:flat {\n"
"	    border: none;\n"
"	}"));
        exitButton = new QPushButton(widget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(20, 410, 181, 31));
        exitButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	    border: 1px solid #000000;\n"
"        border-radius: 10px;\n"
"	    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"	                                   stop: 0 #95581f, stop: 0.5 #331900, stop: 1 #95581f);\n"
"	    color: #FFFFFF;\n"
"	    font: bold 14px;\n"
"	    min-width: 80px;\n"
"                       	}\n"
"QPushButton:pressed {\n"
"	    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"	                                   stop: 0 #cfcccc, stop: 0.5 #333232,\n"
"	                                   stop: 0.51 #000000, stop: 1 #585c5f);\n"
"	    color: #00CC00;\n"
"	}\n"
"	 \n"
"QPushButton:flat {\n"
"	    border: none;\n"
"	}"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(240, 10, 491, 721));
        graphicsView->setStyleSheet(QString::fromUtf8("background-image: url(:/tabel/table);"));
        statisticsView = new QTableView(centralwidget);
        statisticsView->setObjectName(QString::fromUtf8("statisticsView"));
        statisticsView->setGeometry(QRect(10, 450, 221, 281));
        statisticsView->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);
        QObject::connect(exitButton, SIGNAL(clicked()), MainWindow, SLOT(close()));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        chatView->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-weight:600; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Chat:", 0, QApplication::UnicodeUTF8));
        sendButton->setText(QApplication::translate("MainWindow", "Send", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Login:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Password:", 0, QApplication::UnicodeUTF8));
        loginButton->setText(QApplication::translate("MainWindow", "Login", 0, QApplication::UnicodeUTF8));
        registerButton->setText(QApplication::translate("MainWindow", "Register", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(allGames), QApplication::translate("MainWindow", "All Games", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(newGames), QApplication::translate("MainWindow", "New Games", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        createGameButton->setText(QApplication::translate("MainWindow", "Create new game", 0, QApplication::UnicodeUTF8));
        exitButton->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
