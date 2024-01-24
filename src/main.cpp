#include <cstdlib>
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include "p6/p6.h"

int main()
{
    // Run the tests
    if (doctest::Context{}.run() != 0)
        return EXIT_FAILURE;

    // Actual application code
    auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};
    ctx.maximize_window();

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Blue);
        ctx.circle(
            p6::Center{ctx.mouse()},
            p6::Radius{0.2f}
        );
        ctx.fill = {1, 0, 0, 0.5};
        ctx.square(
            p6::Center{0, 0}, p6::Radius{1.0f}
        );
        for (float i = 0; i < 5; i++)
        {
            ctx.fill = {0, 0, 1, 0.5};

            // void triangle(Point2D, Point2D, Point2D, Center = {}, Rotation = {});
            ctx.triangle(
                p6::Point2D{0.1f, 0.1f}, p6::Point2D{0.3f, 0.2f}, p6::Point2D{0.2f, 0.3f}, p6::Center{p6::random::number(-1.f, 1.f), p6::random::number(-1.f, 1.f)}
            );
        }
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
    // position = 1;
}