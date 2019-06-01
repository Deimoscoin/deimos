// Copyright (c) 2009-2019 The Bitcoin Core developers
// Copyright (c) 2014-2019 The DeimOS Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DEIMOS_QT_UTILITYDIALOG_H
#define DEIMOS_QT_UTILITYDIALOG_H

#include <QDialog>
#include <QObject>

class DeimOSGUI;

namespace interfaces {
    class Node;
}

namespace Ui {
    class HelpMessageDialog;
}

/** "Help message" dialog box */
class HelpMessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpMessageDialog(interfaces::Node& node, QWidget *parent, bool about);
    ~HelpMessageDialog();

    void printToConsole();
    void showOrPrint();

private:
    Ui::HelpMessageDialog *ui;
    QString text;

private Q_SLOTS:
    void on_okButton_accepted();
};


/** "Shutdown" window */
class ShutdownWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ShutdownWindow(QWidget *parent=0, Qt::WindowFlags f=0);
    static QWidget *showShutdownWindow(DeimOSGUI *window);

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // DEIMOS_QT_UTILITYDIALOG_H
