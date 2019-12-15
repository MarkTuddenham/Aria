#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <Aria.hpp>

int main(int argc, char *argv[])
{
    // Turn off logging and profiling.

    Aria::Log::init(Aria::Log::Level::NONE);
    // Instrumentor::Get().BeginSession("Aria");

    int result = Catch::Session().run(argc, argv);

    // Instrumentor::Get().EndSession();

    return result;
}
