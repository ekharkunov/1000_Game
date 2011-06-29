#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showFullScreen();
    client = new ThousandClient(1000,"127.0.0.1");
    parser=client->getDataParser();
    setupWidgets();
    client->connectToServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupWidgets()
{
    int x=this->width();
    int y=this->height();
    ui->listAndLogingWidget->setGeometry(x-251,10,241,731);
    ui->graphicsView->setGeometry(241,10,x-502,y-20);

    connect(ui->loginButton,SIGNAL(clicked()),this,SLOT(sendAuthorizationDataToServer()));
    connect(ui->registerButton,SIGNAL(clicked()),this,SLOT(sendRegistrationDataToServer()));
    connect(ui->sendButton,SIGNAL(clicked()),this,SLOT(sendMessageToServer()));

    connect(client,SIGNAL(erorText(QString)),this,SLOT(addMessageInChatView(QString)));
    connect(parser,SIGNAL(compliteMessage(QString)),this,SLOT(addMessageInChatView(QString)));

}



void MainWindow::sendMessageToServer()
{
  parser->outMessage(ui->messageLineEdit->text());
  ui->messageLineEdit->clear();
}

void MainWindow::sendAuthorizationDataToServer()
{
  AuthorizationData info;
  info.login=ui->loginLineEdit->text();
  info.password=ui->passwordLineEdit->text();
  parser->outAuthorization(info);
}

void MainWindow::sendRegistrationDataToServer()
{
    RegistrationData info;
    info.nickName = ui->loginLineEdit->text();
    info.password = ui->passwordLineEdit->text();
    info.realName = "sergei";
}

void MainWindow::sendMoveToServer()
{

}

void MainWindow::addMessageInChatView(QString message)
{
      ui->chatView->append(message);
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
