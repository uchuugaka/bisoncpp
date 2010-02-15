#include "writer.ih"

void Writer::srTable(State const *sp,  std::string const &baseclassScope,
                     FBB::Table &table, std::ostream &out)
{
    bool acceptState = sp->isAcceptState();

    StateItem const *defaultReduction = 
                         sp->reduction(sp->defaultReduction());

        // A token is needed if there are terminaltransitions or multiple
        // reductions (or for the accept state, set at state/define.cc)
    bool tokenNeeded = sp->terminalTransitions() || sp->reductions() > 1;

    int stateType = sp->type();

    if (tokenNeeded)
        stateType |= State::REQ_TOKEN;

    if (defaultReduction)
        stateType |= State::DEF_RED;


    out << "\n"                     // Write the table header
        "SR__ " << s_threadConst << "s_" << sp->idx() << "[] =\n"
        "{\n";

    table.clear();

    table << State::typeName(stateType) << 
            sp->transitions() + sp->reductionsLAsize() + acceptState + 1 <<
            def;

    transitions(table, sp->next());

    if (acceptState)
        table << Rules::eofTerminal() << "PARSE_ACCEPT" << def;

    reductions(table, *sp);        

    table << 0 << 
        (defaultReduction ? -static_cast<int>(defaultReduction->nr()) : 0) <<
        def;

    out << table << "};\n";             // table ends in a newline
}








