#pragma once

#include <QGraphicsRectItem>

/**
 * Node is a QGraphicsRectItem representing one grid cell.
 * It stores row/col indices and visual state.
 *
 * Note: Node methods must be called from the GUI thread.
 */
class Node : public QGraphicsRectItem {
public:
    Node(int row = 0, int col = 0);

    void setVisited(bool v);
    void setPath(bool p);
    void setWall(bool w);
    void reset();

    void setAsStart();
    void setAsTarget();

    bool isWall() const { return m_wall; }
    int row() const { return m_row; }
    int col() const { return m_col; }

private:
    int m_row;
    int m_col;
    bool m_visited;
    bool m_path;
    bool m_wall;
};
