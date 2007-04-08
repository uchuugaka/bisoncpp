#ifndef Parser_h_included
#define Parser_h_included

// $insert baseclass
#include "parserbase.h"
// $insert scanner.h
#include "../scanner/scanner.h"


#undef Parser
class Parser: public ParserBase
{
    // $insert scannerobject
    Scanner d_scanner;
        
    public:
        int parse();

    private:
        void error(char const *msg);    // called on (syntax) errors
        int lex();                      // returns the next token from the
                                        // lexical scanner. 
        void print();                   // use, e.g., d_token, d_loc

        void prompt();
        void done();

    // support functions for parse():
        void executeAction(int ruleNr);
        void errorRecovery();
        int lookup(bool recovery);
        void nextToken();
};

inline void Parser::error(char const *msg)
{
    std::cerr << msg << std::endl;
}

// $insert lex
inline int Parser::lex()
{
    return d_scanner.yylex();
}

inline void Parser::print()      // use d_token, d_loc
{}

inline void Parser::prompt()
{
    std::cout << "? " << std::flush;
}

inline void Parser::done()
{
    std::cout << "Done\n";
    ACCEPT();
}

#endif
