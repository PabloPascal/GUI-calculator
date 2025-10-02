#include "mainwindow.hpp"
#include "parser.hpp"

#include <iostream>
#include <QKeyEvent>


Window::Window(QWidget* parent) : QWidget(parent)
{
    q_expression = "";


    display = new QLineEdit(this);
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMinimumSize(480, 50);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);

    grid = new QGridLayout;
    mainlayout = new QVBoxLayout(this);
    mainlayout->addWidget(display);
    mainlayout->addLayout(grid);
    //mainlayout->setSizeConstraint(QLayout::SetFixedSize);

    //grid->addWidget(display);

    QString names[5][6] = {
        {"del", "clear", "", "", "", "" }, 
        {"1", "2", "3", "+", "-", "*"   },
        {"4", "5", "6", "/", "^", "sin" },
        {"7", "8", "9", "(", ")", "cos" },
        {"0", ".", "=", "exp", "", ""   }
    };



    for(size_t i = 0; i < 5; i++){
        for(size_t j = 0; j < 6; j++){
            buttons[i*6 + j] = new QPushButton(names[i][j]);
            buttons[i*6 + j]->setMaximumSize(60, 60);
            grid->addWidget(buttons[i*6 + j], i, j);
        }
    }


    QObject::connect(buttons[6],  &QPushButton::clicked, [&]{ButtonAddToken("1");});
    QObject::connect(buttons[7],  &QPushButton::clicked, [&]{ButtonAddToken("2");});
    QObject::connect(buttons[8],  &QPushButton::clicked, [&]{ButtonAddToken("3");});
    QObject::connect(buttons[12], &QPushButton::clicked, [&]{ButtonAddToken("4");});
    QObject::connect(buttons[13], &QPushButton::clicked, [&]{ButtonAddToken("5");});
    QObject::connect(buttons[14], &QPushButton::clicked, [&]{ButtonAddToken("6");});
    QObject::connect(buttons[18], &QPushButton::clicked, [&]{ButtonAddToken("7");});
    QObject::connect(buttons[19], &QPushButton::clicked, [&]{ButtonAddToken("8");});
    QObject::connect(buttons[20], &QPushButton::clicked, [&]{ButtonAddToken("9");});
    QObject::connect(buttons[24], &QPushButton::clicked, [&]{ButtonAddToken("0");});

    QObject::connect(buttons[9], &QPushButton::clicked, [&]{ButtonAddToken("+");});
    QObject::connect(buttons[10], &QPushButton::clicked, [&]{ButtonAddToken("-");});
    QObject::connect(buttons[11], &QPushButton::clicked, [&]{ButtonAddToken("*");});
    QObject::connect(buttons[15], &QPushButton::clicked, [&]{ButtonAddToken("/");});
    QObject::connect(buttons[16], &QPushButton::clicked, [&]{ButtonAddToken("^");});
    QObject::connect(buttons[17], &QPushButton::clicked, [&]{ButtonAddToken("sin");});
    QObject::connect(buttons[21], &QPushButton::clicked, [&]{ButtonAddToken("(");});
    QObject::connect(buttons[22], &QPushButton::clicked, [&]{ButtonAddToken(")");});
    QObject::connect(buttons[23], &QPushButton::clicked, [&]{ButtonAddToken("cos");});
    QObject::connect(buttons[25], &QPushButton::clicked, [&]{ButtonAddToken(".");});
    QObject::connect(buttons[27], &QPushButton::clicked, [&]{ButtonAddToken("exp");});
    
    QObject::connect(buttons[0], &QPushButton::clicked, [&]{delButton();});
    QObject::connect(buttons[1], &QPushButton::clicked, [&]{ClearButton();});
    QObject::connect(buttons[26], &QPushButton::clicked, [&]{EqualButton();});


    setWindowTitle("Calculator");
    setMinimumSize(200, 480);

}



void Window::ButtonAddToken(const QString token){
    q_expression += token;
    display->setText(q_expression);
}


void Window::ClearButton(){
    q_expression = "";
    display->setText(q_expression);
}


void Window::delButton(){
    q_expression.erase(q_expression.end()-1, q_expression.end());
    display->setText(q_expression);
}


void Window::EqualButton(){
    std::string expr = q_expression.toStdString();

    Parser parser(expr);
    double ans = parser.getAnswer();
    ClearButton();
    q_expression = QString::number(ans);
    qDebug() << ans;
    display->setText(q_expression);

}


void Window::keyPressEvent(QKeyEvent* event){
    
    switch (event->key())
    {
    case Qt::Key_0:
        ButtonAddToken("0");
        break;
    case Qt::Key_1:
        ButtonAddToken("1");
        break;
    case Qt::Key_2:
        ButtonAddToken("2");
        break;
    case Qt::Key_3:
        ButtonAddToken("3");
        break;
    case Qt::Key_4:
        ButtonAddToken("4");
        break;
    case Qt::Key_5:
        ButtonAddToken("5");
        break;
    case Qt::Key_6:
        ButtonAddToken("6");
        break;
    case Qt::Key_7:
        ButtonAddToken("7");
        break;
    case Qt::Key_8:
        ButtonAddToken("8");
        break;
    case Qt::Key_9:
        ButtonAddToken("9");
        break;
    case Qt::Key_Plus:
        ButtonAddToken("+");
        break;
    case Qt::Key_Minus:
        ButtonAddToken("-");
        break;
    case Qt::Key_Escape:
        delButton();
        break;
    case Qt::Key_Delete:
        delButton();
        break;
    case Qt::Key_Backspace:
        delButton();
        break;
    case Qt::Key_Slash:
        ButtonAddToken("/");
        break;
    case Qt::Key_division:
        ButtonAddToken("/");
        break;
    case Qt::Key_Asterisk:
        ButtonAddToken("*");
        break;
    case Qt::Key_multiply:
        ButtonAddToken("*");
        break;
    case Qt::Key_Period:
        ButtonAddToken(".");
        break;
    case Qt::Key_Comma:
        ButtonAddToken(".");
        break;
    case Qt::Key_ParenLeft:
        ButtonAddToken("(");
        break;
    case Qt::Key_ParenRight:
        ButtonAddToken(")");
        break;
    case Qt::Key_Equal:
        EqualButton();
        break;
    case Qt::Key_Return:
        EqualButton();
        break;
    case Qt::Key_Enter:
        EqualButton();
        break;
    default:
        break;
    }

}