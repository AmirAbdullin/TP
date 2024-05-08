#include "MainWindow.h"
#include "HelpDialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QAction>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QMenu *helpMenu = menuBar()->addMenu(tr("HELP"));
    helpAction = new QAction(tr("Description"), this);
    helpMenu->addAction(helpAction);
    connect(helpAction, &QAction::triggered, this, &MainWindow::showHelpDialog);

    qubitSelector = new QComboBox();
    qubitSelector->addItem("1 Qubit");
    qubitSelector->addItem("2 Qubits");
    connect(qubitSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(updateGateAvailability(int)));

    gateSequenceDisplay = new QTextEdit();
    gateSequenceDisplay->setReadOnly(true);

    resultDisplay = new QTextEdit();
    resultDisplay->setReadOnly(true);

    runSimulationButton = new QPushButton("Get Result");
    connect(runSimulationButton, &QPushButton::clicked, this, &MainWindow::runSimulation);

    clearButton = new QPushButton("Clear Sequence");
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearSequence);

    QHBoxLayout *gateButtonLayout = new QHBoxLayout;
    QStringList gates = {"X0", "X1", "Y0", "Y1", "Z0", "Z1", "H0", "H1", "CX", "SWAP"};
    foreach (const QString &gate, gates) {
        QPushButton *button = new QPushButton(gate);
        gateButtonLayout->addWidget(button);
        gateButtons.append(button);
        connect(button, &QPushButton::clicked, this, &MainWindow::addGateToSequence);
    }

    mainLayout->addWidget(qubitSelector);
    mainLayout->addWidget(gateSequenceDisplay);
    mainLayout->addLayout(gateButtonLayout);
    mainLayout->addWidget(runSimulationButton);
    mainLayout->addWidget(resultDisplay);
    mainLayout->addWidget(clearButton);

    centralWidget->setLayout(mainLayout);

    updateGateAvailability(qubitSelector->currentIndex());
}

void MainWindow::addGateToSequence() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString text = gateSequenceDisplay->toPlainText() + button->text() + " ";
        gateSequenceDisplay->setText(text);
    }
}

void MainWindow::clearSequence() {
    gateSequenceDisplay->clear();
    resultDisplay->clear();
}

void MainWindow::showHelpDialog() {
    HelpDialog helpDialog(this);
    helpDialog.exec();
}

void MainWindow::runSimulation() {
    int numQubits = qubitSelector->currentIndex() + 1;
    QString sequence = gateSequenceDisplay->toPlainText().trimmed();
    if (!sequence.isEmpty()) {
        QString result = simulator.runSimulation(sequence, numQubits);
        resultDisplay->setText(result);
    } else {
        resultDisplay->setText("Please enter a sequence of gates first.");
    }
}

void MainWindow::updateGateAvailability(int index) {
    simulator.setNumberOfQubits(index + 1);
    bool isTwoQubits = (index == 1);
    gateSequenceDisplay->clear();
    resultDisplay->clear();
    for (int i = 1; i < gateButtons.size(); i += 2) {
        gateButtons[i]->setEnabled(isTwoQubits);
    }
    gateButtons[8]->setEnabled(isTwoQubits);
}
