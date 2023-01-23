#include <iostream>
#include <string>
#include <stack>
#include <memory>

enum class TokenType {
    NUMBER,
    OPERATOR,
    LEFT_PAREN,
    RIGHT_PAREN,
    END
};

struct Token {
    TokenType type;
    double value;
    char op;

    Token(TokenType type, double value = 0, char op = 0) : type(type), value(value), op(op) {}
};

class Parser {
public:
    Parser(std::string input) : input_(input), pos_(0) {}

    std::unique_ptr<class Node> Parse();

private:
    std::unique_ptr<class Node> ParseExpression();
    std::unique_ptr<class Node> ParseTerm();
    std::unique_ptr<class Node> ParseFactor();

    Token NextToken();

    std::string input_;
    int pos_;
};

class Node {
public:
    virtual double Evaluate() = 0;
};

class NumberNode : public Node {
public:
    NumberNode(double value) : value_(value) {}

    double Evaluate() override { return value_; }

private:
    double value_;
};

class BinaryOperatorNode : public Node {
public:
    BinaryOperatorNode(char op, std::unique_ptr<Node> left, std::unique_ptr<Node> right) : op_(op), left_(std::move(left)), right_(std::move(right)) {}

    double Evaluate() override {
        double left = left_->Evaluate();
        double right = right_->Evaluate();

        switch (op_) {
            case '+': return left + right;
            case '-': return left - right;
            case '*': return left * right;
            case '/': return left / right;
            default: throw std::runtime_error("Invalid operator");
        }
    }

private:
    char op_;
    std::unique_ptr<Node> left_;
    std::unique_ptr<Node> right_;
};

std::unique_ptr<Node> Parser::Parse() {
    return ParseExpression();
}

std::unique_ptr<Node> Parser::ParseExpression() {
    std::unique_ptr<Node> left = ParseTerm();

    while (true) {
        Token token = NextToken();

        if (token.type == TokenType::OPERATOR) {
            char op = token.op;
            std::unique_ptr<Node> right = ParseTerm();
            left = std::make_unique<BinaryOperatorNode>(op, std::move(left), std::move(right));
        } else {
            pos_--;
            return left;
        }
    }
}
std::unique_ptr<Node> Parser::ParseTerm() {
    std::unique_ptr<Node> left = ParseFactor();

    while (true) {
        Token token = NextToken();

        if (token.type == TokenType::OPERATOR) {
            char op = token.op;
std::unique_ptr<Node> right = ParseFactor();
switch (op) {
case '*': left = std::make_unique<BinaryOperatorNode>(op, std::move(left), std::move(right)); break;
case '/': left = std::make_unique<BinaryOperatorNode>(op, std::move(left), std::move(right)); break;
default: pos_--; return left;
}
} else {
pos_--;
return left;
}
}
}

std::unique_ptr<Node> Parser::ParseFactor() {
Token token = NextToken();

if (token.type == TokenType::NUMBER) {
    return std::make_unique<NumberNode>(token.value);
} else if (token.type == TokenType::OPERATOR) {
    char op = token.op;
    std::unique_ptr<Node> operand = ParseFactor();
    return std::make_unique<BinaryOperatorNode>(op, std::move(operand));
} else if (token.type == TokenType::LEFT_PAREN) {
    std::unique_ptr<Node> expr = ParseExpression();
    token = NextToken();

    if (token.type != TokenType::RIGHT_PAREN) {
        throw std::runtime_error("Mismatched parentheses");
    }

    return expr;
} else {
    throw std::runtime_error("Unexpected token");
}
}

Token Parser::NextToken() {
while (pos_ < input_.size() && input_[pos_] == ' ') {
pos_++;
}

if (pos_ >= input_.size()) {
    return Token(TokenType::END);
}

char c = input_[pos_];

if (c >= '0' && c <= '9') {
    double value = 0;
    int start = pos_;

    while (pos_ < input_.size() && input_[pos_] >= '0' && input_[pos_] <= '9') {
pos_++;
}

    value = std::stod(input_.substr(start, pos_ - start));
    return Token(TokenType::NUMBER, value);
} else if (c == '+' || c == '-' || c == '*' || c == '/') {
    pos_++;
    return Token(TokenType::OPERATOR, 0, c);
} else if (c == '(') {
    pos_++;
    return Token(TokenType::LEFT_PAREN);
} else if (c == ')') {
    pos_++;
    return Token(TokenType::RIGHT_PAREN);
} else {
    throw std::runtime_error("Unexpected character");
}
}

int main() {
std::string input = "(2 + 3) * 4";
Parser parser(input);
std::unique_ptr<Node> parse_tree = parser.Parse();

double result = parse_tree->Evaluate();

std::cout << "Result: " << result << std::endl;

return 0;
}

