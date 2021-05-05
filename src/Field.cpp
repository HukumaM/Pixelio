#include "Field.hpp"

Field::Field()
    : m_score(0),
      m_deleted_count(0),
      m_rows(20),
      m_columns(20),
      m_cell_count(400),
      m_field(m_rows, std::vector<uint16_t>(m_columns, 0))

{
    m_colors[0] = sf::Color::White;
    m_colors[1] = sf::Color::Red;
    m_colors[2] = sf::Color::Green;
    m_colors[3] = sf::Color::Blue;
    m_colors[4] = sf::Color::Yellow;
    m_colors[5] = sf::Color::Magenta;
}

Field::~Field()
{
}

void Field::createField(uint16_t column, uint16_t row, uint16_t colors)
{
    m_columns = column;
    m_rows = row;
    m_cell_count = column * row;

    m_field.resize(m_rows);
    for (auto &row : m_field)
    {
        row.resize(m_columns);
        for (auto &cell : row)
        {
            cell = (rand() % colors) + 1;
        }
    }
    m_cell.setSize(sf::Vector2f(800.f / m_columns, 800.f / m_rows));
}

void Field::Init()
{
    m_cell.setSize(sf::Vector2f(800.f / m_columns, 800.f / m_rows));
    m_cell.setOutlineColor(sf::Color::Black);
    m_cell.setOutlineThickness(-1);
}

void Field::increaseScore()
{
    auto score = m_score;
    auto index = (m_deleted_count / 10 > 6 ? 6 : m_deleted_count / 10);
    m_score += m_deleted_count * Multipliers[index];

    std::cout << m_deleted_count << " : "
              << m_score - score << " : "
              << m_score << std::endl;
    m_deleted_count = 0;
}

void Field::deleteNeighborCell(int16_t x, int16_t y, uint16_t color, Direction direction)
{
    if (x >= 0 && x < m_columns && y >= 0 && y < m_rows)
    {
        if (m_field.at(y).at(x) == color)
        {
            m_field.at(y).at(x) = 0;
            m_cell_count--;
            m_deleted_count++;

            if (direction != Direction::Left)
            {
                deleteNeighborCell(x + 1, y, color, Direction::Right);
            }
            if (direction != Direction::Right)
            {
                deleteNeighborCell(x - 1, y, color, Direction::Left);
            }
            if (direction != Direction::Up)
            {
                deleteNeighborCell(x, y + 1, color, Direction::Down);
            }
            if (direction != Direction::Down)
            {
                deleteNeighborCell(x, y - 1, color, Direction::Up);
            }
        }
    }
}

bool Field::adjacentCells(uint16_t x, uint16_t y, uint16_t color)
{
    return (x - 1 >= 0 && m_field.at(y).at(x - 1) == color) ||
           (x + 1 < m_columns && m_field.at(y).at(x + 1) == color) ||
           (y - 1 >= 0 && m_field.at(y - 1).at(x) == color) ||
           (y + 1 < m_rows && m_field.at(y + 1).at(x) == color);
}

void Field::compact()
{
    for (size_t column{0}; column < getColumns(); ++column)
    {
        int16_t empty_row{getRows() - 1};
        int16_t filled_row{empty_row};

        while (empty_row >= 0 && filled_row >= 0)
        {
            while (empty_row >= 0 && m_field.at(empty_row).at(column) != 0)
            {
                empty_row--;
            }

            if (empty_row >= 0)
            {
                filled_row = empty_row - 1;

                while (filled_row >= 0 && m_field.at(filled_row).at(column) == 0)
                {
                    filled_row--;
                }

                if (filled_row >= 0)
                {
                    m_field.at(empty_row).at(column) =
                        m_field.at(filled_row).at(column);

                    m_field.at(filled_row).at(column) = 0;
                }
            }
        }
    }

    int16_t empty_column{0};
    int16_t occupied_column{empty_column};

    while (empty_column < getColumns() && occupied_column < getColumns())
    {
        while (empty_column < getColumns() &&
               m_field.at(getRows() - 1).at(empty_column) != 0)
        {
            empty_column++;
        }

        if (empty_column < getColumns())
        {
            occupied_column = empty_column + 1;

            while (occupied_column < getColumns() &&
                   m_field.at(getRows() - 1).at(occupied_column) == 0)
            {
                occupied_column++;
            }

            if (occupied_column < getColumns())
            {
                for (size_t row{0}; row < getRows(); ++row)
                {
                    m_field.at(row).at(empty_column) = m_field.at(row).at(occupied_column);
                    m_field.at(row).at(occupied_column) = 0;
                }
            }
        }
    }
}

[[maybe_unused]] bool
Field::deleteCell(sf::Vector2i position)
{
    uint16_t x_pos = position.x / (800 / m_columns);
    uint16_t y_pos = position.y / (800 / m_rows);

    x_pos = (x_pos >= m_columns ? m_columns - 1 : x_pos);
    y_pos = (y_pos >= m_rows ? m_rows - 1 : y_pos);

    // std::cout << position.x << ':' << position.y << std::endl;
    // std::cout << x_pos << ':' << y_pos << std::endl;
    //std::cout << m_cell_count << std::endl;

    const auto color = m_field.at(y_pos).at(x_pos);

    if (m_field.at(y_pos).at(x_pos))
    {
        if (adjacentCells(x_pos, y_pos, color))
        {
            m_field.at(y_pos).at(x_pos) = 0;
            m_cell_count--;
            m_deleted_count++;

            deleteNeighborCell(x_pos - 1, y_pos, color, Direction::Left);
            deleteNeighborCell(x_pos + 1, y_pos, color, Direction::Right);
            deleteNeighborCell(x_pos, y_pos - 1, color, Direction::Up);
            deleteNeighborCell(x_pos, y_pos + 1, color, Direction::Down);

            increaseScore();

            compact();
            return true;
        }
    }
    return false;
}

sf::Color &Field::getCellColor(uint16_t row, uint16_t col)
{
    return m_colors[m_field.at(row).at(col)];
}

bool Field::isWinning()
{
    return !m_cell_count;
}

bool Field::isGameOver()
{
    for (int16_t y{0}; y < getRows(); ++y)
    {
        for (int16_t x{0}; x < getColumns(); ++x)
        {
            int16_t color = m_field.at(y).at(x);

            if (color)
            {
                if (y - 1 >= 0 && m_field.at(y - 1).at(x) == color)
                {
                    return false;
                }
                if (x + 1 < getColumns() && m_field.at(y).at(x + 1) == color)
                {
                    return false;
                }
            }
        }
    }
    if (!m_cell_count)
    {
        return false;
    }
    return true;
}

void Field::Draw(sf::RenderWindow &window)
{
    for (size_t y{0}; y < m_field.size(); ++y)
    {
        for (size_t x{0}; x < m_field.at(y).size(); ++x)
        {
            if (x == m_field.at(y).size() - 1)
            {
            }
            m_cell.setPosition(x * 800.f / m_columns, y * 800.f / m_rows);
            m_cell.setFillColor(m_colors[m_field.at(y).at(x)]);
            window.draw(m_cell);
        }
    }
}
