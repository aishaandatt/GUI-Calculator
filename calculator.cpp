#include "calculator.h"
#include "ui_calculator.h"

double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

Calculator::Calculator(QWidget *parent) 
    : QMainWindow(parent)
    , ui(new Ui::Calculator) 
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));  
    QPushButton *numButtons[10]; //refrence to all buttons 0 to 9
    for(int i=0;i<10;i++)
    {
        QString butName = "Button" + QString::number(i);
        numButtons[i]=Calculator::findChild<QPushButton *>(butName); 
        connect(numButtons[i], SIGNAL(released()),this, 
                SLOT(NumPressed()));

    }
    connect(ui->Add, SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Division, SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Equals, SIGNAL(released()),this,
            SLOT(EqualButtonPressed()));
    connect(ui->ChangeSign, SIGNAL(released()),this,
            SLOT(ChangeNumberSign()));
    connect(ui->Clear, SIGNAL(released()),this,
            SLOT(ClearAll()));
    connect(ui->Delete, SIGNAL(released()),this,
            SLOT(Delete()));



}

Calculator::~Calculator()
{
    delete ui;
}

//destructor

void Calculator::NumPressed(){
    QPushButton *button =(QPushButton *)sender(); 
    QString butVal= button->text(); //to fetch the number that was on the button
    QString displayVal=ui->Display->text(); //to get the value in our display
    if((displayVal.toDouble()==0) || (displayVal.toDouble()==0.0 ))
    {
       ui->Display->setText(butVal);
    }
    else
    {
        QString newVal = displayVal + butVal;
        double dblNewVal= newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal,'g',16));//set to max 16 digits

    }
}

void Calculator::MathButtonPressed(){
    //track which math button was clicked last
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;

    QString displayVal = ui->Display->text(); //store current value in display
    calcVal=displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender(); //to find out what math button was acutally clicked on
    QString butVal=button->text(); //get the math symbol on the button
    //to see which button is clicked 
    if(QString::compare(butVal,"/",Qt::CaseInsensitive)==0)
    {
        divTrigger = true;
    }
    else if(QString::compare(butVal,"*",Qt::CaseInsensitive)==0)
    {
        multTrigger = true;
    }
    else if(QString::compare(butVal,"+",Qt::CaseInsensitive)==0)
    {
        addTrigger = true;
    }
    else
    {
        subTrigger = true;
    }
    ui->Display->setText(""); //clear the display to enter a new number
}

void Calculator::EqualButtonPressed()
{
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal=displayVal.toDouble(); //to convert to double to perform math
    if(addTrigger || subTrigger || multTrigger || divTrigger)
    {
        if(addTrigger)
        {
            solution=calcVal+dblDisplayVal;
        }
        else if(subTrigger)
        {
            solution=calcVal-dblDisplayVal;
        }
        else if(multTrigger)
        {
            solution=calcVal*dblDisplayVal;
        }
        else
        {
            solution=calcVal/dblDisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution));
}

void Calculator::ChangeNumberSign()
{
    QString displayVal= ui->Display->text();
    //reg ex check to check if the text inside is actually a number
    QRegExp reg("[-]?[0-9.]*");
    if(reg.exactMatch(displayVal)){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText((QString::number(dblDisplayValSign)));
    }

}

void Calculator::ClearAll()
{
    ui->Display->setText("0.0");
}

void Calculator::Delete()
{
    QString text = ui->Display->text();
       text = ui->Display->text().left(ui->Display->text().size()-1);
       if (text.isEmpty()) {
           text = "0";
       }
       ui->Display->setText(text);
   }
