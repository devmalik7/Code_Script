#pragma once

#include <QObject>
#include <QPoint>
#include <QVector>

class AlgorithmWorker : public QObject {
    Q_OBJECT
public:
    explicit AlgorithmWorker(QObject *parent = nullptr);
    ~AlgorithmWorker() override;

public slots:
    void runBFS(const QVector<QVector<int>> &grid, const QPoint &start, const QPoint &target, int delayMs);
    void runDijkstra(const QVector<QVector<int>> &grid, const QPoint &start, const QPoint &target, int delayMs);
    void runAStar(const QVector<QVector<int>> &grid, const QPoint &start, const QPoint &target, int delayMs);

    void requestAbort();

signals:
    void visit(int row, int col);
    void pathNode(int row, int col);
    void status(const QString &msg);
    void finished();

private:
    volatile bool m_abortRequested;

    void sleepMs(int ms) const;

    static inline int manhattan(int r1, int c1, int r2, int c2) {
        return qAbs(r1 - r2) + qAbs(c1 - c2);
    }
};
