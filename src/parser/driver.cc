#include <parser/driver.hh>

namespace parser
{
    Driver::Driver()
        : ast_(nullptr)
    {}

    Driver::~Driver()
    {}

    misc::Error& Driver::error_get()
    {
        return error_;
    }

    ast::Ast* Driver::parse_file(const std::string& filename)
    {
        std::string old_file = file_;
        ast::Ast* old = ast_;

        file_ = filename;

        yy::tpy_parser parser(*this);
        // parser.set_debug_level(true);
        scan_begin();
        parser.parse();
        scan_end();

        std::swap(ast_, old);

        file_ = old_file;

        return old;
    }

    void Driver::ast_set(ast::Ast* ast)
    {
        ast_ = ast;
    }
} // namespace parser
