#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <string>


class Window : public QWidget{

    Q_OBJECT;

public:

    Window(QWidget* parent = nullptr);

private slots:

    void ButtonAddToken(const QString token);
    void ClearButton();
    void delButton();
    void EqualButton();

    void keyPressEvent(QKeyEvent* key_event) override;

private:

    QString q_expression;

    QLineEdit* display; 
    QPushButton* buttons[30];

    QGridLayout* grid;
    QVBoxLayout* mainlayout;

    //Parser parser;

};
