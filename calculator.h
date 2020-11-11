#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <array.h>

class QLabel;
class QLineEdit;
class QRadioButton;
class QPushButton;

class Calculator : public QWidget
{
    Q_OBJECT

    // lOperands
    QLabel *lblOperands;
    QLabel *lblLeftOperand;
    QLabel *lblRightOperand;
    QLineEdit *editLeftOperand;
    QLineEdit *editRightOperand;

    // lOperators
    QLabel *lblOperators;
    QRadioButton *rbAddition;
    QRadioButton *rbSubstruction;
    QRadioButton *rbMultiplication;
    QRadioButton *rbDivision;

    // Buttons
    QPushButton *btnCalculate;
    QPushButton *btnAbout;
    QPushButton *btnQuit;

    void setupForm();
    void setupConnections();
    void showResultMes(LongInt result);
    void showResultMesDiv(int res, LongInt rem);
    bool inputCheck(string);
public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();
public slots:
    void calculate();
    void showAbout();
};
#endif // CALCULATOR_H
