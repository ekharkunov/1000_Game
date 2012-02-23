#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    connect(ui->startButton,SIGNAL(clicked()),this,SLOT(sendStartGameQuary()));

    connect(client,SIGNAL(erorText(QString)),this,SLOT(addMessageInChatView(QString)));
    connect(parser,SIGNAL(compliteMessage(QString)),this,SLOT(addMessageInChatView(QString)));
    connect(parser,SIGNAL(compliteAuthorization(QVector<QString>)),this,SLOT(getSomeMessagesFromServer(QVector<QString>)));
    connect(parser,SIGNAL(compliteRegistration(QVector<QString>)),this,SLOT(getSomeMessagesFromServer(QVector<QString>)));
    connect(parser,SIGNAL(compliteListAllGame(QList<GameThousand>)),this,SLOT(getListOfAllGamesOnServer(QList<GameThousand>)));
    connect(parser,SIGNAL(compliteListAllNewGame(QList<GameThousand>)),this,SLOT(getListOfAllNewGamesOnServer(QList<GameThousand>)));
}


void MainWindow::sendStartGameQuary()
{
    GameSettings game;
    //game.playersNumber=
    //game.timeout=
    parser->outStartGame(game);
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
    info.realName = "user";
    parser->outRegistration(info);
}

void MainWindow::getListOfAllNewGamesOnServer(QList<GameThousand> gameslist)
{
    for(int i=0;i<gameslist.size();i++)
    {
       quint16 gameID = gameslist.at(i).gameID();
       quint8 numberOfPlayers = gameslist.at(i).playerNumber();
       QString textDescription("New game %1:,%2");
       textDescription = textDescription.arg(gameID).arg(numberOfPlayers);
       QListWidgetItem item(textDescription,ui->allNewGamesView);
       ui->allGamesView->insertItem(i,&item);
    }
}

void MainWindow::getListOfAllGamesOnServer(QList<GameThousand> gameslist)
{
    for(int i=0;i<gameslist.size();i++)
    {
       quint16 gameID = gameslist.at(i).gameID();
       quint8 numberOfPlayers = gameslist.at(i).playerNumber();
       QString textDescription("Game %1:,%2");
       textDescription = textDescription.arg(gameID).arg(numberOfPlayers);
       QListWidgetItem item(textDescription,ui->allGamesView);
       ui->allGamesView->insertItem(i,&item);
    }
}


void MainWindow::getSomeMessagesFromServer(QVector<QString> data)
{
    for(int i=0;i<data.size();i++)
         ui->chatView->append(data.at(i));
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
