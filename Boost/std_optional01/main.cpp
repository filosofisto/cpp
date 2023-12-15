#include <optional>
#include <iostream>

class locked_device
{
    explicit locked_device(const char* /* param */) 
    {
        std::cout << "Device is locked\n";
    }

    static bool try_lock_device_impl()
    {
        std::cout << "Lock implementation running...\n";
        return true;
    }
    
public:
    void use()
    {
        std::cout << "Success!\n";
    }
    
    static std::optional<locked_device> try_lock_device()
    {
        if (!try_lock_device_impl()) {
            // Failed to lock device
            return std::nullopt;
        }
        
        // Success!
        return locked_device("device name");
    }
    
    ~locked_device()
    {
        // Release device lock
    }
};

int main()
{
    for (unsigned i = 0; i < 10; ++i) {
        std::optional<locked_device> t = locked_device::try_lock_device();
        
        if (t) {
            t->use();
            return EXIT_SUCCESS;
        } else {
            std::cout << "...trying again\n";
        }
    }
    
    std::cout << "Failure!\n";
    return EXIT_FAILURE;
}
