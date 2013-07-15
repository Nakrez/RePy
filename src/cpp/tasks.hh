#ifndef CPP_TASKS_HH
# define CPP_TASKS_HH

# include <cassert>

# include <repy.hh>

# include <tasks/libtasks.hh>

# include <cpp/code-generator.hh>
# include <cpp/header-generator.hh>

namespace cpp
{
    REGULAR_TASK("c|cpp-generator", "Generate C++ code from python input",
                 "global-desugar", cpp_generator);
    REGULAR_TASK("h|header-generator", "Generate C++ header from python input",
                 "global-desugar", header_generator);
} // namespace cpp

#endif /* !CPP_TASKS_HH */
