#include "QuantumSimulator.h"
#include <cmath>
#include <QTextStream>

QuantumSimulator::QuantumSimulator() : stateVector(4, {0.0, 0.0}) {
    stateVector[0] = {1.0, 0.0};
}

void QuantumSimulator::setNumberOfQubits(int numQubits) {
    int size = 1 << numQubits;
    stateVector.resize(size, {0.0, 0.0});
    stateVector[0] = {1.0, 0.0};
}

void QuantumSimulator::applyGate(const QString &gate) {
    if (gate == "X0") {
        std::swap(stateVector[0], stateVector[1]);
        std::swap(stateVector[2], stateVector[3]);
    } else if (gate == "X1") {
        std::swap(stateVector[0], stateVector[2]);
        std::swap(stateVector[1], stateVector[3]);
    } else if (gate == "Y0") {
        std::swap(stateVector[0], stateVector[1]); stateVector[1] *= std::complex<double>(0, 1);
        std::swap(stateVector[2], stateVector[3]); stateVector[3] *= std::complex<double>(0, 1);
    } else if (gate == "Y1") {
        std::swap(stateVector[0], stateVector[2]); stateVector[2] *= std::complex<double>(0, 1);
        std::swap(stateVector[1], stateVector[3]); stateVector[3] *= std::complex<double>(0, 1);
    } else if (gate == "Z0") {
        stateVector[1] *= -1;
        stateVector[3] *= -1;
    } else if (gate == "Z1") {
        stateVector[2] *= -1;
        stateVector[3] *= -1;
    } else if (gate == "H0") {
        auto temp0 = (stateVector[0] + stateVector[1]) / sqrt(2);
        auto temp1 = (stateVector[0] - stateVector[1]) / sqrt(2);
        stateVector[0] = temp0;
        stateVector[1] = temp1;
        auto temp2 = (stateVector[2] + stateVector[3]) / sqrt(2);
        auto temp3 = (stateVector[2] - stateVector[3]) / sqrt(2);
        stateVector[2] = temp2;
        stateVector[3] = temp3;
    }else if (gate == "H1") {
        auto temp0 = (stateVector[0] + stateVector[2]) / sqrt(2);
        auto temp1 = (stateVector[0] - stateVector[2]) / sqrt(2);
        stateVector[0] = temp0;
        stateVector[2] = temp1;
        auto temp2 = (stateVector[1] + stateVector[3]) / sqrt(2);
        auto temp3 = (stateVector[1] - stateVector[3]) / sqrt(2);
        stateVector[1] = temp2;
        stateVector[3] = temp3;
    } else if (gate == "CX") {
        std::complex<double> temp = stateVector[3];
        stateVector[3] = stateVector[1];
        stateVector[1] = temp;
    } else if (gate == "SWAP") {
        std::swap(stateVector[1], stateVector[2]);
    }
}

void QuantumSimulator::normalizeStateVector() {
    double norm = 0.0;
    for (const auto& amp : stateVector) {
        norm += std::norm(amp);
    }
    norm = sqrt(norm);
    for (auto& amp : stateVector) {
        amp /= norm;
    }
}

QString QuantumSimulator::runSimulation(const QString &input, int numQubits) {
    stateVector = std::vector<std::complex<double>>(4, {0.0, 0.0});
    int vectorSize = 1 << numQubits;
    stateVector.resize(vectorSize, {0.0, 0.0});
    stateVector[0] = {1.0, 0.0};
    QStringList gates = input.split(" ");
    for (const QString &gate : gates) {
        applyGate(gate.trimmed());
    }
    normalizeStateVector();



    QString result;
    QTextStream stream(&result);
    stream.setCodec("UTF-8");
    stream << "Final state vector:\n";
    for (size_t i = 0; i < stateVector.size(); ++i) {
        double probability = std::norm(stateVector[i]);
        QString binaryIndex = QString::number(i, 2).rightJustified(2, '0');
        stream << QString("|%1⟩: %2% (%3 + %4i)\n")
                      .arg(binaryIndex)
                      //.arg(i, 0, 2)
                      .arg(probability * 100, 0, 'f', 2)
                      .arg(stateVector[i].real(), 0, 'f', 3)
                      .arg(stateVector[i].imag(), 0, 'f', 3);
    }
    return result;
}
