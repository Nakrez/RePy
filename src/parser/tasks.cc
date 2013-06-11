#include <parser/tasks.hh>

# include <iostream>

namespace parser
{
    void parse_input_file()
    {
        Driver driver;
        driver.parse_file(typy::input_name);

        driver.error_get().throw_if_needed();
    }
} // namespace parser
