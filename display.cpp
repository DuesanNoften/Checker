#include "display.h"

Display::Display()
{
    // Connect Game signal with Display slot
    QObject::connect(&game, SIGNAL(sendResponse(QString)), this, SLOT(getResponse(QString)));
    DisplayScene = new QGraphicsScene();
    setup();
    placePieces();
    turnColor = WHITE;
}

void Display::setup()
{
    int j = 0;
    int k = 0;
    bool black = true;
    for(int i=0; i<64; i++)
    {
        QString spacename = spaces[i];
        Space * s = new Space(j,k);
        s->setRect(j,k,50,50); //x loc, y loc, width, height

        // Color squares
        if (i % 8 == 0)
        {
            black = !black;
        }

        if (black)
        {
            s->setBrush(Qt::lightGray);
        }
        black = !black;

        s->setName(spacename);
        spaceList.append(s);
        DisplayScene->addItem(s);
        // Connect Space signal with Game slot
        QObject::connect(s, SIGNAL(sendSignal(QString)), &game, SLOT(getInput(QString)));

        j += 50;
        if (j == 400)
        {
            j = 0;
            k += 50;
        }
    }

    QString matchText = "Player 1 vs IA";
    QGraphicsTextItem * match = new QGraphicsTextItem();
    match->setPlainText(matchText);
    match->setPos(425, 0);
    DisplayScene->addItem(match);

    QString toMove = "White's turn";
    turn = new QGraphicsTextItem();
    turn->setPlainText(toMove);
    turn->setPos(425, 100);
    DisplayScene->addItem(turn);

    QString state = "";
    check = new QGraphicsTextItem();
    check->setPlainText(state);
    check->setPos(425, 200);
    DisplayScene->addItem(check);
}

void Display::placePieces()
{
    spaceList[1]->setImage(":/images/Images/black.png");
    spaceList[3]->setImage(":/images/Images/black.png");
    spaceList[5]->setImage(":/images/Images/black.png");
    spaceList[7]->setImage(":/images/Images/black.png");
    spaceList[8]->setImage(":/images/Images/black.png");
    spaceList[10]->setImage(":/images/Images/black.png");
    spaceList[12]->setImage(":/images/Images/black.png");
    spaceList[14]->setImage(":/images/Images/black.png");
    spaceList[17]->setImage(":/images/Images/black.png");
    spaceList[19]->setImage(":/images/Images/black.png");
    spaceList[21]->setImage(":/images/Images/black.png");
    spaceList[23]->setImage(":/images/Images/black.png");

    spaceList[40]->setImage(":/images/Images/white.png");
    spaceList[42]->setImage(":/images/Images/white.png");
    spaceList[44]->setImage(":/images/Images/white.png");
    spaceList[46]->setImage(":/images/Images/white.png");
    spaceList[49]->setImage(":/images/Images/white.png");
    spaceList[51]->setImage(":/images/Images/white.png");
    spaceList[53]->setImage(":/images/Images/white.png");
    spaceList[55]->setImage(":/images/Images/white.png");
    spaceList[56]->setImage(":/images/Images/white.png");
    spaceList[58]->setImage(":/images/Images/white.png");
    spaceList[60]->setImage(":/images/Images/white.png");
    spaceList[62]->setImage(":/images/Images/white.png");
}


QGraphicsScene* Display::getScene()
{
    return DisplayScene;
}

// Get a response from the Game object and change the
// images of pieces on the board appropriately
void Display::getResponse(QString response)
{
    std::string responseString = response.toStdString();

    // If response was "Invalid Move", ignore it
    if (responseString.compare("Invalid Move") == 0)
    {
        qDebug() << "Invalid Move";
        return;
    }
    else if (responseString.compare("Stalemate") == 0)
    {
        qDebug() << "Stalemate!";
        check->setPlainText("Stalemate!");
        return;
    }
    // Otherwise, use the response from Game to move the correct pieces
    else
    {
        qDebug() << "Display got permission from Game to move icons.";
//        qDebug() << "The response Game sent back was " << response;

            QString firstSpace = "";
            QString secondSpace = "";
            firstSpace += response[0];
            firstSpace += response[1];
            secondSpace += response[2];
            secondSpace += response[3];

            QString temp;
            for (int i=0; i<spaceList.length(); i++ )
            {
                if (spaceList[i]->getName() == firstSpace)
                {
                    temp = spaceList[i]->getImage();
                    spaceList[i]->clearImage();
                }
            }
            for (int i=0; i<spaceList.length(); i++ )
            {
                if (spaceList[i]->getName() == secondSpace)
                {
                    spaceList[i]->setImage(temp);
                }
            }


        if (turnColor == WHITE)
        {
            turnColor = BLACK;
            turn->setPlainText("Black's Turn");
        }
        else
        {
            turnColor = WHITE;
            turn->setPlainText("White's Turn");
        }
    }

}
