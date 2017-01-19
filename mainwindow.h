#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtCore>
#include <QtGui>
#include <QFile>
#include <QFileDialog>

#include <bot/bot.h>
#include <bot/message.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //std::unique_ptr<botlib::Bot> bot;
    botlib::Bot *bot;

private slots:
    void on_sendButton_clicked();
    void messageHistoryChanged(const QList<botlib::Message> &messages);

    void on_openConfigButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
};

#endif // MAINWINDOW_H
