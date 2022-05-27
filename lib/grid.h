#ifndef GRID_H
#define GRID_H

#include <vector>

struct Index
{
    size_t row;
    size_t col;

    Index() = default;
    Index(size_t row, size_t col)
        : row(row),
          col(col) {}

    bool is_in_range(const Index &max)
    {
        return row >= 0 && row < max.row && col >= 0 && col < max.col;
    }

    bool is_in_range(const Index &min, const Index &max)
    {
        return row >= min.row && row < max.row && col >= min.col && col < max.col;
    }
};

std::vector<size_t>
range(size_t end)
{
    std::vector<size_t> res(end);
    for (auto i = 0u; i < end; ++i)
        res.at(i) = i;
    return res;
}

template <typename T>
class Grid
{
private:
    std::vector<T> _data;
    size_t _rows;
    size_t _cols;

public:
    Grid() = default;
    Grid(size_t rows, size_t cols)
        : _data(cols * rows), _rows(rows), _cols(cols) {}

    Grid(size_t rows, size_t cols, T initial_value) : Grid(rows, cols)
    {
        for (auto &e : _data)
            e = initial_value;
    }

    Grid(size_t rows, size_t cols, T(initializer)(void)) : Grid(rows, cols)
    {
        for (auto &e : _data)
            e = initializer();
    }

    Grid(size_t rows, size_t cols, T(initializer)(size_t row, size_t col)) : Grid(rows, cols)
    {
        for (auto row : this->rows())
            for (auto col : this->cols())
                at(row, col) = initializer(row, col);
    }

    T &at(size_t row, size_t col) { return _data.at(row * _cols + col); }
    T atConst(size_t row, size_t col) const
    {
        return _data.at(row * _cols + col);
    } // means just the get constant safe

    std::vector<Index> get_neighbours(size_t row, size_t col) const
    {
        std::vector<Index> result;
        for (auto i = -1; i <= 1; i++)
        {
            for (auto j = -1; j <= 1; j++)
            {
                if (i == 0 && j == 0)
                    continue;

                Index index(row + i, col + j);
                if (index.is_in_range(max_index()))
                    result.push_back(index);
            }
        }
        return result;
    }

    size_t row_size() const { return _rows; }
    size_t col_size() const { return _cols; }
    size_t total_size() const { return _data.size(); }

    Index max_index() const { return Index(_rows, _cols); }

    std::vector<size_t> rows() const { return range(_rows); }
    std::vector<size_t> cols() const { return range(_cols); }
};

#endif