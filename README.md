## A Propositional logic parser
- Supported logical operators:
    - AND (&)
    - OR (|)
    - NOT (!)
    - Implication (->)
    - Biconditional (<->)

#### Notes:
    - only underscores and numbers are allowed in variable names whitespaces are ignored and variables starting with a number is not allowed.
    - in this program the operator precedence of the operators are as follows:
        () > ! > & > | > -> > <->

### Steps to run the program
    make sure you have gcc installed

    1. Clone the repo:
    ```bash
        git clone https://github.com/Anish-Bikram-Nembang/propositional_parser.git
    ```
    2. cd into it:
    ```bash
        cd propositional_parser
    ```
    3. compile and run the program
    ```bash
        g++ ./src/main.cpp ./src/lexer/lexer.cpp ./src/parser/parser.cpp && ./a.out
    ```

