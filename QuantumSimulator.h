#ifndef QUANTUMSIMULATOR_H
#define QUANTUMSIMULATOR_H

#include <QString>
#include <QStringList>
#include <vector>
#include <complex>

class QuantumSimulator {
public:
    QuantumSimulator();
    void setNumberOfQubits(int numQubits);
    QString runSimulation(const QString &input, int numQubits);

private:
    std::vector<double> realParts;
    std::vector<double> imagParts;
    std::vector<std::complex<double>> stateVector;
    void applyGate(const QString &gate);
    void normalizeStateVector();
};

#endif // QUANTUMSIMULATOR_H
