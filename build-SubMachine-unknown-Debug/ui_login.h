/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QWidget *centralwidget;
    QLineEdit *leuid;
    QLineEdit *lepsd;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pblogin;
    QPushButton *pbquit;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QStringLiteral("login"));
        login->resize(301, 575);
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        font.setItalic(true);
        login->setFont(font);
        login->setFocusPolicy(Qt::StrongFocus);
        centralwidget = new QWidget(login);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        leuid = new QLineEdit(centralwidget);
        leuid->setObjectName(QStringLiteral("leuid"));
        leuid->setGeometry(QRect(100, 240, 151, 31));
        lepsd = new QLineEdit(centralwidget);
        lepsd->setObjectName(QStringLiteral("lepsd"));
        lepsd->setGeometry(QRect(100, 290, 151, 31));
        lepsd->setEchoMode(QLineEdit::Password);
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 110, 231, 41));
        QFont font1;
        font1.setPointSize(14);
        label->setFont(font1);
        label->setFocusPolicy(Qt::NoFocus);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 250, 54, 18));
        label_2->setFont(font1);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 300, 51, 18));
        label_3->setFont(font1);
        pblogin = new QPushButton(centralwidget);
        pblogin->setObjectName(QStringLiteral("pblogin"));
        pblogin->setGeometry(QRect(30, 410, 81, 41));
        pblogin->setFont(font1);
        pbquit = new QPushButton(centralwidget);
        pbquit->setObjectName(QStringLiteral("pbquit"));
        pbquit->setGeometry(QRect(180, 410, 81, 41));
        pbquit->setFont(font1);
        login->setCentralWidget(centralwidget);
        statusBar = new QStatusBar(login);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        login->setStatusBar(statusBar);

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QMainWindow *login)
    {
        login->setWindowTitle(QApplication::translate("login", "\346\254\242\350\277\216\347\231\273\345\275\225!", 0));
#ifndef QT_NO_WHATSTHIS
        label->setWhatsThis(QApplication::translate("login", "<html><head/><body><p align=\"center\"><br/></p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        label->setText(QApplication::translate("login", "  \345\210\206\345\270\203\345\274\217\346\270\251\346\216\247\347\263\273\347\273\237\347\256\241\347\220\206\345\271\263\345\217\260", 0));
        label_2->setText(QApplication::translate("login", "\345\270\220\345\217\267:", 0));
        label_3->setText(QApplication::translate("login", "\345\257\206\347\240\201:", 0));
        pblogin->setText(QApplication::translate("login", "\347\231\273\345\275\225", 0));
        pbquit->setText(QApplication::translate("login", "\351\200\200\345\207\272", 0));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
