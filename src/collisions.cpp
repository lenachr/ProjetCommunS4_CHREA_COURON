#include <FreeflyCamera.hpp>
#include "p6/p6.h"

// Gère les collisions
void collisions(const auto& ctx, FreeflyCamera& freeflyCamera, bool upPressed, bool downPressed, bool leftPressed, bool rightPressed, float move, bool collisionDetectedUp, bool collisionDetectedDown, bool collisionDetectedLeft, bool collisionDetectedRight)
{
    if (upPressed)
    {
        collisionDetectedUp = true;
        if (ctx->key_is_pressed(GLFW_KEY_W))
        {
            freeflyCamera.moveFront(-move);
        }
    }
    else
    {
        collisionDetectedUp = false;
    }
    if (downPressed)
    {
        collisionDetectedDown = true;
        if (ctx->key_is_pressed(GLFW_KEY_S))
        {
            freeflyCamera.moveFront(move);
        }
    }
    else
    {
        collisionDetectedDown = false;
    }
    if (leftPressed)
    {
        collisionDetectedLeft = true;
        if (ctx->key_is_pressed(GLFW_KEY_A))
        {
            freeflyCamera.moveLeft(-move);
        }
    }
    else
    {
        collisionDetectedLeft = false;
    }
    if (rightPressed)
    {
        collisionDetectedRight = true;
        if (ctx->key_is_pressed(GLFW_KEY_D))
        {
            freeflyCamera.moveLeft(move);
        }
    }
    else
    {
        collisionDetectedRight = false;
    }
}