#pragma once

#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Field
{
private:
    enum Direction
    {
        Left,
        Right,
        Up,
        Down
    };
    const uint16_t Multipliers[7]{
        3, 7, 16, 36, 80, 200, 1000};

private:
    uint32_t m_score;
    uint16_t m_deleted_count;
    uint16_t m_rows;
    uint16_t m_columns;
    uint16_t m_cell_count;

    std::vector<std::vector<uint16_t>> m_field;

private:
    sf::RectangleShape m_cell;
    sf::Color m_colors[6];

private:
    void compact();
    void increaseScore();
    bool adjacentCells(uint16_t x, uint16_t y, uint16_t color);
    void deleteNeighborCell(int16_t x, int16_t y, uint16_t color, Direction direction);

public:
    Field();
    ~Field();

    void Init();

    bool isWinning();
    bool isGameOver();

    [[maybe_unused]] bool
    deleteCell(sf::Vector2i position);
    void createField(uint16_t column, uint16_t row, uint16_t colors);

    void Draw(sf::RenderWindow &window);

private:
    uint16_t getScore() const { return m_score; }
    uint16_t getRows() const { return m_rows; }
    uint16_t getColumns() const { return m_columns; }
    sf::Color &getCellColor(uint16_t row, uint16_t col);
};
