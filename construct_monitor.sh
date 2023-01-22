#!/bin/bash

# Read the property file
property_file=$1
formula=$(cat $property_file)

echo formula;

#tree = Make Parse tree

# Generate the C program
echo "#include <stdio.h>" > test_monitor.c
echo "" >> test_monitor.c
echo "int evaluate_tree(char *atomic_props, int *truth_values) {" >> test_monitor.c
echo "    // Code to evaluate the tree using the truth values of the atomic propositions" >> test_monitor.c
echo "}" >> test_monitor.c
echo "" >> test_monitor.c
echo "int main() {" >> test_monitor.c
echo "    // Read the names of the atomic propositions from the input file" >> test_monitor.c
echo "    char atomic_props[100];" >> test_monitor.c
echo "    scanf("%s", atomic_props);" >> test_monitor.c
echo "" >> test_monitor.c
echo "    // Read the truth values of the atomic propositions at each time step" >> test_monitor.c
echo "    int time = 0;" >> test_monitor.c
echo "    while (!feof(stdin)) {" >> test_monitor.c
echo "        int truth_values[100];" >> test_monitor.c
echo "        for (int i = 0; i < strlen(atomic_props); i++) {" >> test_monitor.c
echo "            scanf("%d", &truth_values[i]);" >> test_monitor.c
echo "        }" >> test_monitor.c
echo "" >> test_monitor.c
echo "        // Evaluate the parsed tree using the truth values of the atomic propositions" >> test_monitor.c
echo "        int verdict = evaluate_tree(atomic_props, truth_values);" >> test_monitor.c
echo "" >> test_monitor.c
echo "        // Write the verdict to the output file" >> test_monitor.c
echo "        fprintf(verdict_file, \"%d\\n\", verdict);" >> test_monitor.c
echo "        time++;" >> test_monitor.c
echo "    }" >> test_monitor.c
echo "" >> test_monitor.c
echo "    return 0;" >> test_monitor.c
echo "}" >> test_monitor.c
