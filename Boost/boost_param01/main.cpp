#include <iostream>
#include <boost/program_options.hpp>

using std::cout;
using std::endl;
namespace opt = boost::program_options;

int main(int argc, char *argv[])
{
    opt::options_description desc("All options");
    desc.add_options()
        ("apples", opt::value<int>(), "how many apples do you have")
        ("oranges", opt::value<int>(), "how many oranges do you have")
        ("help", "produce help message");
        
    if (argc < 2) {
        cout << desc << endl;
        return EXIT_FAILURE;
    }
    
    opt::variables_map vm;
    opt::store(opt::parse_command_line(argc, argv, desc), vm);
    opt::notify(vm);

    if (vm.count("help")) {
        cout << desc << endl;
        return 1;
    }
    
    cout << "Fruits count: " << vm["apples"].as<int>() + vm["oranges"].as<int>() << endl;
    
    return EXIT_SUCCESS;
}
