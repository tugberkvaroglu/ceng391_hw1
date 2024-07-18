#include <string>

namespace ceng391 {
typedef unsigned char uchar;

class Image
{
public:
    Image(int width, int height, int step=-1, int n_channels=1);
    ~Image();

    int w() const { return m_width; }
    int h() const { return m_height; }
    int step() const { return m_step; }
    int n_channels() const { return m_n_channels; }

    const uchar *data() const { return m_data; }
    uchar *      data()       { return m_data; }
    const uchar *data(int y) const { return m_data + y*m_step; }
    uchar *      data(int y)       { return m_data + y*m_step; }

    void set(uchar value);
    void set_rgb(uchar r, uchar g, uchar b);
    void set_rgba(uchar r, uchar g, uchar b, uchar a = 255);

    void set_rect(int x_tl, int y_tl, int width, int height, uchar value);
    void set_rect_rgb(int x_tl, int y_tl, int width, int height, uchar r, uchar g, uchar b);
    void set_rect_rgba(int x_tl, int y_tl, int width, int height, uchar r, uchar g, uchar b, uchar a = 255);

    void write_pnm(const std::string& filename) const;
    void read_pnm(const std::string& filename);

    void to_rgb();
    void to_grayscale();
    void to_rgba();

private:
    int m_n_channels;
    int m_width;
    int m_height;
    int m_step;

    uchar *m_data;
};

}
