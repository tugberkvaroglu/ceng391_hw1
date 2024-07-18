#include <cstdlib>
#include <iostream>

#include "ceng391/image.hpp"

using namespace std;
using ceng391::Image;

int main(int /*argc*/, char** /*argv*/)
{
    try {
        // Test for grayscale image
        cout << "Creating grayscale image..." << endl;
        Image img_gray(320, 240, -1, 1);
        cout << "Created grayscale image of size (" << img_gray.w() << "x" << img_gray.h() << ")!" << endl;
        img_gray.set(255);
        img_gray.set_rect(100, -50, 1000, 150, 0);
        img_gray.write_pnm("test_img_gray");

        // Test for RGB image
        cout << "Creating RGB image..." << endl;
        Image img_rgb(320, 240, -1, 3);
        cout << "Created RGB image of size (" << img_rgb.w() << "x" << img_rgb.h() << ")!" << endl;
        img_rgb.set_rgb(255, 0, 0);
        img_rgb.set_rect_rgb(50, 50, 100, 100, 0, 255, 0);
        img_rgb.write_pnm("test_img_rgb");

        // Test for RGBA image
        cout << "Creating RGBA image..." << endl;
        Image img_rgba(320, 240, -1, 4);
        cout << "Created RGBA image of size (" << img_rgba.w() << "x" << img_rgba.h() << ")!" << endl;
        img_rgba.set_rgba(0, 0, 255, 128);
        img_rgba.set_rect_rgba(150, 150, 50, 50, 255, 255, 0, 128);
        img_rgba.write_pnm("test_img_rgba");

     // Test for reading a grayscale image
        cout << "Reading grayscale image..." << endl;
        Image img_gray_read(1, 1);  // Temporary dimensions
        img_gray.read_pnm("test_img_gray.ppm");
        cout << "Read grayscale image of size (" << img_gray.w() << "x" << img_gray.h() << ")!" << endl;
        img_gray.write_pnm("read_test_img_gray");

        // Test for reading a RGB image
        cout << "Reading RGB image..." << endl;
        Image img_rgb_read(1, 1);  // Temporary dimensions
        img_rgb.read_pnm("test_img_rgb.ppm");
        cout << "Read RGB image of size (" << img_rgb.w() << "x" << img_rgb.h() << ")!" << endl;
        img_rgb.write_pnm("read_test_img_rgb");

        // Test for reading an RGBA image
        cout << "Reading RGBA image..." << endl;
        Image img_rgba_read(1, 1);  // Temporary dimensions
        img_rgba.read_pnm("test_img_rgba.ppm");
        cout << "Read RGBA image of size (" << img_rgba.w() << "x" << img_rgba.h() << ")!" << endl;
        img_rgba.write_pnm("read_test_img_rgba");

    } catch (const std::exception& ex) {
        cerr << "Exception caught: " << ex.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/// Local Variables:
/// mode: c++
/// compile-command: "make -C ../build image-test"
/// End:
