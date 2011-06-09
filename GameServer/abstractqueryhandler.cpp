#include "abstractqueryhandler.h"

AbstractQueryHandler::AbstractQueryHandler(QObject *parent) :
    QThread(parent)
{
}

AbstractQueryHandler::~AbstractQueryHandler() {

}
