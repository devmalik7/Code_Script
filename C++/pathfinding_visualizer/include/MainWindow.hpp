#pragma once

#include <QMainWindow>
#include <QThread>
#include <QString>

class Grid;
class AlgorithmWorker;
class QComboBox;
class QSlider;
class QLabel;
class QAction;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onRun();
    void onReset();
    void onSpeedChanged(int value);
    void onAlgoChanged(const QString &name);

    // Slots to receive worker signals (executed in GUI thread)
    void handleVisit(int row, int col);
    void handlePathNode(int row, int col);
    void handleWorkerFinished();
    void handleStatus(const QString &text);

private:
    void createToolbar();
    void startAlgorithmOnWorker();

    Grid *m_grid;
    AlgorithmWorker *m_worker;
    QThread *m_workerThread;

    QAction *m_runAction;
    QAction *m_resetAction;
    QComboBox *m_algoSelector;
    QSlider *m_speedSlider;
    QLabel *m_statusLabel;

    QString m_currentAlgo;
    int m_speedMs;
    bool m_isRunning;
};
