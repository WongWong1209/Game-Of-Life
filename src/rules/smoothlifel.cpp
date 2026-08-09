#include "grid.h"
#include <algorithm>

static float smoothStep(
    float edge1,
    float edge2,
    float value
) {
    float t = (value - edge1) / (edge2 - edge1);
    t = std::clamp(t, 0.0f, 1.0f);

    return t * t * (3.0f - 2.0f * t);
}

static float smoothRange(
    float value,
    float lower,
    float upper,
    float smoothness
) {
    float enter = smoothStep(
        lower - smoothness,
        lower + smoothness,
        value
    );

    float leave = 1.0f - smoothStep(
        upper - smoothness,
        upper + smoothness,
        value
    );

    return enter * leave;
}

static float slrGraph(
    float liveRateInCircle,
    float liveRateNeighbors
) {
    constexpr float SMOOTHNESS = 0.03f;

    if (liveRateInCircle < 0.5f) {
        // born range
        return smoothRange(
            liveRateNeighbors,
            0.257f,
            0.336f,
            SMOOTHNESS
        );
    }

    // keep alive range
    return smoothRange(
        liveRateNeighbors,
        0.365f,
        0.549f,
        SMOOTHNESS
    );
}

void smoothLifeLRule(
    Cell grid[GRID_WIDTH][GRID_HEIGHT]
) {
    constexpr int INNER_RADIUS = 3;
    constexpr int OUTER_RADIUS = 9;

    constexpr int INNER_RADIUS_SQUARED =
        INNER_RADIUS * INNER_RADIUS;

    constexpr int OUTER_RADIUS_SQUARED =
        OUTER_RADIUS * OUTER_RADIUS;

    static Cell newGrid[GRID_WIDTH][GRID_HEIGHT];

    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            int totalInCircle = 0;
            int totalNeighbors = 0;

            float lifeInCircle = 0.0f;
            float lifeNeighbors = 0.0f;

            for (
                int circleX = x - OUTER_RADIUS;
                circleX <= x + OUTER_RADIUS;
                circleX++
            ) {
                for (
                    int circleY = y - OUTER_RADIUS;
                    circleY <= y + OUTER_RADIUS;
                    circleY++
                ) {
                    int deltaX = circleX - x;
                    int deltaY = circleY - y;

                    int wrappedX =
                        (circleX + GRID_WIDTH) % GRID_WIDTH;
                    int wrappedY =
                        (circleY + GRID_HEIGHT) % GRID_HEIGHT;

                    int distanceSquared =
                        deltaX * deltaX +
                        deltaY * deltaY;

                    // transfer alpha to life
                    float cellLife =
                        grid[wrappedX][wrappedY].life;

                    // inner circle
                    if (
                        distanceSquared <=
                        INNER_RADIUS_SQUARED
                    ) {
                        totalInCircle++;
                        lifeInCircle += cellLife;
                    }

                    // outer circle
                    else if (
                        distanceSquared <=
                        OUTER_RADIUS_SQUARED
                    ) {
                        totalNeighbors++;
                        lifeNeighbors += cellLife;
                    }
                }
            }

            float liveRateInCircle = 0.0f;
            float liveRateNeighbors = 0.0f;

            if (totalInCircle > 0) {
                liveRateInCircle =
                    lifeInCircle /
                    static_cast<float>(totalInCircle);
            }

            if (totalNeighbors > 0) {
                liveRateNeighbors =
                    lifeNeighbors /
                    static_cast<float>(totalNeighbors);
            }

            float nextState = slrGraph(
                liveRateInCircle,
                liveRateNeighbors
            );

            nextState = std::clamp(
                nextState,
                0.0f,
                1.0f
            );

            newGrid[x][y] = Cell{
                nextState,
                255,
                255,
                255
            };
        }
    }

    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            grid[x][y] = newGrid[x][y];
        }
    }
}
