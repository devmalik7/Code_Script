#include "Node.hpp"
#include <QBrush>
#include <QPen>

Node::Node(int row, int col)
    : QGraphicsRectItem(), m_row(row), m_col(col), m_visited(false), m_path(false), m_wall(false)
{
    setBrush(Qt::white);
    setPen(QPen(Qt::lightGray));
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setAcceptHoverEvents(false);
}

void Node::setVisited(bool v) {
    m_visited = v;
    if (!m_wall) {
        if (v) setBrush(QColor(135,206,250)); // light sky blue
        else setBrush(Qt::white);
    }
}

void Node::setPath(bool p) {
    m_path = p;
    if (!m_wall) {
        if (p) setBrush(QColor(255,215,0)); // gold
        else setBrush(Qt::white);
    }
}

void Node::setWall(bool w) {
    m_wall = w;
    setBrush(w ? Qt::black : Qt::white);
}

void Node::reset() {
    m_visited = false;
    m_path = false;
    m_wall = false;
    setBrush(Qt::white);
}

void Node::setAsStart() {
    m_visited = false;
    m_path = false;
    m_wall = false;
    setBrush(QColor(0,180,0)); // green
}

void Node::setAsTarget() {
    m_visited = false;
    m_path = false;
    m_wall = false;
    setBrush(QColor(200,0,0)); // red
}
