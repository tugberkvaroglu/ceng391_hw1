#include "ceng391/image.hpp"

#include <fstream>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <limits>

using namespace std;

namespace ceng391 {

bool safe_multiply(size_t a, size_t b, size_t& result) {
    if (a == 0 || b == 0) {
        result = 0;
        return true;
    }
    if (a > std::numeric_limits<size_t>::max() / b) {
        return false;
    }
    result = a * b;
    return true;
}

Image::Image(int width, int height, int step, int n_channels)
    : m_width(width), m_height(height), m_n_channels(n_channels)
{
    if (n_channels != 1 && n_channels != 3 && n_channels != 4) {
        cerr << "Error: n_channels must be 1, 3, or 4!" << endl;
        exit(1);
    }

    if (step < m_width * m_n_channels)
        step = m_width * m_n_channels;
    m_step = step;

    size_t data_size;
    if (!safe_multiply(m_step, m_height, data_size)) {
        cerr << "Error: Memory allocation size overflow!" << endl;
        exit(1);
    }

    cout << "Allocating memory: " << data_size << " bytes" << endl;

    m_data = new (nothrow) uchar[data_size];
    if (!m_data) {
        cerr << "Error: Memory allocation failed!" << endl;
        exit(1);
    }

    cout << "Memory allocation successful!" << endl;
}

Image::~Image()
{
    delete[] m_data;
}

void Image::set(uchar value)
{
    if (m_n_channels == 1) {
        set_rect(0, 0, m_width, m_height, value);
    } else if (m_n_channels == 3) {
        set_rgb(value, value, value);
    } else if (m_n_channels == 4) {
        set_rgba(value, value, value, 255);
    }
}

void Image::set_rgb(uchar r, uchar g, uchar b)
{
    set_rect_rgb(0, 0, m_width, m_height, r, g, b);
}

void Image::set_rgba(uchar r, uchar g, uchar b, uchar a)
{
    set_rect_rgba(0, 0, m_width, m_height, r, g, b, a);
}

void Image::set_rect(int x_tl, int y_tl, int width, int height, uchar value)
{
    if (x_tl < 0) {
        width += x_tl;
        x_tl = 0;
    }

    if (y_tl < 0) {
        height += y_tl;
        y_tl = 0;
    }

    size_t length = min(width, m_width - x_tl);
    int y_max = min(y_tl + height, m_height);
    for (int y = y_tl; y < y_max; ++y) {
        uchar *row_y = data(y) + x_tl;
        memset(row_y, value, length);
    }
}

void Image::set_rect_rgb(int x_tl, int y_tl, int width, int height, uchar r, uchar g, uchar b)
{
    if (m_n_channels != 3) {
        throw runtime_error("set_rect_rgb can only be called on an RGB image");
    }

    if (x_tl < 0) {
        width += x_tl;
        x_tl = 0;
    }

    if (y_tl < 0) {
        height += y_tl;
        y_tl = 0;
    }

    size_t length = min(width, m_width - x_tl);
    int y_max = min(y_tl + height, m_height);
    for (int y = y_tl; y < y_max; ++y) {
        uchar *row_y = data(y) + x_tl * m_n_channels;
        for (size_t x = 0; x < length; ++x) {
            row_y[x * 3 + 0] = r;
            row_y[x * 3 + 1] = g;
            row_y[x * 3 + 2] = b;
        }
    }
}

void Image::set_rect_rgba(int x_tl, int y_tl, int width, int height, uchar r, uchar g, uchar b, uchar a)
{
    if (m_n_channels != 4) {
        throw runtime_error("set_rect_rgba can only be called on an RGBA image");
    }

    if (x_tl < 0) {
        width += x_tl;
        x_tl = 0;
    }

    if (y_tl < 0) {
        height += y_tl;
        y_tl = 0;
    }

    size_t length = min(width, m_width - x_tl);
    int y_max = min(y_tl + height, m_height);
    for (int y = y_tl; y < y_max; ++y) {
        uchar *row_y = data(y) + x_tl * m_n_channels;
        for (size_t x = 0; x < length; ++x) {
            row_y[x * 4 + 0] = r;
            row_y[x * 4 + 1] = g;
            row_y[x * 4 + 2] = b;
            row_y[x * 4 + 3] = a;
        }
    }
}

void Image::write_pnm(const std::string& filename) const
{
    ofstream fout;
    string extended_name = filename + ".ppm";
    fout.open(extended_name.c_str(), ios::out | ios::binary);

    if (m_n_channels == 1) {
        fout << "P5\n";
        fout << m_width << " " << m_height << " 255\n";
        for (int y = 0; y < m_height; ++y) {
            const uchar *row_data = this->data(y);
            fout.write(reinterpret_cast<const char*>(row_data), m_width * sizeof(uchar));
        }
    } else {
        fout << "P6\n";
        fout << m_width << " " << m_height << " 255\n";
        for (int y = 0; y < m_height; ++y) {
            const uchar *row_data = this->data(y);
            for (int x = 0; x < m_width; ++x) {
                fout.write(reinterpret_cast<const char*>(&row_data[x * m_n_channels]), 3 * sizeof(uchar));
            }
        }
    }

    fout.close();
}

}
