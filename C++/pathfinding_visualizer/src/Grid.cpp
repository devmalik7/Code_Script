#include "Grid.hpp"
#include "Node.hpp"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QBrush>
#include <QDebug>

Grid::Grid(int rows, int cols, QObject *parent)
    : QObject(parent), m_rows(rows), m_cols(cols), m_scene(new QGraphicsScene(this))
{
    const int cellSize = 22;
    m_nodes.resize(m_rows);
    for (int r = 0; r < m_rows; ++r) {
        m_nodes[r].resize(m_cols);
        for (int c = 0; c < m_cols; ++c) {
            Node *n = new Node(r, c);
            n->setRect(0,0,cellSize - 1, cellSize - 1);
            n->setPos(c * cellSize, r * cellSize);
            m_scene->addItem(n);
            m_nodes[r][c] = n;
        }
    }

    m_start = QPoint(0, 0);
    m_target = QPoint(m_rows - 1, m_cols - 1);
    // mark start/target visuals
    m_nodes[m_start.x()][m_start.y()]->setAsStart();
    m_nodes[m_target.x()][m_target.y()]->setAsTarget();

    // Install this object as an event filter on the scene so we can handle clicks
    m_scene->installEventFilter(this);
}

Grid::~Grid() {
    // QGraphicsScene will delete items when destroyed; nothing to free here
}

Grid::Model Grid::exportModel() const {
    Model m;
    m.grid = QVector<QVector<int>>(m_rows, QVector<int>(m_cols, 0));
    for (int r = 0; r < m_rows; ++r)
        for (int c = 0; c < m_cols; ++c)
            m.grid[r][c] = m_nodes[r][c]->isWall() ? 1 : 0;
    m.start = m_start;
    m.target = m_target;
    return m;
}

void Grid::markVisited(int r, int c) {
    if (r < 0 || r >= m_rows || c < 0 || c >= m_cols) return;
    m_nodes[r][c]->setVisited(true);
}

void Grid::markPath(int r, int c) {
    if (r < 0 || r >= m_rows || c < 0 || c >= m_cols) return;
    m_nodes[r][c]->setPath(true);
}

void Grid::reset() {
    for (int r = 0; r < m_rows; ++r)
        for (int c = 0; c < m_cols; ++c)
            m_nodes[r][c]->reset();

    // re-mark start/target
    m_nodes[m_start.x()][m_start.y()]->setAsStart();
    m_nodes[m_target.x()][m_target.y()]->setAsTarget();
}

/**
 * eventFilter intercepts scene mouse press events and delegates to handlers.
 * Left click: toggle wall
 * Right click: set start
 * Middle click or Shift+Left: set target
 */
bool Grid::eventFilter(QObject *watched, QEvent *event) {
    if (watched == m_scene && event->type() == QEvent::GraphicsSceneMousePress) {
        auto *mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
        QPointF scenePos = mouseEvent->scenePos();
        if (mouseEvent->button() == Qt::LeftButton && !(mouseEvent->modifiers() & Qt::ShiftModifier)) {
            toggleWallAtScenePos(scenePos);
            return true;
        } else if (mouseEvent->button() == Qt::RightButton) {
            setStartAtScenePos(scenePos);
            return true;
        } else if (mouseEvent->button() == Qt::MiddleButton || (mouseEvent->button() == Qt::LeftButton && (mouseEvent->modifiers() & Qt::ShiftModifier))) {
            setTargetAtScenePos(scenePos);
            return true;
        }
    }
    return QObject::eventFilter(watched, event);
}

static QPointF roundToCellTopLeft(const QPointF &pos, int cellSize) {
    int c = int(pos.x()) / cellSize;
    int r = int(pos.y()) / cellSize;
    return QPointF(c * cellSize, r * cellSize);
}

void Grid::toggleWallAtScenePos(const QPointF &scenePos) {
    const int cellSize = 22;
    int c = int(scenePos.x()) / cellSize;
    int r = int(scenePos.y()) / cellSize;
    if (r < 0 || r >= m_rows || c < 0 || c >= m_cols) return;
    Node *n = m_nodes[r][c];
    // don't allow changing start/target into walls
    if (QPoint(r, c) == m_start || QPoint(r, c) == m_target) return;
    n->setWall(!n->isWall());
}

void Grid::setStartAtScenePos(const QPointF &scenePos) {
    const int cellSize = 22;
    int c = int(scenePos.x()) / cellSize;
    int r = int(scenePos.y()) / cellSize;
    if (r < 0 || r >= m_rows || c < 0 || c >= m_cols) return;
    // clear old start
    m_nodes[m_start.x()][m_start.y()]->reset();
    m_start = QPoint(r, c);
    m_nodes[m_start.x()][m_start.y()]->setAsStart();
}

void Grid::setTargetAtScenePos(const QPointF &scenePos) {
    const int cellSize = 22;
    int c = int(scenePos.x()) / cellSize;
    int r = int(scenePos.y()) / cellSize;
    if (r < 0 || r >= m_rows || c < 0 || c >= m_cols) return;
    // clear old target
    m_nodes[m_target.x()][m_target.y()]->reset();
    m_target = QPoint(r, c);
    m_nodes[m_target.x()][m_target.y()]->setAsTarget();
}
