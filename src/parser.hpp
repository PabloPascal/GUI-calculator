#include <iostream>
#include <string>
#include <cmath>



class Parser{

    std::string m_expression;
    int index = 0;

    enum class TOKEN{
        number,
        plus,
        minus,
        mult,
        devide,
        LP,
        RP,
        COS,
        SIN,
        EXP,
        POW,
        END
    };

    TOKEN current_token;
    double current_number;

    const double PI = 3.14159265359;

public:

    Parser() {m_expression = "";}
    Parser(const std::string& expression);

    double getAnswer();
    void setExpression(const std::string& expression){m_expression = expression; }

private:

    //parse with sum or number
    double parse_expr();

    double parse_term();

    double parse_factor();

    void getNextToken();

    bool isNumber();

    double getNumber();

    void skip_void();

    bool checkCos();

    bool checkSin();

    bool checkExp();

    bool checkPI();

};