#include "Algorithms/AlgorithmWorker.hpp"
#include <QThread>
#include <queue>
#include <limits>
#include <algorithm>

AlgorithmWorker::AlgorithmWorker(QObject *parent)
    : QObject(parent), m_abortRequested(false)
{}

AlgorithmWorker::~AlgorithmWorker() {}

void AlgorithmWorker::requestAbort() {
    m_abortRequested = true;
}

void AlgorithmWorker::sleepMs(int ms) const {
    // Sleep in worker thread
    QThread::msleep(static_cast<unsigned long>(ms));
}

/**
 * BFS implementation on a grid represented by QVector<QVector<int>>
 * 0 = free, 1 = wall
 */
void AlgorithmWorker::runBFS(const QVector<QVector<int>> &grid, const QPoint &start, const QPoint &target, int delayMs) {
    m_abortRequested = false;
    int rows = grid.size();
    if (rows == 0) { emit finished(); return; }
    int cols = grid[0].size();

    std::queue<QPoint> q;
    QVector<QVector<bool>> seen(rows, QVector<bool>(cols, false));
    QVector<QVector<QPoint>> parent(rows, QVector<QPoint>(cols, QPoint(-1, -1)));

    q.push(start);
    seen[start.x()][start.y()] = true;

    const int dr[4] = {1,-1,0,0};
    const int dc[4] = {0,0,1,-1};

    while (!q.empty() && !m_abortRequested) {
        QPoint cur = q.front(); q.pop();
        emit visit(cur.x(), cur.y());
        sleepMs(delayMs);

        if (cur == target) break;

        for (int i = 0; i < 4; ++i) {
            int nr = cur.x() + dr[i];
            int nc = cur.y() + dc[i];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
            if (grid[nr][nc] == 1) continue;
            if (seen[nr][nc]) continue;
            seen[nr][nc] = true;
            parent[nr][nc] = cur;
            q.push(QPoint(nr, nc));
        }
    }

    if (m_abortRequested) { emit status("Aborted"); emit finished(); return; }

    if (!seen[target.x()][target.y()]) {
        emit status("No path found");
        emit finished();
        return;
    }

    // Reconstruct path
    QVector<QPoint> path;
    for (QPoint at = target; at != QPoint(-1, -1); at = parent[at.x()][at.y()])
        path.push_back(at);
    std::reverse(path.begin(), path.end());
    for (const QPoint &p : path) {
        emit pathNode(p.x(), p.y());
        sleepMs(delayMs);
    }
    emit finished();
}

/**
 * Dijkstra (uniform weights for now; ready to accept weights if grid uses >1 values)
 */
void AlgorithmWorker::runDijkstra(const QVector<QVector<int>> &grid, const QPoint &start, const QPoint &target, int delayMs) {
    m_abortRequested = false;
    int rows = grid.size();
    if (rows == 0) { emit finished(); return; }
    int cols = grid[0].size();

    const int INF = std::numeric_limits<int>::max() / 4;
    QVector<QVector<int>> dist(rows, QVector<int>(cols, INF));
    QVector<QVector<QPoint>> parent(rows, QVector<QPoint>(cols, QPoint(-1,-1)));

    using NodeT = std::pair<int, QPoint>;
    auto cmp = [](const NodeT &a, const NodeT &b){ return a.first > b.first; };
    std::priority_queue<NodeT, std::vector<NodeT>, decltype(cmp)> pq(cmp);

    dist[start.x()][start.y()] = 0;
    pq.push({0, start});

    const int dr[4] = {1,-1,0,0};
    const int dc[4] = {0,0,1,-1};

    while (!pq.empty() && !m_abortRequested) {
        auto [d, pos] = pq.top(); pq.pop();
        int r = pos.x(), c = pos.y();
        if (d != dist[r][c]) continue;

        emit visit(r, c);
        sleepMs(delayMs);

        if (pos == target) break;

        for (int i=0;i<4;++i) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
            if (grid[nr][nc] == 1) continue;
            int w = 1; // default weight; if grid[r][c] > 1 treat as weight
            int nd = d + w;
            if (nd < dist[nr][nc]) {
                dist[nr][nc] = nd;
                parent[nr][nc] = pos;
                pq.push({nd, QPoint(nr,nc)});
            }
        }
    }

    if (m_abortRequested) { emit status("Aborted"); emit finished(); return; }

    if (dist[target.x()][target.y()] == INF) {
        emit status("No path found");
        emit finished();
        return;
    }

    QVector<QPoint> path;
    for (QPoint at = target; at != QPoint(-1,-1); at = parent[at.x()][at.y()])
        path.push_back(at);
    std::reverse(path.begin(), path.end());
    for (const QPoint &p : path) {
        emit pathNode(p.x(), p.y());
        sleepMs(delayMs);
    }
    emit finished();
}

/**
 * A* with Manhattan heuristic
 */
void AlgorithmWorker::runAStar(const QVector<QVector<int>> &grid, const QPoint &start, const QPoint &target, int delayMs) {
    m_abortRequested = false;
    int rows = grid.size();
    if (rows == 0) { emit finished(); return; }
    int cols = grid[0].size();

    const int INF = std::numeric_limits<int>::max() / 4;
    QVector<QVector<int>> gscore(rows, QVector<int>(cols, INF));
    QVector<QVector<QPoint>> parent(rows, QVector<QPoint>(cols, QPoint(-1,-1)));

    using NodeT = std::pair<int, QPoint>; // fscore, pos
    auto cmp = [](const NodeT &a, const NodeT &b){ return a.first > b.first; };
    std::priority_queue<NodeT, std::vector<NodeT>, decltype(cmp)> open(cmp);

    gscore[start.x()][start.y()] = 0;
    int f0 = manhattan(start.x(), start.y(), target.x(), target.y());
    open.push({f0, start});

    const int dr[4] = {1,-1,0,0};
    const int dc[4] = {0,0,1,-1};

    while (!open.empty() && !m_abortRequested) {
        auto [f, pos] = open.top(); open.pop();
        int r = pos.x(), c = pos.y();

        emit visit(r, c);
        sleepMs(delayMs);

        if (pos == target) break;

        for (int i=0;i<4;++i) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
            if (grid[nr][nc] == 1) continue;
            int tentative = gscore[r][c] + 1;
            if (tentative < gscore[nr][nc]) {
                parent[nr][nc] = pos;
                gscore[nr][nc] = tentative;
                int h = manhattan(nr, nc, target.x(), target.y());
                int nf = tentative + h;
                open.push({nf, QPoint(nr,nc)});
            }
        }
    }

    if (m_abortRequested) { emit status("Aborted"); emit finished(); return; }

    if (gscore[target.x()][target.y()] == INF) {
        emit status("No path found");
        emit finished();
        return;
    }

    QVector<QPoint> path;
    for (QPoint at = target; at != QPoint(-1,-1); at = parent[at.x()][at.y()])
        path.push_back(at);
    std::reverse(path.begin(), path.end());
    for (const QPoint &p : path) {
        emit pathNode(p.x(), p.y());
        sleepMs(delayMs);
    }
    emit finished();
}
