#ifndef _INCLUDED_WRITER_
#define _INCLUDED_WRITER_

#include <iosfwd>
#include <string>

#include <bobcat/table>

#include "../support/support.h"
#include "../next/next.h"

class Terminal;
class NonTerminal;
class Production;
class StateItem;
class State;
class Rules;

class Writer
{
    std::ostream *d_out;
    std::string const &d_baseclass;
    Rules const &d_rules;

    public:
        Writer(std::string const &baseclass, Rules const &rules);
        void useStream(std::ostream &out);

        void productions() const;
        void srTables() const;
        void statesArray() const;
        void symbolicNames() const;
        void insert(Terminal::ConstVector const &tokens) const;

    private:
        struct TokenContext
        {
            size_t lastValue;
            std::ostream &out;
        };
        static void insert(Terminal const *token, TokenContext &context);

        static void terminalSymbol(Terminal const *terminal, 
                                    std::ostream &out);
        static void nonTerminalSymbol(NonTerminal const *nonTerminal, 
                                    std::ostream &out);
        static void srTable();

        struct SRContext
        {
            std::string const &baseclassScope;
            FBB::Table &table;
            std::ostream &out;
        };

        static void productionInfo(Production const *production, 
                                   std::ostream &out);
        static void srTable(State const *state, SRContext &sac);
        static void transitions(FBB::Table &table, Next::Vector const &next);
        static void transition(Next const &next, FBB::Table &table);

        static void reductions(FBB::Table &, State const &state);
        static void reduction(FBB::Table &, StateItem const &stateItem);

        struct ReductionContext
        {
            size_t ruleNr;
            FBB::Table &table;
        };
        static void reduction(Element const *sym, ReductionContext &context);
};

inline void Writer::useStream(std::ostream &out)
{
    d_out = &out;
}

#endif
