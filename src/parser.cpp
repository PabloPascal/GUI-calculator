#include "parser.hpp"



Parser::Parser(const std::string& expression){
    m_expression = expression;
}

double Parser::getAnswer(){
    double res;
    try{
        getNextToken();
        res = parse_expr();
    }catch(const char* exp){
        std::cerr << exp << std::endl;
    }
    return res;
}


    //parse with sum or number
double Parser::parse_expr(){

    double left = parse_term();

    while(current_token == TOKEN::plus || current_token == TOKEN::minus){

        TOKEN op = current_token;
        getNextToken();
        double right = parse_term();

        switch (op)
        {
        case TOKEN::plus:
            left += right;
            break;
        case TOKEN::minus:
            left -= right;
            break;
        }
    }

    return left;
}


double Parser::parse_term(){

        double left = parse_factor(); 

        while(current_token == TOKEN::mult || current_token == TOKEN::devide){
            
            TOKEN op = current_token;
            getNextToken();
            double right = parse_factor();

            switch (op)
            {
                case TOKEN::mult:
                    left *= right;
                    break;
                case TOKEN::devide:
                {
                    if(right == 0){
                        throw "DEVIDE BY ZERO\n";
                    }
                    else{
                        left /= right; 
                    }
                    break;
                }

            }//switch
        }
        return left;
    }


double Parser::parse_factor(){

    double result;
    switch (current_token)
        {
    case TOKEN::number:
    {
        result = current_number;
        getNextToken();
        break;
    }
    case TOKEN::minus:
    {
        result = -current_number;
    getNextToken();
    break;
    }
    case TOKEN::LP:
    {
            getNextToken();
       result = parse_expr();
       if(current_token != TOKEN::RP) throw "EXPECTED )\n";
       
       getNextToken();
       break;
    }
    case TOKEN::COS:
    {
        getNextToken();
        result = std::cos(parse_factor());
        break;
    }
    case TOKEN::SIN:
    {
        getNextToken();
        result = std::sin(parse_factor());
        break;
    }
    case TOKEN::EXP:
    {
        getNextToken();
        result = std::exp(parse_factor());
        break;
    }
    default:
        throw "EXPECTED PRIMARY\n";
        break;
    }

    if (current_token == TOKEN::POW)
    {
        getNextToken();
        result = std::pow(result, parse_factor());
    }

    return result;
}


void Parser::getNextToken(){

        skip_void();

        if(index >= m_expression.size()) {
            current_token = TOKEN::END;
        return;
    }
    char c = m_expression[index];
    switch (c)
    {
    case '+':
        current_token = TOKEN::plus; 
        index++;
        break;
    case '-':
        current_token = TOKEN::minus;
        index++;
        break;
    case '*':
        current_token = TOKEN::mult;
        index++;
        break;
    case '/':
        current_token = TOKEN::devide;
        index++;
        break;
    case '(':
        current_token = TOKEN::LP;
        index++;
        break;
    case ')':
        current_token = TOKEN::RP;
        index++;
        break;
    case 'c':
    {
        if(checkCos()){
            current_token = TOKEN::COS;
            index += 3;
        }else{
            throw "Undefined symbol\n";
        }
        break;
    }
    case 's':
    {
        if(checkSin()){
            current_token = TOKEN::SIN;
            index += 3;
        }else{
            throw "Undefined symbol\n";
        }
        break;
    }
    case 'e':
    {
        if(checkExp()){
            current_token = TOKEN::EXP;
            index += 3;
        }else{
            throw "Undefined symbol\n";
        }
        break;
    }
    case '^':
    {
        current_token = TOKEN::POW;
        index++;
        break;
    }
    default:
        if(c >= '0' && c <= '9' || c == '.'){
            current_token = TOKEN::number;
            current_number = getNumber();
            return;
        }else if(c == 'P'){
            if(checkPI()){
                current_token = TOKEN::number;
                current_number = PI;
                index += 2;
                return;
            }else{
                throw "UNDEFINED SYMBOL\n";
            }
        }
        else
            throw "UNDEFINED\n";
        break;
    }

}


bool Parser::isNumber(){

    char c = m_expression[index];

    if(c >= '0' && c <= '9' || c == '.')
    {
        return true;
    }
    return false;
}


double Parser::getNumber(){

    std::string numb = "";

    while(isNumber()){
        numb += m_expression[index];
        index++;
    }
    return std::stod(numb);
}

void Parser::skip_void(){
    while(m_expression[index] == ' ' && index < m_expression.size()){
        index++;
    }
}


bool Parser::checkCos(){
    if(m_expression[index] == 'c' && m_expression[index + 1] == 'o' && m_expression[index + 2] == 's'){
        return true;
    }
    return false;
}

bool Parser::checkSin(){
    if(m_expression[index] == 's' && m_expression[index + 1] == 'i' && m_expression[index + 2] == 'n'){
        return true;
    }
    return false;
}

bool Parser::checkExp(){
    if(m_expression[index] == 'e' && m_expression[index + 1] == 'x' && m_expression[index + 2] == 'p'){
        return true;
    }
    return false;
}
bool Parser::checkPI(){
    if(m_expression[index] == 'P' && m_expression[index + 1] == 'I'){
        return true;
    }
    return false;
}


