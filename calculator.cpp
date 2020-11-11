#include "calculator.h"
#include "array.h"

#include "iostream"
#include "string"
#include <cctype>
using namespace std;

#include <QLineEdit>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

#include <QTextStream>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    setupForm();
    setupConnections();
}

void Calculator::setupForm() {
    QHBoxLayout *lTop = new QHBoxLayout;
    QVBoxLayout *lOperands = new QVBoxLayout;
    QVBoxLayout *lOperators = new QVBoxLayout;
    QHBoxLayout *lButtons = new QHBoxLayout;
    QVBoxLayout *lMain = new QVBoxLayout;

    // lOperands
    lblOperands = new QLabel(tr("Operands: "));
    lblLeftOperand = new QLabel(tr("&Left operand: "));
    editLeftOperand = new QLineEdit;
    lblRightOperand = new QLabel(tr("&Right operand: "));
    editRightOperand = new QLineEdit;

    lblLeftOperand->setBuddy(editLeftOperand);
    lblRightOperand->setBuddy(editRightOperand);
    lOperands->addWidget(lblOperands);
    lOperands->addWidget(lblLeftOperand);
    lOperands->addWidget(editLeftOperand);
    lOperands->addWidget(lblRightOperand);
    lOperands->addWidget(editRightOperand);
    lOperands->addStretch();

    // LOperators
    lblOperators = new QLabel(tr("Operators: "));
    rbAddition = new QRadioButton(tr("&Addidion"));
    rbSubstruction = new QRadioButton(tr("&Substruction"));
    rbMultiplication = new QRadioButton(tr("&Multiplication"));
    rbDivision = new QRadioButton(tr("&Division"));
    rbAddition->setChecked(true);

    lOperators->addWidget(lblOperators);
    lOperators->addWidget(rbAddition);
    lOperators->addWidget(rbSubstruction);
    lOperators->addWidget(rbMultiplication);
    lOperators->addWidget(rbDivision);
    lOperators->addStretch();

    // Buttons
    btnCalculate = new QPushButton(tr("&Calculate"));
    btnQuit = new QPushButton(tr("&Quit"));
    btnAbout = new QPushButton(tr("About"));

    lButtons->addWidget(btnCalculate);
    lButtons->addStretch();
    lButtons->addWidget(btnQuit);
    lButtons->addWidget(btnAbout);

    // Layouts
    lTop->addLayout(lOperands);
    lTop->addLayout(lOperators);
    lMain->addLayout(lTop);
    lMain->addLayout(lButtons);
    setWindowTitle(tr("Calculator of long integers"));

    setLayout(lMain);
}

void Calculator::setupConnections() {
    connect(btnQuit, SIGNAL(clicked()), this, SLOT(close()));
    connect(btnCalculate, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(btnAbout, SIGNAL(clicked()), this, SLOT(showAbout()));
}

Calculator::~Calculator()
{
}

void Calculator::showResultMes(LongInt result) {
    QString resQStr = result.toQStr();
    QMessageBox::information(this,
                             tr("Success"),
                             tr("The results is %1").arg(resQStr));
    editLeftOperand->clear();
    editRightOperand->clear();
    editLeftOperand->setFocus();
}

void Calculator::showResultMesDiv(int res, LongInt rem) {
    QString resQStr = QString::number(res);
    QString remQStr = rem.toQStr();
    QMessageBox::information(this,
                             tr("Success"),
                             tr("The results is %1 with reminder = %2").arg(resQStr).arg(remQStr));
    editLeftOperand->clear();
    editRightOperand->clear();
    editLeftOperand->setFocus();
}

bool Calculator::inputCheck(string str) {
    if (str.length()==0) {return false;}
    int end = static_cast<int>(str.length());
    int start = 0;
    cout << "str[0] "  << str[0] << endl;
    if (str[0]=='-') {start=+1;}
    for (int i=start; i< end; i++) {
            if (isdigit(str[i])) {}
            else {return false;}
        }
    return true;
}

void Calculator::calculate(){
    QString xQStr, yQStr, resQStr;

    xQStr = editLeftOperand->text();
    string xStr = xQStr.toStdString();
    cout << "xStr " << xStr << endl;
    if(!inputCheck(xStr)) {
        QMessageBox::warning(this,
                             tr("Error"),
                             tr("Invalid left operand"));
        return;
    }
    LongInt x (xStr);
    cout << "x " << x << endl;

    yQStr = editRightOperand->text();
    string yStr = yQStr.toStdString();
    if(!inputCheck(yStr)) {
        QMessageBox::warning(this,
                             tr("Error"),
                             tr("Invalid right operand"));
        return;
    }
    LongInt y (yStr);
    cout << "y " << y << endl;

    if (rbAddition->isChecked()) {
        LongInt result = x + y;
        showResultMes(result);

    } else if (rbSubstruction->isChecked()) {
        LongInt result = x - y;
        showResultMes(result);

    } else if (rbMultiplication->isChecked()) {
        LongInt result = x * y;
        showResultMes(result);

    } else if (rbDivision->isChecked()) {
        if (y.isZero()) {
            QMessageBox::warning(this,
                                 tr("Error"),
                                 tr("Division by zero"));
            return;
        }
        auto res_div = x / y;
        showResultMesDiv(res_div.first,res_div.second);
    } else {
        QMessageBox::warning(this,
                             tr("Error"),
                             tr("No operator is selected"));
    }
}

void Calculator::showAbout() {
    QMessageBox::about(this,
                       tr("About"),
                       tr("<h2>Simple calculator for long integers 1.0</h2>"
                          ""
                          "Created by: Adeliia Gataullina"));
}
