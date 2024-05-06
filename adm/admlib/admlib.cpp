#include <admlib/admlib.hpp>
#include <iostream>
#include <vector>
#include <random>

double bernsteinCoefficient(int i, int n, double t) {
    double choose = 1.0;
    for (int j = 1; j <= i; ++j) {
        choose *= (double)(n - j + 1) / j;
    }
    return choose * pow(t, i) * pow(1 - t, n - i);
}

std::vector<sf::Vector2f> Bezier::generateBezierCurve(const std::vector<sf::Vector2f>& controlPoints) {
    std::vector<sf::Vector2f> bezierCurve;
    for (double t = 0.0; t <= 1.0; t += 0.01) {
        sf::Vector2f point(0, 0);
        for (int i = 0; i < 4; ++i) {
            point += controlPoints[i] * static_cast<float>(bernsteinCoefficient(i, 3, t));
        }
        bezierCurve.push_back(point);
    }
    return bezierCurve;
}

void Bezier::saveBezierCurveToPNG(const std::vector<sf::Vector2f>& bezierCurve, const std::string& filename) {
    sf::RenderTexture texture;
    texture.create(500, 200);
    texture.clear(sf::Color::White);

    sf::VertexArray lines(sf::LineStrip);
    for (const auto& point : bezierCurve) {
        lines.append(sf::Vertex(point, sf::Color::Magenta));
    }

    texture.draw(lines);
    texture.display();

    sf::Image image = texture.getTexture().copyToImage();
    image.saveToFile(filename);
}