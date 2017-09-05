#include "worker.h"

worker::worker(QObject *parent)
{
    QObject(parent,stopped(false,))

}

