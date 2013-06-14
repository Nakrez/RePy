#include <parser/driver.hh>

namespace parser
{
    Driver::Driver()
    {}

    Driver::~Driver()
    {}

    misc::Error& Driver::error_get()
    {
        return error_;
    }

    void Driver::parse_file(const std::string& filename)
    {
        std::string old_file = file_;

        file_ = filename;

        yy::tpy_parser parser(*this);
        parser.set_debug_level(true);
        scan_begin();
        parser.parse();
        scan_end();

        file_ = old_file;
    }
} // namespace parser
