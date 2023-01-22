from plyplus import Grammar, STransformer

# Define the grammar for the expressions
grammar = r"""
    start: add;
    ?add: (mul | add "+" mul)*;
    ?mul: (primary | mul "*" primary)*;
    ?primary: number | "(" add ")";
    number: '\d+(\.\d+)?';
"""

# Create a transformer to convert the parse tree into a more usable format
class CalcTransformer(STransformer):
    def number(self, node):
        return float(node.tail[0])
    def add(self, node):
        if len(node.tail) == 1:
            return node.tail[0]
        else:
            return node.tail[0] + node.tail[2]
    def mul(self, node):
        if len(node.tail) == 1:
            return node.tail[0]
        else:
            return node.tail[0] * node.tail[2]
    def primary(self, node):
        return node.tail[0]

# Build the parser
parser = Grammar(grammar)

# Define the input expression
expr = "(2 + 3) * 4"

# Parse the expression and transform the parse tree
parse_tree = parser.parse(expr)
result = CalcTransformer().transform(parse_tree)

# The final result is the evaluated expression
print(result) # Output: 20.0