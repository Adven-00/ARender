#include <SFML/Graphics.hpp>

#include "../core/rasterizer.h"

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        glm::vec4 red(255.f, 0.f, 0.f, 255.f);
        glm::vec4 blue(0.f, 0.f, 255.f, 255.f);
        glm::vec4 yellow(0.f, 255.f, 0.f, 255.f);

        glm::vec4 pos_a(-0.5f, -0.5f, 0.1f, 1.f);
        glm::vec4 pos_b(0.5f, -0.5f, 0.1f, 1.f);
        glm::vec4 pos_c(0.f, 0.5f, 0.1f, 1.f);

        Vertex a;
        ShaderInput shader_input_a;
        shader_input_a.vec4_input["color"] = red;
        a.coord.world = pos_a;
        a.shader_input = shader_input_a;

        Vertex b;
        ShaderInput shader_input_b;
        shader_input_b.vec4_input["color"] = yellow;
        b.coord.world = pos_b;
        b.shader_input = shader_input_b;

        Vertex c;
        ShaderInput shader_input_c;
        shader_input_c.vec4_input["color"] = blue;
        c.coord.world = pos_c;
        c.shader_input = shader_input_c;

        VertexIndexList list = {{0, std::make_shared<Vertex>(a)},
                                {1, std::make_shared<Vertex>(b)},
                                {2, std::make_shared<Vertex>(c)}};

        const int w = 800;
        const int h = 600;

        Rasterizer r(w, h);
        r.SetVertexIndexList(list);
        r.DrawModel();

        auto fb = r.GetFrameBuffer();
        std::vector<sf::Vertex> vertices;

        for (int x = 0; x < w; x++) {
            for (int y = 0; y < h; y++) {
                glm::vec4 color = fb[x][y];
                vertices.push_back(sf::Vertex(sf::Vector2f(x, y), sf::Color(color.r, color.g, color.b)));
            }
        }
        window.draw(&vertices[0], w * h, sf::Points);

        // end the current frame
        window.display();
    }

    return 0;
}