// #include <cstdlib>
// #include "glm/fwd.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include <vector>
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

    // Vector pour avoir les différentes positions et vitesses des boids
    int                    nb_boids = 10;
    std::vector<glm::vec4> positions;
    std::vector<glm::vec2> speeds;

    // Ajout dans le vector des position aléatoire pour les boids
    for (int i = 0; i < nb_boids; i++)
    {
        positions.push_back(boids.position());
        speeds.push_back(glm::vec2(p6::random::number(-0.005f, 0.005f), p6::random::number(-0.005f, 0.005f)));
    }

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Blue);
        ctx.fill = {1, 0, 0, 0.5};
        ctx.square(
            p6::Center{0, 0}, p6::Radius{1.0f}
        );
        for (int i = 0; i < nb_boids; i++)
        {
            positions[i] = boids.speed(&speeds[i], positions[i]);
            boids.create(&ctx, positions[i]);
        }
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
    // position = 1;
}