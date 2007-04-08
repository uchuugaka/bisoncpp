#ifndef Parser_h_included
#define Parser_h_included

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "../rulevalue/_rulevalue.h"

// $insert baseclass
#include "parserbase.h"
// $insert scanner.h
#include "../scanner/scanner.h"


#undef Parser
class Parser: public ParserBase
{
    public:
        typedef std::map<std::string, RuleValue::Function>  FunctionMap;
        typedef std::map<std::string, double>               DoubleMap;

    private:
        enum AngleType
        {
            RADIANS,
            DEG360,
            DEG400
        };
    
        typedef std::map<std::string, size_t>               SymbolMap;

        struct ShowVar
        {
            std::vector<RuleValue> &d_value;
            ShowVar(std::vector<RuleValue> &value);
            void operator()(SymbolMap::value_type &v);
        };

        // $insert scannerobject
        Scanner d_scanner;

        std::string d_lastIdent;
        AngleType   d_angleType;
        bool        d_error;

        SymbolMap               d_symtab;
        std::vector<RuleValue>  d_value;
    
        static FunctionMap  s_functions;
        static DoubleMap    s_doubles;
        
    public:
        Parser();
        int parse();

    private:
        RuleValue call(RuleValue const &funName, RuleValue &argv);

        void error(char const *msg);    // called on (syntax) errors
                                        // called on semantic errors
        void error(bool ifTrue, char const *msg); 

        
        int lex();                      // returns the next token from the
                                        // lexical scanner. 
        void print();                   // use, e.g., d_token, d_loc

        RuleValue       &addArg(RuleValue &argv, RuleValue &arg);
        double          angle(double radians);
        RuleValue       &assign(RuleValue &lvalue, int operation,
                                       RuleValue const &rvalue);
        RuleValue       binary(RuleValue lvalue, int operation,
                                       RuleValue const &rvalue);
        void            display(RuleValue const &e);
        void            div0(RuleValue const &vl, RuleValue const &vr);
        RuleValue       firstArg(RuleValue &rv);

        RuleValue       function(RuleValue const &fun, RuleValue const &e);
        RuleValue       function(RuleValue const &fun,
                            RuleValue const &arg1, RuleValue const &arg2);

        void            integral(RuleValue const &v1);
        void            help();
        void            integral(RuleValue const &v1, RuleValue const &v2);
        void            list();
        RuleValue       &lvalue(RuleValue &e);
        RuleValue       mathConst();
        void            prompt();
        double          radians(double angle);
        RuleValue const &rvalue(RuleValue const &e) const;
        void            setAngleType();
        RuleValue       setDataType();
        RuleValue       setFunction();
        void            storeIdent();
        RuleValue       unary(int operation, RuleValue const &e);
        RuleValue       newValue(int typeToken);
        RuleValue       variable();
        RuleValue       identValue();

    // support functions for parse():
        void executeAction(int ruleNr);
        void errorRecovery();
        int lookup(bool recovery);
        void nextToken();
};

inline Parser::Parser()
:
    d_value(1)
{}

// $insert lex
inline int Parser::lex()
{
    return d_scanner.yylex();
}

inline void Parser::print()      // use d_token, d_loc
{}

inline Parser::ShowVar::ShowVar(std::vector<RuleValue> &value)
:
    d_value(value)
{}

inline RuleValue &Parser::addArg(RuleValue &argv, RuleValue &arg)
{
    return argv.push_arg(arg);
}

#endif


