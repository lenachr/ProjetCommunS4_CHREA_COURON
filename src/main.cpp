#include <cstdlib>
#include "glm/fwd.hpp"
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

    std::vector<glm::vec2> center;
    std::vector<glm::vec2> number;
    std::vector<glm::vec2> rotation;
    for (float i = 0; i < 5; i++)
    {
        center.emplace_back(p6::random::number(-1.f, 1.f));
        number.emplace_back(p6::random::number(-1.f, 1.f));
        rotation.emplace_back(p6::random::number(-1.f, 1.f));
    }

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Blue);
        ctx.fill = {1, 0, 0, 0.5};
        ctx.square(
            p6::Center{0, 0}, p6::Radius{1.0f}
        );
        for (float i = 0; i < 5; i++)
        {
            ctx.fill = {0, 0, 1, 0.5};

            // void triangle(Point2D, Point2D, Point2D, Center = {}, Rotation = {});
            ctx.triangle(
                p6::Point2D{0.1f, 0.1f}, p6::Point2D{0.25f, 0.2f}, p6::Point2D{0.2f, 0.25f}, p6::Center{center[i].x, number[i].y}

            );
        }
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
    // position = 1;
}