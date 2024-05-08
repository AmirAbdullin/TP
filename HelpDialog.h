// HelpDialog.h
#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>

class HelpDialog : public QDialog {
    Q_OBJECT
public:
    explicit HelpDialog(QWidget *parent = nullptr) : QDialog(parent, Qt::WindowCloseButtonHint) {
        setWindowTitle(tr("Reference for Quantum Gates"));
        QLabel* label = new QLabel(this);
        label->setText(tr(
            "<h2>Quantum Gate Reference</h2>"
            "<p><b>Initial State |00⟩:</b> All simulations start with both qubits in the state |00⟩.</p>"
            "<ul>"
            "<li><b>X0, X1 (Pauli-X, NOT Gate):</b> Flips |0⟩ to |1⟩ and |1⟩ to |0⟩ for the selected qubit.</li>"
            "<li><b>Y0, Y1 (Pauli-Y):</b> Performs a π rotation around the Y-axis of the Bloch sphere for the selected qubit.</li>"
            "<li><b>Z0, Z1 (Pauli-Z, Phase Shift):</b> Adds a phase of π to |1⟩ while leaving |0⟩ unchanged for the selected qubit.</li>"
            "<li><b>H0, H1 (Hadamard Gate):</b> Creates superposition by mapping |0⟩ to (|0⟩ + |1⟩)/√2 and |1⟩ to (|0⟩ - |1⟩)/√2 for the selected qubit.</li>"
            "<li><b>CX (Controlled-NOT):</b> Flips the second (target) qubit if the first (control) qubit is |1⟩.</li>"
            "<li><b>SWAP:</b> Swaps the states of two qubits.</li>"
            "</ul>"
            ));
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(label);
    }
};

#endif // HELPDIALOG_H
