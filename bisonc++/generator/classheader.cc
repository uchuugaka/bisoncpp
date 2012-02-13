#include "generator.ih"

// New members and other facilites may be added to the parser's class header
// after its initial generation. 

// Writing a base class header may be forced by the --force-class-header
// option. Otherwise, it's not rewritten by bisonc++ once it's available

void Generator::classHeader() const
{
    if 
    (
        access(d_options.classHeader().c_str(), F_OK) == 0
        &&
        not d_arg.option(0, "force-class-header")
    )
        return;

    ofstream out;
    ifstream in;

    Errno::open(in,  d_options.classSkeleton()); 
    Errno::open(out, d_options.classHeader()); 

    filter(in, out);    
}
