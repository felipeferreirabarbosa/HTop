#ifndef WORKER_H
#define WORKER_H


class worker : public QObject
{Q_OBJECT
public:
    explicit worker(QObject *parente = 0);
};

#endif // WORKER_H
