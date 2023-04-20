#include <TncEngine.hpp>

class Sanbox : public TncEngine::Application
{
public:
    Sanbox() {}
    ~Sanbox() {}
};

TncEngine::Application* TncEngine::CreateApplication()
{
    return new Sanbox();
}