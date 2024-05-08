#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QComboBox>
#include <QVector>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include "QuantumSimulator.h"
#include "HelpDialog.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void addGateToSequence();
    void clearSequence();
    void runSimulation();
    void updateGateAvailability(int index);
    void showHelpDialog();

private:
    QTextEdit *gateSequenceDisplay;
    QTextEdit *resultDisplay;
    QComboBox *qubitSelector;
    QVector<QPushButton*> gateButtons;
    QPushButton *runSimulationButton;
    QPushButton *clearButton;
    QuantumSimulator simulator;
    QAction *helpAction;
};

#endif // MAINWINDOW_H
