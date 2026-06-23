#include "Application.hpp"

int main() {
    Application* app = new Application();
    
    app->init();
    app->run();
    
    delete app;
    return 0;
}