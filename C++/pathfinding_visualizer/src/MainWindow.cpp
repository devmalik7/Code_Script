#include "MainWindow.hpp"
#include "Grid.hpp"
#include "Algorithms/AlgorithmWorker.hpp"

#include <QGraphicsView>
#include <QToolBar>
#include <QAction>
#include <QIcon>
#include <QComboBox>
#include <QSlider>
#include <QLabel>
#include <QStatusBar>
#include <QKeyEvent>
#include <QMetaObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_grid(nullptr),
      m_worker(nullptr),
      m_workerThread(nullptr),
      m_runAction(nullptr),
      m_resetAction(nullptr),
      m_algoSelector(nullptr),
      m_speedSlider(nullptr),
      m_statusLabel(nullptr),
      m_currentAlgo("A*"),
      m_speedMs(40),
      m_isRunning(false)
{
    setWindowTitle("Pathfinding Visualizer - Code_Script");
    resize(1280, 720);

    m_grid = new Grid(30, 50, this);
    QGraphicsView *view = new QGraphicsView(m_grid->scene(), this);
    view->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(view);

    createToolbar();
    m_statusLabel = new QLabel("Ready", this);
    statusBar()->addWidget(m_statusLabel);

    // Worker and thread
    m_worker = new AlgorithmWorker();
    m_workerThread = new QThread(this);
    m_worker->moveToThread(m_workerThread);
    m_workerThread->start();

    // Connect worker signals -> main window slots
    connect(m_worker, &AlgorithmWorker::visit, this, &MainWindow::handleVisit);
    connect(m_worker, &AlgorithmWorker::pathNode, this, &MainWindow::handlePathNode);
    connect(m_worker, &AlgorithmWorker::status, this, &MainWindow::handleStatus);
    connect(m_worker, &AlgorithmWorker::finished, this, &MainWindow::handleWorkerFinished);

    // Ensure thread quits when window destroyed
    connect(this, &QObject::destroyed, [this]() {
        if (m_worker) m_worker->requestAbort();
        if (m_workerThread && m_workerThread->isRunning()) {
            m_workerThread->quit();
            m_workerThread->wait();
        }
    });
}

MainWindow::~MainWindow() {
    if (m_worker) {
        m_worker->requestAbort();
    }
    if (m_workerThread && m_workerThread->isRunning()) {
        m_workerThread->quit();
        m_workerThread->wait();
    }
    delete m_worker;
}

void MainWindow::createToolbar() {
    QToolBar *toolbar = addToolBar("Controls");
    toolbar->setMovable(false);

    m_runAction = toolbar->addAction("Run");
    m_resetAction = toolbar->addAction("Reset");

    m_algoSelector = new QComboBox(this);
    m_algoSelector->addItems({"BFS", "Dijkstra", "A*"});
    toolbar->addWidget(m_algoSelector);

    m_speedSlider = new QSlider(Qt::Horizontal, this);
    m_speedSlider->setRange(5, 300);
    m_speedSlider->setValue(m_speedMs);
    m_speedSlider->setFixedWidth(200);
    toolbar->addWidget(m_speedSlider);

    connect(m_runAction, &QAction::triggered, this, &MainWindow::onRun);
    connect(m_resetAction, &QAction::triggered, this, &MainWindow::onReset);
    connect(m_speedSlider, &QSlider::valueChanged, this, &MainWindow::onSpeedChanged);
    connect(m_algoSelector, &QComboBox::currentTextChanged, this, &MainWindow::onAlgoChanged);
}

void MainWindow::onRun() {
    if (m_isRunning) {
        // Request abort if already running
        m_worker->requestAbort();
        m_statusLabel->setText("Abort requested...");
        return;
    }
    m_statusLabel->setText("Preparing...");
    startAlgorithmOnWorker();
}

void MainWindow::startAlgorithmOnWorker() {
    auto model = m_grid->exportModel(); // model.grid is QVector<QVector<int>>, start/target are QPoint
    // Call the appropriate worker slot via queued connection
    if (m_currentAlgo == "BFS") {
        QMetaObject::invokeMethod(m_worker, "runBFS", Qt::QueuedConnection,
                                  Q_ARG(QVector<QVector<int>>, model.grid),
                                  Q_ARG(QPoint, model.start),
                                  Q_ARG(QPoint, model.target),
                                  Q_ARG(int, m_speedMs));
    } else if (m_currentAlgo == "Dijkstra") {
        QMetaObject::invokeMethod(m_worker, "runDijkstra", Qt::QueuedConnection,
                                  Q_ARG(QVector<QVector<int>>, model.grid),
                                  Q_ARG(QPoint, model.start),
                                  Q_ARG(QPoint, model.target),
                                  Q_ARG(int, m_speedMs));
    } else {
        QMetaObject::invokeMethod(m_worker, "runAStar", Qt::QueuedConnection,
                                  Q_ARG(QVector<QVector<int>>, model.grid),
                                  Q_ARG(QPoint, model.start),
                                  Q_ARG(QPoint, model.target),
                                  Q_ARG(int, m_speedMs));
    }
    m_isRunning = true;
    m_statusLabel->setText("Running " + m_currentAlgo);
}

void MainWindow::onReset() {
    m_worker->requestAbort();
    m_grid->reset();
    m_statusLabel->setText("Grid reset");
    m_isRunning = false;
}

void MainWindow::onSpeedChanged(int value) {
    m_speedMs = value;
    m_statusLabel->setText(QString("Speed: %1 ms").arg(m_speedMs));
}

void MainWindow::onAlgoChanged(const QString &name) {
    m_currentAlgo = name;
    m_statusLabel->setText("Algorithm: " + name);
}

void MainWindow::handleVisit(int row, int col) {
    m_grid->markVisited(row, col);
}

void MainWindow::handlePathNode(int row, int col) {
    m_grid->markPath(row, col);
}

void MainWindow::handleWorkerFinished() {
    m_isRunning = false;
    m_statusLabel->setText("Finished");
}

void MainWindow::handleStatus(const QString &text) {
    m_statusLabel->setText(text);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (!event) return;
    if (event->key() == Qt::Key_Space) {
        onRun();
    } else if (event->key() == Qt::Key_R) {
        onReset();
    } else if (event->key() == Qt::Key_B) {
        m_algoSelector->setCurrentText("BFS");
    } else if (event->key() == Qt::Key_D) {
        m_algoSelector->setCurrentText("Dijkstra");
    } else if (event->key() == Qt::Key_A) {
        m_algoSelector->setCurrentText("A*");
    } else {
        QMainWindow::keyPressEvent(event);
    }
}
