// #include <cstdlib>
// #include "glm/fwd.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "boids.hpp"
#include "doctest/doctest.h"
// #include "p6/p6.h"

int main()
{
    // Run the tests
    if (doctest::Context{}.run() != 0)
        return EXIT_FAILURE;

    // Actual application code
    auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};
    ctx.maximize_window();

    // initialisation des boids
    Boids boids = Boids{};
    // position aléatoire
    glm::vec4 position = boids.position();
    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Blue);
        ctx.fill = {1, 0, 0, 0.5};
        ctx.square(
            p6::Center{0, 0}, p6::Radius{1.0f}
        );
        boids.create(&ctx, position);
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
    // position = 1;
}