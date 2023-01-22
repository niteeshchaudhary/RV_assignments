#include <iostream>
#include <string>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace x3 = boost::spirit::x3;

// Define the AST (Abstract Syntax Tree) structure
struct binary_op;
struct unary_op;
struct expression;

using expression_ast = x3::variant<
    double,
    x3::forward_ast<binary_op>,
    x3::forward_ast<unary_op>
>;

struct binary_op {
    char op;
    expression_ast left, right;
};

struct unary_op {
    char op;
    expression_ast operand;
};

// Define the grammar
x3::rule<class expression_rule, expression_ast> const expression_rule = "expression";
auto const expression_def = x3::double_ | x3::rule<binary_op>{'(' >> expression_rule >> x3::char_("+-") >> expression_rule >> ')'};
BOOST_SPIRIT_DEFINE(expression_rule)

int main() {
    std::string input = "(2 + 3) * 4";
    auto begin = input.begin();
    expression_ast parsed_expr;
    bool success = x3::phrase_parse(begin, input.end(), expression_rule, x3::space, parsed_expr);

    if (success && begin == input.end()) {
        // The parse was successful
        std::cout << "Parsing succeeded: " << parsed_expr << std::endl;
    } else {
        // The parse failed
        std::cout << "Parsing failed" << std::endl;
    }
    return 0;
}
