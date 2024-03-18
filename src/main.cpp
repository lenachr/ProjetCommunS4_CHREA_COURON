// #include <cstdlib>
// #include "glm/fwd.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include <vector>
#include "boid.hpp"
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

    // initialisation des boids
    std::vector<Boid> boids{};
    // Ajout dans le vector des position aléatoire pour les boids
    for (int i = 0; i < 10; i++)
    {
        boids.push_back(Boid{
            /*position = */ glm::vec2{p6::random::number(-1.f, 0.7f), p6::random::number(-1.f, 0.7f)},
            /*rotation =*/glm::vec2{p6::random::number(-0.9f, 0.9f), p6::random::number(-0.9f, 0.9f)},
            // glm::vec2{0.f, 0.f},
            /*speed = */ glm::vec2(p6::random::number(-0.005f, 0.005f), p6::random::number(-0.005f, 0.005f)),
        });
    }

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Blue);
        ctx.fill = {1, 0, 0, 0.5};
        ctx.square(
            p6::Center{0, 0}, p6::Radius{1.0f}
        );
        for (int i = 0; i < boids.size(); i++)
        {
            boids[i].draw(&ctx);
            boids[i].update(boids);
        }
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
    // position = 1;
}