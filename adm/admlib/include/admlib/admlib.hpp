#pragma once

#ifndef ADMLIB_LIB_HPP
#define ADMLIB_LIB_HPP
#include <SFML/Graphics.hpp>
#include <vector>

class Bezier {
public:
    static std::vector<sf::Vector2f> generateBezierCurve(const std::vector<sf::Vector2f>& controlPoints);
    static void saveBezierCurveToPNG(const std::vector<sf::Vector2f>& bezierCurve, const std::string& filename);
};
#endif