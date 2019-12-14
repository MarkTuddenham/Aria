#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <DarkChess.hpp>

int main(int argc, char *argv[])
{
    DarkChess::Log::init();
    Instrumentor::Get().BeginSession("DarkChess");

    int result = Catch::Session().run(argc, argv);

    Instrumentor::Get().EndSession();

    return result;
}
