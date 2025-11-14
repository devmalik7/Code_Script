#pragma once

#include <QGraphicsScene>
#include <QObject>
#include <QPoint>
#include <QVector>

/**
 * Grid manages QGraphicsScene and Node items.
 * It also handles mouse interactions by installing an event filter on the scene.
 * exportModel() returns a copy (QVector) safe to send across threads.
 */
class Node;
class Grid : public QObject {
    Q_OBJECT
public:
    struct Model {
        QVector<QVector<int>> grid; // 0 = free, 1 = wall
        QPoint start;
        QPoint target;
    };

    explicit Grid(int rows, int cols, QObject *parent = nullptr);
    ~Grid() override;

    QGraphicsScene* scene() const { return m_scene; }

    Model exportModel() const;

    // Called from GUI thread (slots)
    void markVisited(int r, int c);
    void markPath(int r, int c);
    void reset();

protected:
    // eventFilter to capture mouse clicks on the scene and translate to grid actions
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void toggleWallAtScenePos(const QPointF &scenePos);
    void setStartAtScenePos(const QPointF &scenePos);
    void setTargetAtScenePos(const QPointF &scenePos);

    int m_rows;
    int m_cols;
    QGraphicsScene *m_scene;
    QVector<QVector<Node*>> m_nodes;

    QPoint m_start;
    QPoint m_target;
};
