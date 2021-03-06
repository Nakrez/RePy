#include <tasks/task-invoker.hh>

namespace tasks
{
    TaskInvoker::TaskInvoker()
    {}

    TaskInvoker::~TaskInvoker()
    {}

    TaskInvoker& TaskInvoker::instance()
    {
        static TaskInvoker inst;

        return inst;
    }

    static error_t parse_opt(int key, char* arg, struct argp_state* state)
    {
        switch (key)
        {
            case ARGP_KEY_ARG:
                if (state->arg_num >= 1)
                    argp_usage(state);
                else
                    *((char**)state->input) = arg;

                return 0;
            case ARGP_KEY_END:
                if (state->arg_num < 1)
                    argp_usage(state);

                return 0;
            default:
                for (auto it : TaskRegister::instance().registered_tasks_get())
                {
                    if (it->key_get() == key)
                    {
                        TaskInvoker::instance().enable_task(it);
                        return 0;
                    }
                }

                return ARGP_ERR_UNKNOWN;
        }
    }

    char* TaskInvoker::parse_argv(int argc, char* argv[])
    {
        const std::list<BasicTask*>* tasks_list = nullptr;
        tasks_list = &TaskRegister::instance().registered_tasks_get();

        size_t tasks_size = tasks_list->size() + 1;
        struct argp_option available_options[tasks_size];
        size_t task_counter = 0;

        std::memset(available_options, 0, sizeof (argp_option) * tasks_size);

        for (auto it : *tasks_list)
        {
            available_options[task_counter].name = it->long_opt_get().c_str();
            available_options[task_counter].key = it->key_get();
            available_options[task_counter].arg = nullptr;
            available_options[task_counter].flags = 0;
            available_options[task_counter].doc = it->description_get().c_str();
            available_options[task_counter].group = 0;

            ++task_counter;
        }

        argp_child child[1] = { {nullptr, 0, nullptr, 0} };

        struct argp argp =
        {
            available_options,
            parse_opt,
            "INPUT",
            "TyPy is a python compiler.",
            child,
            nullptr,
            nullptr
        };

        char* input_filename;
        argp_parse(&argp, argc, argv, 0, 0, &input_filename);

        return input_filename;
    }

    void TaskInvoker::run()
    {
        for (auto it : tasks_to_run_)
            it->run();
    }

    bool TaskInvoker::is_enable(const std::string& s)
    {
        for (auto t : tasks_to_run_)
        {
            if (t->long_opt_get() == s)
                return true;
        }

        return false;
    }

    void TaskInvoker::enable_task(BasicTask* task)
    {
        if (task->dep_get() != "")
        {
            std::istringstream stream(task->dep_get());

            do
            {
                std::string dep;
                stream >> dep;

                if (!is_enable(dep))
                {
                    for (auto t : TaskRegister::instance().registered_tasks_get())
                    {
                        if (t->long_opt_get() == dep)
                        {
                            enable_task(t);
                            break;
                        }
                    }
                }
            }
            while (stream);
        }

        tasks_to_run_.push_back(task);
    }
} // namespace tasks
