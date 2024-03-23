// #include <cstdlib>
// #include "glm/fwd.hpp"
#include <imgui.h>
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

    // initialisation des boids et des coefficients des règles de base
    std::vector<Boid> boids{};
    int               boids_number     = 1;
    float             alignement_coeff = 0.1f;
    float             cohesion_coeff   = 0.1f;
    float             separation_coeff = 0.01f;
    // Ajout dans le vector des position aléatoire pour les boids
    for (int i = 0; i < 50; i++)
    {
        boids.push_back(Boid{
            /*position = */ glm::vec2{p6::random::number(-1.f, 0.7f), p6::random::number(-1.f, 0.7f)},
            /*speed = */ glm::vec2(p6::random::number(-0.005f, 0.001f), p6::random::number(-0.005f, 0.001f)),
        });
    }

    // Declare your infinite update loop.
    ctx.update = [&]() {
        // Show a simple window
        ImGui::Begin("Choice of parameters");
        ImGui::SliderInt("Number of boids", &boids_number, 1, 50);
        ImGui::SliderFloat("Alignement distance", &alignement_coeff, 0, 0.3);
        ImGui::SliderFloat("Cohesion distance", &cohesion_coeff, 0, 0.3);
        ImGui::SliderFloat("Separation distance", &separation_coeff, 0, 0.1);
        ImGui::End();
        ctx.background(p6::NamedColor::Blue);
        ctx.fill = {1, 0, 0, 0.5};
        ctx.square(
            p6::Center{0, 0}, p6::Radius{1.0f}
        );
        for (int i = 0; i < boids_number; i++)
        {
            boids[i].draw(&ctx);
            boids[i].update(boids, alignement_coeff, cohesion_coeff, separation_coeff);
        }
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}