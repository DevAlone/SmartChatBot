#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "bot/bot.h"
//#include "bot/message.h"
//#include "bot/config/botaction.h"
//#include "bot/config/botconfig.h"
//#include "bot/config/botmessage.h"
//#include "bot/config/reaction.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bot = new botlib::Bot;
    connect(bot, SIGNAL(messageHistoryChanged(QList<botlib::Message>)),
            this, SLOT(messageHistoryChanged(QList<botlib::Message>)));
    //connect(ui->sendButton, SIGNAL(clicked()), ui->lineEdit_config, SLOT(clear()));

    QFile file("config.xml");
    ui->lineEdit_config->setText(QFileInfo(file.fileName()).absolutePath());
    file.open(QFile::ReadOnly);
    if(!file.isOpen()) {
        QMessageBox::warning(this, "Ошибка", "Ошибка открытия файла config.xml, возможно он отсутствует");
        //QApplication::exit();
        exit(1);
    }


    QString xmlData = filereadAll();

    file.close();

    if(!bot->setConfigFromXml(xmlData)) {
        QMessageBox::critical(this, "Error", "File parsing error");
    }

    timer = new QTimer();
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), bot, SLOT(update()));
    timer->start();

    ui->userMessage->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendButton_clicked()
{

    if(ui->userMessage->text().length()>0)
        bot->sendMessageToBot(ui->userMessage->text());
    ui->userMessage->clear();
}

void MainWindow::messageHistoryChanged(const QList<botlib::Message> &messages)
{
    for(int i = 0; i < messages.length(); i++) {
        const botlib::Message &message = messages[i];
        ui->messageHistory->addItem(QString(message.type == botlib::Message::BOT_MESSAGE ? "bot: " : "user: ") +
                                    message.message);
    }
    ui->messageHistory->scrollToBottom();
}

void MainWindow::on_openConfigButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("открыть xml конфиг"), "./", tr("XML files (*.xml)"));

    QFile file(fileName);
    file->open(QFile::ReadOnly);
    if(!file->isOpen())
    {
        QMessageBox::warning(this, "Ошибка", "Ошибка открытия файла, возможно он отсутствует, либо недостаточно прав для доступа к файлу");
        return;
    }
    QString fileData = file->readAll();

    file.close();
    ui->messageHistory->clear();
    if(!bot->setConfigFromXml(fileData)) {
        QMessageBox::warning(this, "Ошибка", "Ошибка парсинга конфига, возможно вы выбрали неправильный файл конфига");
        return;
    }


    ui->lineEdit_config->setText(fileName);
}
