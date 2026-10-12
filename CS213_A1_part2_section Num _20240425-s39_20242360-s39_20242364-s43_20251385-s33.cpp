

/*
Team members:
    •	Kinzy Ahmad Raouf
            {ID:20240425}
             Section: S39,40

    •	Mai Sabry Shapaan
            {ID: 20242360}
             Section: S39,40

    •	Nadeen Osama
            {ID: 20242364}
             Section:S43,44

    •	Marwa Mohamed
            {ID:20251385}
            Section:S33,34





Solves Filters:
        -Filters 1 & 5 & 9  & 13 solved by Kinzy Ahmed
        -Filters 2 & 6 & 10 & 14 solved by Mai Sabry
        -Filters 3 & 7 & 11 & 15 solved by Nadeen Osama
        -Filters 4 & 8 & 12 & 16 solved by Marwa Mohamed
        (Repo & Menu & README & BONUS FILTERS 17,18 and GUI are common between all members)

        ----



Project Links:https://github.com/maisabry-5/Assignment-1-oop.git

     Video Link :https://drive.google.com/drive/folders/1RXyCFM-2BeTHPh4msZNPQdXrSCR9kLHd

     Repo link :https://github.com/maisabry-5/Assignment-1-oop.git

     Document Link :https://docs.google.com/document/d/1vvKj7y3Uugc-Ry0TGnhq8RDZLo8p8fueu4_pe-Qvypc/edit?usp=sharing


*/

// =====================================================================
//  CS213 Photo Editor - Win32 GUI version
//
//  File layout (read it top to bottom):
//    PART 1  - Includes and settings
//    PART 2  - The 18 image filters (original code, adapted so they take
//              their parameters as arguments instead of using cin/cout)
//    PART 3  - Application state, colours, helper functions
//    PART 4  - File operations (open / save, using Windows dialogs)
//    PART 5  - Preview rendering (RGB -> BGR bitmap -> GDI)
//    PART 6  - Applying filters (validation + running the filter)
//    PART 7  - Window layout and drawing the dark/purple theme
//    PART 8  - Window procedures (event handling)
//    PART 9  - WinMain
//
//  Save this file next to Image_Class.h, stb_image.h and stb_image_write.h
// =====================================================================

// ---------------------------------------------------------------------
// PART 1 - Includes
// ---------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#define NOMINMAX              // stop windows.h from defining min/max macros
#define WIN32_LEAN_AND_MEAN

// Windows headers first, then standard headers, and Image_Class.h LAST
// (it defines macros such as "ll" and "pixel" that could clash with others).
#include <windows.h>
#include <commdlg.h>
#include <windowsx.h>

#include <string>
#include <vector>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cwchar>
#include <cwctype>
#include <cerrno>
#include <new>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include "Image_Class.h"

// We do NOT use "using namespace std;" because it clashes with Windows
// types (std::byte vs byte) in C++17. We import only what we need.
using std::string;
using std::wstring;
using std::vector;
using std::min;
using std::max;
using std::swap;

// ---------------------------------------------------------------------
// PART 2 - FILTERS (original code, GUI-friendly signatures)
// ---------------------------------------------------------------------
// FILTERS_BEGIN

//  Grayscale Filter 
void GrayscaleFilter(Image& img) {
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            unsigned char r = img(x, y, 0);
            unsigned char g = img(x, y, 1);
            unsigned char b = img(x, y, 2);
            unsigned char gray = (r + g + b) / 3;
            img(x, y, 0) = gray;
            img(x, y, 1) = gray;
            img(x, y, 2) = gray;
        }
    }
}

//  Black & White Filter
void BW(Image& img)
{
    for (int j = 0; j < img.height; j++)
    {
        for (int i = 0; i < img.width; i++)
        {
            int avg = 0;
            for (int k = 0; k < 3; k++)
            {

                avg += img(i, j, k);
            }
            avg /= 3;
            unsigned char bw = (avg >= 128) ? 255 : 0;
            for (int k = 0; k < 3; k++)
            {
                img(i, j, k) = bw;
            }
        }
    }
}

//  Invert Image 
void Invert(Image& img) {
    for (int x = 0; x < img.height; x++) {
        for (int y = 0; y < img.width; y++) {
            for (int c = 0; c <= 2; c++) {
                unsigned char& new_pixel = img(y, x, c);
                new_pixel = 255 - new_pixel;
            }
        }
    }
}


void Frame(Image& img, int n) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            if (i < 10 || j < 10 || i >= img.width - 10 || j >= img.height - 10) {
                if (n == 1) {
                    img(i, j, 0) = 0;
                    img(i, j, 1) = 0;
                    img(i, j, 2) = 255;
                }
                else if (n == 2) {
                    img(i, j, 0) = 0;
                    img(i, j, 1) = 0;
                    img(i, j, 2) = 255;
                    if ((i < 20 && j < 20) || (i >= img.width - 20 && j < 20) ||
                        (i < 20 && j >= img.height - 20) || (i >= img.width - 20 && j >= img.height - 20)) {
                        img(i, j, 0) = 255;
                        img(i, j, 1) = 255;
                        img(i, j, 2) = 255;
                    }
                }
            }
        }
    }
}

//  Flip Image 
void Flip(Image& img) {
    for (int y = 0; y < img.height / 2; y++) {
        for (int x = 0; x < img.width; x++) {
            for (int c = 0; c < 3; c++) {
                swap(img(x, y, c), img(x, img.height - 1 - y, c));
            }
        }
    }
}

// Rotate Image 
void Rotate(Image& img)
{
    Image rotated_img(img.height, img.width);
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++)
        {
            for (int k = 0; k < img.channels; k++)
            {
                unsigned char value = img.getPixel(i, j, k);
                rotated_img.setPixel(j, rotated_img.height - 1 - i, k, value);
            }
        }
    }
    img = rotated_img;
}

void getAngle(Image& img, int rotateAngle)
{
    int rotations = rotateAngle / 90;
    while (rotations--) {
        Rotate(img);
    }
}

//  Darken & Lighten Image 

void DarkenandLighten(Image& img, bool darken, int constant) {
    if (darken) {
        for (int x = 0; x < img.height; x++) {
            for (int y = 0; y < img.width; y++) {
                for (int c = 0; c <= 2; c++) {
                    unsigned char& pixel_7 = img(y, x, c);
                    int value = pixel_7 - constant;
                    pixel_7 = (value >= 0) ? value : 0;
                }
            }
        }
    }
    else {
        for (int x = 0; x < img.height; x++) {
            for (int y = 0; y < img.width; y++) {
                for (int c = 0; c <= 2; c++) {
                    unsigned char& pixel_7 = img(y, x, c);
                    int value_2 = pixel_7 + constant;
                    pixel_7 = (value_2 < 255) ? value_2 : 255;
                }
            }
        }
    }
}

//  Resizing Images 
void Resize(Image& image, int target_w, int target_h) {
    Image image2(target_w, target_h);
    double avg = (double)image.width / target_w;
    double avg2 = (double)image.height / target_h;

    for (int i = 0; i < target_w; i++) {
        for (int j = 0; j < target_h; j++) {
            int orgx = min((int)(i * avg), image.width - 1);
            int orgy = min((int)(j * avg2), image.height - 1);
            for (int k = 0; k < image2.channels; ++k) {
                image2.setPixel(i, j, k, image.getPixel(orgx, orgy, k));
            }
        }
    }
    image = image2;
}

//  Merge Image 
void Merge(Image& imag1, Image& imag2) {
    int width = min(imag1.width, imag2.width);
    int height = min(imag1.height, imag2.height);
    Image merged(width, height);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int R = (imag1(x, y, 0) + imag2(x, y, 0)) / 2;
            int G = (imag1(x, y, 1) + imag2(x, y, 1)) / 2;
            int B = (imag1(x, y, 2) + imag2(x, y, 2)) / 2;
            merged(x, y, 0) = R;
            merged(x, y, 1) = G;
            merged(x, y, 2) = B;
        }
    }
    imag1 = merged;
}

// Resizes the SECOND image to the size of the first one, then merges.

void Merge_With_Resize(Image& img1, Image& img2) {
    if (img1.width != img2.width || img1.height != img2.height) {
        Resize(img2, img1.width, img1.height);
    }
    Merge(img1, img2);
}

//  Detect Image Edges 

Image EdgeDetection(Image grayscale)
{
    Image output(grayscale.width, grayscale.height);
    size_t totalBytes = (size_t)grayscale.width * grayscale.height * output.channels;
    for (size_t n = 0; n < totalBytes; n++) {
        output.imageData[n] = 255;
    }

    int threshold = 100;
    for (int i = 1; i < grayscale.width - 1; ++i) {
        for (int j = 1; j < grayscale.height - 1; ++j)
        {
            int gx = grayscale(i + 1, j - 1, 0) + 2 * grayscale(i + 1, j, 0) + grayscale(i + 1, j + 1, 0) - grayscale(i - 1, j - 1, 0) - 2 * grayscale(i - 1, j, 0) - grayscale(i - 1, j + 1, 0);
            int gy = grayscale(i - 1, j + 1, 0) + 2 * grayscale(i, j + 1, 0) + grayscale(i + 1, j + 1, 0) - grayscale(i - 1, j - 1, 0) - 2 * grayscale(i, j - 1, 0) - grayscale(i + 1, j - 1, 0);
            int magnitude = (int)sqrt((double)(gx * gx + gy * gy));
            unsigned char color = (magnitude > threshold) ? 0 : 255;
            output(i, j, 0) = color;
            output(i, j, 1) = color;
            output(i, j, 2) = color;
        }
    }
    return output;
}


bool Crop(Image& my_image, int new_x, int new_y, int new_w, int new_h) {
    if (new_w > 0 && new_h > 0 && new_x >= 0 && new_y >= 0 && new_x + new_w <= my_image.width && new_y + new_h <= my_image.height) {
        Image croped_image(new_w, new_h);
        for (int h = 0; h < new_h; h++) {
            for (int w = 0; w < new_w; w++) {
                for (int c = 0; c <= 2; c++) {
                    croped_image.setPixel(w, h, c, my_image.getPixel(w + new_x, h + new_y, c));
                }
            }
        }
        my_image = croped_image;
        return true;
    }
    return false;
}

//  Blur Image 
// FIX: a level below 0 made the inner loops run zero times, so "count" stayed
// 0 and "r / count" divided by zero (crash). The GUI only allows 1..20 and the
// division is also guarded here.
void Blur(Image& image2, int level) {
    Image image(image2.width, image2.height);

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int r = 0, g = 0, b = 0, count = 0;
            for (int x = -level; x <= level; x++) {
                for (int y = -level; y <= level; y++) {
                    if (i + x >= 0 && i + x < image2.width && j + y >= 0 && j + y < image2.height) {
                        r += image2(i + x, j + y, 0);
                        g += image2(i + x, j + y, 1);
                        b += image2(i + x, j + y, 2);
                        count++;
                    }
                }
            }
            if (count == 0) count = 1;
            image.setPixel(i, j, 0, r / count);
            image.setPixel(i, j, 1, g / count);
            image.setPixel(i, j, 2, b / count);
        }
    }
    image2 = image;
}


//Sunlight Correction
void SunlightCorrection(Image& img) {
    for (int x = 0; x < img.width; x++) {
        for (int y = 0; y < img.height; y++) {
            int R = img(x, y, 0);
            int G = img(x, y, 1);
            int B = img(x, y, 2);

            R = min(255, int(R * 1.2 + 20));
            G = min(255, int(G * 1.1 + 15));
            B = min(255, int(B * 0.95));

            img(x, y, 0) = R;
            img(x, y, 1) = G;
            img(x, y, 2) = B;
        }
    }
}

// Old TV Filter 
void applyOldTV(Image& image)
{
    const double dark1 = 0.85;
    const double dark2 = 0.9;
    const double redTint = 0.95;
    const double blueTint = 1.1;

    for (int y = 0; y < image.height; ++y)
    {
        for (int x = 0; x < image.width; ++x)
        {
            unsigned char r = image(x, y, 0);
            unsigned char g = image(x, y, 1);
            unsigned char b = image(x, y, 2);

            if (y % 4 == 0)
            {
                r = static_cast<unsigned char>(r * dark1);
                g = static_cast<unsigned char>(g * dark1);
                b = static_cast<unsigned char>(b * dark1);
            }
            else if (y % 4 == 2)
            {
                r = static_cast<unsigned char>(r * dark2);
                g = static_cast<unsigned char>(g * dark2);
                b = static_cast<unsigned char>(b * dark2);
            }

            r = static_cast<unsigned char>(min(255, int(r * redTint)));
            b = static_cast<unsigned char>(min(255, int(b * blueTint)));

            image(x, y, 0) = r;
            image(x, y, 1) = g;
            image(x, y, 2) = b;
        }
    }
}

//  Purple Filter 
void Purple(Image& img) {
    for (int x = 0; x < img.height; x++) {
        for (int y = 0; y < img.width; y++) {
            for (int c = 0; c <= 2; c++) {
                unsigned char& pixel_15 = img(y, x, c);
                int color = pixel_15;

                if (c == 0 || c == 2) {
                    if (color > 225) {
                        pixel_15 = 255;
                    }
                    else {
                        pixel_15 = color + 30;
                    }
                }
            }
        }
    }
}

//  Infrared Filter 
void infraredFilter(Image& image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int g = image(i, j, 1);
            int b = image(i, j, 2);

            image.setPixel(i, j, 0, 255);
            image.setPixel(i, j, 1, 255 - g);
            image.setPixel(i, j, 2, 255 - b);
        }
    }
}

//  Image Skewing / Warp (BONUS) 

Image warpImage(Image& image, double shear = 0.3) {
    int extra = (int)std::ceil(std::fabs(shear) * (image.height - 1));
    int newWidth = image.width + extra;
    Image result(newWidth, image.height);

    size_t totalBytes = (size_t)newWidth * image.height * result.channels;
    for (size_t n = 0; n < totalBytes; n++) {
        result.imageData[n] = 0;
    }

    for (int y = 0; y < image.height; y++) {
        int offset;
        if (shear >= 0) offset = (int)(shear * (image.height - 1 - y));
        else            offset = (int)(-shear * y);

        for (int x = 0; x < image.width; x++) {
            for (int c = 0; c < 3; c++) {
                result.setPixel(x + offset, y, c, image.getPixel(x, y, c));
            }
        }
    }
    return result;
}

//  Oil Painting (BONUS)
void oilPaint(Image& image, int radius = 3, int intensityLevels = 20)
{
    Image temp = image;
    for (int y = radius; y < image.height - radius; y++)
    {
        for (int x = radius; x < image.width - radius; x++)
        {
            vector<int> intensityCount(intensityLevels, 0);
            vector<int> rSum(intensityLevels, 0), gSum(intensityLevels, 0), bSum(intensityLevels, 0);

            for (int j = -radius; j <= radius; j++)
            {
                for (int i = -radius; i <= radius; i++)
                {
                    unsigned char r = temp(x + i, y + j, 0);
                    unsigned char g = temp(x + i, y + j, 1);
                    unsigned char b = temp(x + i, y + j, 2);

                    int intensity = (r + g + b) / 3 * intensityLevels / 255;
                    if (intensity >= intensityLevels) intensity = intensityLevels - 1;

                    intensityCount[intensity]++;
                    rSum[intensity] += r;
                    gSum[intensity] += g;
                    bSum[intensity] += b;
                }
            }

            int maxCount = 0, maxIndex = 0;
            for (int i = 0; i < intensityLevels; i++)
            {
                if (intensityCount[i] > maxCount)
                {
                    maxCount = intensityCount[i];
                    maxIndex = i;
                }
            }

            if (maxCount > 0)
            {
                image(x, y, 0) = rSum[maxIndex] / maxCount;
                image(x, y, 1) = gSum[maxIndex] / maxCount;
                image(x, y, 2) = bSum[maxIndex] / maxCount;
            }
        }
    }
}

// FILTERS_END

// ---------------------------------------------------------------------
// PART 3 - Application state, constants and small helpers
// ---------------------------------------------------------------------

// Ids of the 18 filters (also the order of the buttons in the list)
enum FilterIndex {
    FILTER_GRAYSCALE = 0, FILTER_BW, FILTER_INVERT, FILTER_FRAME, FILTER_FLIP,
    FILTER_ROTATE, FILTER_DARKLIGHT, FILTER_RESIZE, FILTER_MERGE, FILTER_EDGE,
    FILTER_CROP, FILTER_BLUR, FILTER_SUNLIGHT, FILTER_OLDTV, FILTER_PURPLE,
    FILTER_INFRARED, FILTER_WARP, FILTER_OIL,
    FILTER_COUNT
};

struct FilterInfo {
    const wchar_t* name;
    const wchar_t* help;      // short description shown in the settings panel
    bool needsSettings;       // true -> opens the settings panel first
};

const FilterInfo FILTERS[FILTER_COUNT] = {
    { L"Grayscale",                  L"Turns the image into shades of gray.", false },
    { L"Black and White",            L"Pure black and white (threshold at 128).", false },
    { L"Invert Colors",              L"Replaces every colour with its opposite (negative).", false },
    { L"Add Frame",                  L"Draws a 10 px blue frame around the image.", true },
    { L"Flip Vertically",            L"Flips the image upside down (top <-> bottom).", false },
    { L"Rotate",                     L"Rotates counter-clockwise by the chosen angle.", true },
    { L"Darken / Lighten",           L"Subtracts from (or adds to) every colour value.", true },
    { L"Resize",                     L"Changes the image to an exact width and height.", true },
    { L"Merge Images",               L"Blends the current image 50/50 with a second image.", true },
    { L"Edge Detection",             L"Black edges on a white background (Sobel).", false },
    { L"Crop",                       L"Keeps a rectangle: start point plus new size.", true },
    { L"Blur",                       L"Averages neighbouring pixels. Higher = blurrier.", true },
    { L"Sunlight Correction",        L"Warms the image: more red/green, less blue.", false },
    { L"Old TV",                     L"Dark scan lines with a bluish tint.", false },
    { L"Purple Filter",              L"Gives the whole image a purple tone.", false },
    { L"Infrared",                   L"Red channel to 255, green and blue inverted.", false },
    { L"Skew / Warp (BONUS)",        L"Leans the image sideways (horizontal shear).", true },
    { L"Oil Painting (BONUS)",       L"Painterly effect. Large radius = slow on big images.", true }
};

// Limits used by validation
const int MAX_RESIZE_SIDE = 8000;
const long long MAX_PIXELS = 60000000LL;   // ~180 MB of RGB data
const int MAX_BLUR_LEVEL = 20;
const int MAX_OIL_RADIUS = 10;
const int MIN_OIL_LEVELS = 2;
const int MAX_OIL_LEVELS = 64;

// Command ids of the controls
enum CommandId {
    CMD_OPEN = 100, CMD_SAVE, CMD_SAVE_AS, CMD_RESET,
    CMD_APPLY, CMD_CANCEL, CMD_PICK_SECOND,
    CMD_OPTION1, CMD_OPTION2, CMD_OPTION3,       // choice buttons (must be consecutive)
    CMD_EDIT1, CMD_EDIT2, CMD_EDIT3, CMD_EDIT4,  // number boxes (must be consecutive)
    CMD_FILTER_FIRST = 1000                      // 1000 .. 1017
};

// Theme colours (dark with purple accents)
const COLORREF COLOR_BG = RGB(22, 20, 33);
const COLORREF COLOR_PANEL = RGB(32, 29, 48);
const COLORREF COLOR_BUTTON = RGB(54, 49, 82);
const COLORREF COLOR_BUTTON_OFF = RGB(38, 35, 54);
const COLORREF COLOR_ACCENT = RGB(139, 92, 246);
const COLORREF COLOR_TEXT = RGB(236, 233, 248);
const COLORREF COLOR_MUTED = RGB(160, 154, 184);
const COLORREF COLOR_EDIT_BG = RGB(18, 16, 28);
const COLORREF COLOR_PREVIEW_BG = RGB(14, 12, 22);
const COLORREF COLOR_OK = RGB(110, 231, 160);
const COLORREF COLOR_ERROR = RGB(252, 129, 129);

// Layout sizes (pixels)
const int HEADER_H = 60;
const int TOOLBAR_H = 54;
const int STATUS_H = 30;
const int MARGIN = 10;
const int LEFT_W = 240;
const int RIGHT_W = 290;

// Parameters collected from the settings panel for one filter run
struct FilterParams {
    int option = 0;       // index of the chosen option button
    int a = 0, b = 0, c = 0, d = 0;   // numbers from the edit boxes
};

// Everything the program needs to remember lives in this one struct.
struct AppState {
    // window handles
    HWND hMain = nullptr, hFilterPanel = nullptr, hPreview = nullptr, hSettings = nullptr;
    HWND hOpen = nullptr, hSave = nullptr, hSaveAs = nullptr, hReset = nullptr;
    HWND hApply = nullptr, hCancel = nullptr, hPickSecond = nullptr;
    HWND hTitleLabel = nullptr, hHelpLabel = nullptr, hSecondLabel = nullptr;
    HWND hOption[3] = { nullptr, nullptr, nullptr };
    HWND hEdit[4] = { nullptr, nullptr, nullptr, nullptr };
    HWND hEditLabel[4] = { nullptr, nullptr, nullptr, nullptr };
    HWND filterButtons[FILTER_COUNT] = {};

    // GDI objects (created once, deleted at exit)
    HFONT fontNormal = nullptr, fontBold = nullptr, fontTitle = nullptr, fontSmall = nullptr;
    HBRUSH brushBg = nullptr, brushPanel = nullptr, brushEdit = nullptr, brushPreview = nullptr;

    // image states
    Image original;        // exactly as loaded from disk (used by Reset)
    Image working;         // the image the filters change
    Image secondImage;     // second image for Merge
    bool hasImage = false;
    bool hasSecond = false;
    bool modified = false;             // working image changed since last save/open
    bool pathIsOriginalFile = false;   // currentPath is the file we opened (not yet saved over)
    wstring currentPath;
    wstring secondName;

    // preview: a separate BGR copy of "working" used only for drawing
    vector<unsigned char> previewPixels;
    int previewStride = 0;

    // UI state
    int selectedFilter = -1;     // filter whose settings panel is open (-1 = none)
    int selectedOption = 0;
    int filterScroll = 0;
    wstring statusMessage;
    bool statusIsError = false;
};

AppState g;

// ---- small helpers -----------------------------------------------------

wstring FileNameOnly(const wstring& path) {
    size_t slash = path.find_last_of(L"\\/");
    return (slash == wstring::npos) ? path : path.substr(slash + 1);
}

// Returns the extension in lower case including the dot (".jpg"), or L"".
wstring GetLowerExtension(const wstring& path) {
    size_t slash = path.find_last_of(L"\\/");
    size_t dot = path.find_last_of(L'.');
    if (dot == wstring::npos || (slash != wstring::npos && dot < slash)) return L"";
    wstring ext = path.substr(dot);
    for (size_t i = 0; i < ext.size(); i++) ext[i] = (wchar_t)towlower(ext[i]);
    return ext;
}

bool IsSupportedExtension(const wstring& ext) {
    return ext == L".png" || ext == L".bmp" || ext == L".tga" || ext == L".jpg" || ext == L".jpeg";
}

wstring WidenAnsi(const char* text) {
    int len = MultiByteToWideChar(CP_ACP, 0, text, -1, nullptr, 0);
    if (len <= 0) return L"";
    wstring result(len, L'\0');
    MultiByteToWideChar(CP_ACP, 0, text, -1, &result[0], len);
    result.resize(len - 1);
    return result;
}

// Converts a wide path to the narrow (ANSI) string that Image_Class.h needs.
// Returns false if some characters cannot be represented.
bool ToNarrowPath(const wstring& wide, string& narrow) {
    BOOL usedDefault = FALSE;
    int len = WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, wide.c_str(), -1, nullptr, 0, nullptr, &usedDefault);
    if (len <= 0) return false;
    narrow.assign(len, '\0');
    WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, wide.c_str(), -1, &narrow[0], len, nullptr, &usedDefault);
    narrow.resize(len - 1);
    return !usedDefault;
}

wstring LastErrorText(DWORD code) {
    wchar_t* buffer = nullptr;
    DWORD len = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, code, 0, (LPWSTR)&buffer, 0, nullptr);
    wstring text = (len > 0 && buffer) ? wstring(buffer, len) : L"Unknown error";
    if (buffer) LocalFree(buffer);
    while (!text.empty() && (text.back() == L'\r' || text.back() == L'\n' || text.back() == L' ')) text.pop_back();
    return text;
}

// ---- messages ------------------------------------------------------------

void GetStatusRect(RECT& status) {
    RECT client;
    GetClientRect(g.hMain, &client);
    status = { 0, client.bottom - STATUS_H, client.right, client.bottom };
}

void SetStatus(const wstring& message, bool isError) {
    g.statusMessage = message;
    g.statusIsError = isError;
    if (g.hMain) {
        RECT status;
        GetStatusRect(status);
        InvalidateRect(g.hMain, &status, FALSE);
    }
}

// Error: red text in the status bar AND a message box so it cannot be missed.
void ShowError(const wstring& message) {
    SetStatus(message.substr(0, message.find(L'\n')), true);
    MessageBoxW(g.hMain, message.c_str(), L"CS213 Photo Editor - Error", MB_OK | MB_ICONERROR);
}

void ShowSuccess(const wstring& message) {
    SetStatus(message, false);
}

// ---------------------------------------------------------------------
// PART 4 - File operations
// ---------------------------------------------------------------------
// Image_Class.h takes narrow (ANSI) file names and only recognises LOWER-case
// extensions (".jpg" works, ".JPG" throws). To support any Windows path
// (spaces, non-English letters, upper-case extensions) we copy the file to a
// temporary file with a plain ASCII name and a lower-case extension, let
// Image_Class.h work on that copy, then delete it.

bool MakeTempFilePath(const wstring& ext, wstring& tempPath, wstring& error) {
    wchar_t tempDir[MAX_PATH + 1];
    DWORD len = GetTempPathW(MAX_PATH, tempDir);
    if (len == 0 || len > MAX_PATH) {
        error = L"Could not find the Windows temporary folder.";
        return false;
    }
    wchar_t shortDir[MAX_PATH + 1];
    DWORD shortLen = GetShortPathNameW(tempDir, shortDir, MAX_PATH);
    wstring dir = (shortLen > 0 && shortLen < MAX_PATH) ? wstring(shortDir) : wstring(tempDir);
    if (!dir.empty() && dir.back() != L'\\') dir += L'\\';

    static unsigned counter = 0;
    counter++;
    tempPath = dir + L"cs213pe_" + std::to_wstring(GetCurrentProcessId()) + L"_" + std::to_wstring(counter) + ext;
    return true;
}

bool LoadImageFile(const wstring& path, Image& outImage, wstring& error) {
    wstring ext = GetLowerExtension(path);
    if (!IsSupportedExtension(ext)) {
        error = L"Unsupported file type \"" + ext + L"\".\nPlease choose a JPG, JPEG, PNG, BMP or TGA image.";
        return false;
    }

    wstring tempPath;
    if (!MakeTempFilePath(ext, tempPath, error)) return false;

    if (!CopyFileW(path.c_str(), tempPath.c_str(), FALSE)) {
        error = L"Could not read the file:\n" + path + L"\n\n" + LastErrorText(GetLastError());
        return false;
    }

    string narrowTemp;
    bool ok = false;
    if (!ToNarrowPath(tempPath, narrowTemp)) {
        error = L"The Windows temporary folder path contains characters this program cannot use.";
    }
    else {
        try {
            outImage.loadNewImage(narrowTemp);
            if (outImage.imageData == nullptr || outImage.width <= 0 || outImage.height <= 0) {
                error = L"The file could not be decoded as an image:\n" + path;
            }
            else {
                ok = true;
            }
        }
        catch (const std::exception&) {
            error = L"The file could not be loaded as an image (it may be damaged or not a real image):\n" + path;
        }
    }
    DeleteFileW(tempPath.c_str());
    return ok;
}

bool SaveImageFile(Image& img, const wstring& destination, wstring& error) {
    wstring ext = GetLowerExtension(destination);
    if (!IsSupportedExtension(ext)) {
        error = L"Cannot save as \"" + ext + L"\".\nUse a .png, .jpg, .jpeg, .bmp or .tga file name.";
        return false;
    }

    wstring tempPath;
    if (!MakeTempFilePath(ext, tempPath, error)) return false;
    DeleteFileW(tempPath.c_str());

    string narrowTemp;
    if (!ToNarrowPath(tempPath, narrowTemp)) {
        error = L"The Windows temporary folder path contains characters this program cannot use.";
        return false;
    }

    try {
        img.saveImage(narrowTemp);
    }
    catch (const std::exception&) {
        error = L"The image could not be encoded.";
        DeleteFileW(tempPath.c_str());
        return false;
    }

    // Image::saveImage() always returns true, even when the file could not be
    // written, so we check that a non-empty file really exists.
    WIN32_FILE_ATTRIBUTE_DATA info;
    if (!GetFileAttributesExW(tempPath.c_str(), GetFileExInfoStandard, &info) ||
        (info.nFileSizeLow == 0 && info.nFileSizeHigh == 0)) {
        error = L"The image could not be written (encoding failed).";
        DeleteFileW(tempPath.c_str());
        return false;
    }

    if (!CopyFileW(tempPath.c_str(), destination.c_str(), FALSE)) {
        error = L"Could not save to:\n" + destination + L"\n\n" + LastErrorText(GetLastError());
        DeleteFileW(tempPath.c_str());
        return false;
    }
    DeleteFileW(tempPath.c_str());
    return true;
}

bool ShowOpenDialog(HWND owner, const wchar_t* title, wstring& outPath) {
    vector<wchar_t> buffer(32768, L'\0');
    OPENFILENAMEW ofn = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = owner;
    ofn.lpstrFilter =
        L"Image files (*.jpg;*.jpeg;*.png;*.bmp;*.tga)\0*.jpg;*.jpeg;*.png;*.bmp;*.tga\0"
        L"All files (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFile = buffer.data();
    ofn.nMaxFile = (DWORD)buffer.size();
    ofn.lpstrTitle = title;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
    if (!GetOpenFileNameW(&ofn)) return false;
    outPath = buffer.data();
    return true;
}

bool ShowSaveDialog(HWND owner, const wstring& suggestedName, wstring& outPath) {
    vector<wchar_t> buffer(32768, L'\0');
    wcsncpy(buffer.data(), suggestedName.c_str(), buffer.size() - 1);

    wstring ext = GetLowerExtension(suggestedName);
    DWORD filterIndex = 1;                                   // PNG
    if (ext == L".jpg" || ext == L".jpeg") filterIndex = 2;
    else if (ext == L".bmp") filterIndex = 3;
    else if (ext == L".tga") filterIndex = 4;

    OPENFILENAMEW ofn = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = owner;
    ofn.lpstrFilter =
        L"PNG image (*.png)\0*.png\0"
        L"JPEG image (*.jpg;*.jpeg)\0*.jpg;*.jpeg\0"
        L"BMP image (*.bmp)\0*.bmp\0"
        L"TGA image (*.tga)\0*.tga\0";
    ofn.nFilterIndex = filterIndex;
    ofn.lpstrFile = buffer.data();
    ofn.nMaxFile = (DWORD)buffer.size();
    ofn.lpstrTitle = L"Save image as";
    ofn.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
    if (!GetSaveFileNameW(&ofn)) return false;

    outPath = buffer.data();
    if (GetLowerExtension(outPath).empty()) {
        // user typed a name without extension: add the one of the chosen filter
        static const wchar_t* extByFilter[] = { L".png", L".jpg", L".bmp", L".tga" };
        DWORD index = (ofn.nFilterIndex >= 1 && ofn.nFilterIndex <= 4) ? ofn.nFilterIndex - 1 : 0;
        outPath += extByFilter[index];
    }
    return true;
}

// ---------------------------------------------------------------------
// PART 5 - Preview rendering
// ---------------------------------------------------------------------
// Image_Class.h stores pixels as R,G,B,R,G,B,... from the top row down.
// GDI wants B,G,R per pixel, and every row padded to a multiple of 4 bytes
// (the "stride"). We build such a buffer in g.previewPixels whenever the
// working image changes. WM_PAINT only draws that buffer - it never touches
// the working image, so repainting can never change or re-filter anything.

void RebuildPreviewBuffer() {
    g.previewPixels.clear();
    g.previewStride = 0;
    if (!g.hasImage || g.working.imageData == nullptr) return;

    int w = g.working.width;
    int h = g.working.height;
    int stride = ((w * 24 + 31) / 32) * 4;
    g.previewStride = stride;
    g.previewPixels.assign((size_t)stride * h, 0);

    const unsigned char* src = g.working.imageData;
    for (int y = 0; y < h; y++) {
        unsigned char* dst = &g.previewPixels[(size_t)y * stride];
        for (int x = 0; x < w; x++) {
            const unsigned char* rgb = src + ((size_t)y * w + x) * 3;
            dst[x * 3 + 0] = rgb[2];   // B
            dst[x * 3 + 1] = rgb[1];   // G
            dst[x * 3 + 2] = rgb[0];   // R
        }
    }
}

void UpdateWindowTitleAndButtons() {
    wstring title = L"CS213 Photo Editor";
    if (g.hasImage) {
        title += L" - " + FileNameOnly(g.currentPath);
        if (g.modified) title += L" *";
    }
    SetWindowTextW(g.hMain, title.c_str());

    EnableWindow(g.hSave, g.hasImage);
    EnableWindow(g.hSaveAs, g.hasImage);
    EnableWindow(g.hReset, g.hasImage);

    RECT status;
    GetStatusRect(status);
    InvalidateRect(g.hMain, &status, FALSE);
}

void RefreshPreview() {
    RebuildPreviewBuffer();
    InvalidateRect(g.hPreview, nullptr, FALSE);
    UpdateWindowTitleAndButtons();
}

void DrawPreview(HWND hwnd, HDC hdc) {
    RECT rc;
    GetClientRect(hwnd, &rc);
    int w = rc.right, h = rc.bottom;
    if (w <= 0 || h <= 0) return;

    // draw into an off-screen bitmap first -> no flicker
    HDC mem = CreateCompatibleDC(hdc);
    HBITMAP bitmap = CreateCompatibleBitmap(hdc, w, h);
    HGDIOBJ oldBitmap = SelectObject(mem, bitmap);
    FillRect(mem, &rc, g.brushPreview);

    bool canDraw = g.hasImage && g.working.width > 0 && g.working.height > 0 &&
        g.previewPixels.size() >= (size_t)g.previewStride * g.working.height;
    if (!canDraw) {
        SetBkMode(mem, TRANSPARENT);
        SetTextColor(mem, COLOR_MUTED);
        HGDIOBJ oldFont = SelectObject(mem, g.fontBold);
        DrawTextW(mem, L"Open an image to get started", -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        SelectObject(mem, oldFont);
    }
    else {
        const int padding = 14;
        int availW = max(1, w - 2 * padding);
        int availH = max(1, h - 2 * padding);
        double scale = min((double)availW / g.working.width, (double)availH / g.working.height);
        int drawW = max(1, (int)(g.working.width * scale));
        int drawH = max(1, (int)(g.working.height * scale));
        int drawX = (w - drawW) / 2;
        int drawY = (h - drawH) / 2;

        BITMAPINFO bmi = {};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = g.working.width;
        bmi.bmiHeader.biHeight = -g.working.height;     // negative = top-down rows
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 24;
        bmi.bmiHeader.biCompression = BI_RGB;

        SetStretchBltMode(mem, HALFTONE);
        SetBrushOrgEx(mem, 0, 0, nullptr);
        StretchDIBits(mem, drawX, drawY, drawW, drawH,
            0, 0, g.working.width, g.working.height,
            g.previewPixels.data(), &bmi, DIB_RGB_COLORS, SRCCOPY);

        // thin purple outline
        HPEN pen = CreatePen(PS_SOLID, 1, COLOR_ACCENT);
        HGDIOBJ oldPen = SelectObject(mem, pen);
        HGDIOBJ oldBrush = SelectObject(mem, GetStockObject(NULL_BRUSH));
        Rectangle(mem, drawX - 1, drawY - 1, drawX + drawW + 1, drawY + drawH + 1);
        SelectObject(mem, oldBrush);
        SelectObject(mem, oldPen);
        DeleteObject(pen);
    }

    BitBlt(hdc, 0, 0, w, h, mem, 0, 0, SRCCOPY);
    SelectObject(mem, oldBitmap);
    DeleteObject(bitmap);
    DeleteDC(mem);
}

// ---------------------------------------------------------------------
// PART 6 - Settings panel and applying filters
// ---------------------------------------------------------------------

struct SettingsSpec {
    int optionCount = 0;
    const wchar_t* optionLabels[3] = { L"", L"", L"" };
    int editCount = 0;
    const wchar_t* editLabels[4] = { L"", L"", L"", L"" };
    bool needsSecond = false;
};

SettingsSpec GetSpec(int filter) {
    SettingsSpec s;
    switch (filter) {
    case FILTER_FRAME:
        s.optionCount = 2;
        s.optionLabels[0] = L"Simple frame";
        s.optionLabels[1] = L"Ornamental frame (white corners)";
        break;
    case FILTER_ROTATE:
        s.optionCount = 3;
        s.optionLabels[0] = L"90\u00B0 counter-clockwise";
        s.optionLabels[1] = L"180\u00B0";
        s.optionLabels[2] = L"270\u00B0 counter-clockwise";
        break;
    case FILTER_DARKLIGHT:
        s.optionCount = 2;
        s.optionLabels[0] = L"Darken";
        s.optionLabels[1] = L"Lighten";
        s.editCount = 1;
        s.editLabels[0] = L"Level (0 - 100)";
        break;
    case FILTER_RESIZE:
        s.editCount = 2;
        s.editLabels[0] = L"New width (1 - 8000 px)";
        s.editLabels[1] = L"New height (1 - 8000 px)";
        break;
    case FILTER_MERGE:
        s.needsSecond = true;
        s.optionCount = 2;
        s.optionLabels[0] = L"Resize 2nd image to match";
        s.optionLabels[1] = L"Merge overlapping area only";
        break;
    case FILTER_CROP:
        s.editCount = 4;
        s.editLabels[0] = L"Start X";
        s.editLabels[1] = L"Start Y";
        s.editLabels[2] = L"New width";
        s.editLabels[3] = L"New height";
        break;
    case FILTER_BLUR:
        s.editCount = 1;
        s.editLabels[0] = L"Blur level (1 - 20)";
        break;
    case FILTER_WARP:
        s.editCount = 1;
        s.editLabels[0] = L"Skew % (-100 to 100)";
        break;
    case FILTER_OIL:
        s.editCount = 2;
        s.editLabels[0] = L"Radius (1 - 10)";
        s.editLabels[1] = L"Intensity levels (2 - 64)";
        break;
    default:
        break;
    }
    return s;
}

void InvalidateFilterButtons() {
    for (int i = 0; i < FILTER_COUNT; i++) InvalidateRect(g.filterButtons[i], nullptr, FALSE);
}

void InvalidateOptionButtons() {
    for (int i = 0; i < 3; i++) InvalidateRect(g.hOption[i], nullptr, FALSE);
}

void SetEditText(int index, const wstring& text) {
    SetWindowTextW(g.hEdit[index], text.c_str());
}

void LayoutSettingsControls() {
    RECT rc;
    GetClientRect(g.hSettings, &rc);
    const int pad = 14;
    int width = max(50, (int)rc.right - 2 * pad);
    int y = 12;

    MoveWindow(g.hTitleLabel, pad, y, width, 26, TRUE);
    y += 32;
    MoveWindow(g.hHelpLabel, pad, y, width, 70, TRUE);
    y += 78;

    // hide every optional control first, then show the ones we need
    ShowWindow(g.hPickSecond, SW_HIDE);
    ShowWindow(g.hSecondLabel, SW_HIDE);
    for (int i = 0; i < 3; i++) ShowWindow(g.hOption[i], SW_HIDE);
    for (int i = 0; i < 4; i++) { ShowWindow(g.hEdit[i], SW_HIDE); ShowWindow(g.hEditLabel[i], SW_HIDE); }

    if (g.selectedFilter < 0) {
        ShowWindow(g.hApply, SW_HIDE);
        ShowWindow(g.hCancel, SW_HIDE);
        return;
    }

    SettingsSpec spec = GetSpec(g.selectedFilter);

    if (spec.needsSecond) {
        MoveWindow(g.hPickSecond, pad, y, width, 32, TRUE);
        ShowWindow(g.hPickSecond, SW_SHOW);
        y += 38;
        MoveWindow(g.hSecondLabel, pad, y, width, 36, TRUE);
        ShowWindow(g.hSecondLabel, SW_SHOW);
        y += 44;
    }
    for (int i = 0; i < spec.optionCount; i++) {
        SetWindowTextW(g.hOption[i], spec.optionLabels[i]);
        MoveWindow(g.hOption[i], pad, y, width, 32, TRUE);
        ShowWindow(g.hOption[i], SW_SHOW);
        y += 38;
    }
    if (spec.optionCount > 0) y += 6;
    for (int i = 0; i < spec.editCount; i++) {
        SetWindowTextW(g.hEditLabel[i], spec.editLabels[i]);
        MoveWindow(g.hEditLabel[i], pad, y, width, 20, TRUE);
        MoveWindow(g.hEdit[i], pad, y + 22, width, 28, TRUE);
        ShowWindow(g.hEditLabel[i], SW_SHOW);
        ShowWindow(g.hEdit[i], SW_SHOW);
        y += 60;
    }

    int buttonY = rc.bottom - 14 - 38;
    int buttonW = (width - 8) / 2;
    MoveWindow(g.hApply, pad, buttonY, buttonW, 38, TRUE);
    MoveWindow(g.hCancel, pad + buttonW + 8, buttonY, buttonW, 38, TRUE);
    ShowWindow(g.hApply, SW_SHOW);
    ShowWindow(g.hCancel, SW_SHOW);
    InvalidateRect(g.hSettings, nullptr, TRUE);
}

void CloseSettings() {
    g.selectedFilter = -1;
    g.selectedOption = 0;
    SetWindowTextW(g.hTitleLabel, L"Settings");
    SetWindowTextW(g.hHelpLabel,
        L"Filters with options show their settings here.\r\nFilters without options are applied immediately when you click them.");
    LayoutSettingsControls();
    InvalidateFilterButtons();
}

void OpenSettingsFor(int filter) {
    g.selectedFilter = filter;
    g.selectedOption = 0;
    g.hasSecond = false;
    g.secondName.clear();
    SetWindowTextW(g.hSecondLabel, L"No second image chosen yet.");

    SetWindowTextW(g.hTitleLabel, FILTERS[filter].name);
    SetWindowTextW(g.hHelpLabel, FILTERS[filter].help);

    // sensible default values (some depend on the current image size)
    int w = g.working.width, h = g.working.height;
    switch (filter) {
    case FILTER_DARKLIGHT: SetEditText(0, L"20"); break;
    case FILTER_RESIZE:    SetEditText(0, std::to_wstring(w)); SetEditText(1, std::to_wstring(h)); break;
    case FILTER_CROP:
        SetEditText(0, L"0"); SetEditText(1, L"0");
        SetEditText(2, std::to_wstring(w)); SetEditText(3, std::to_wstring(h));
        break;
    case FILTER_BLUR:      SetEditText(0, L"3"); break;
    case FILTER_WARP:      SetEditText(0, L"30"); break;
    case FILTER_OIL:       SetEditText(0, L"3"); SetEditText(1, L"20"); break;
    default: break;
    }

    LayoutSettingsControls();
    InvalidateFilterButtons();
    InvalidateOptionButtons();
}

// Reads a whole number from edit box "index"; checks it is within [minV, maxV].
bool ReadIntField(int index, const wchar_t* fieldName, int minV, int maxV, int& value, wstring& error) {
    wchar_t text[64] = L"";
    GetWindowTextW(g.hEdit[index], text, 64);

    wstring rangeText = L"between " + std::to_wstring(minV) + L" and " + std::to_wstring(maxV);
    wchar_t* end = nullptr;
    errno = 0;
    long parsed = wcstol(text, &end, 10);
    if (end == text) {
        error = wstring(fieldName) + L" must be a whole number " + rangeText + L".";
        return false;
    }
    while (*end != L'\0' && iswspace(*end)) end++;
    if (*end != L'\0' || errno == ERANGE) {
        error = wstring(fieldName) + L" must be a whole number " + rangeText + L".";
        return false;
    }
    if (parsed < minV || parsed > maxV) {
        error = wstring(fieldName) + L" must be " + rangeText + L".";
        return false;
    }
    value = (int)parsed;
    return true;
}

// Runs one filter on a COPY of the working image. Only if everything works is
// the working image replaced - so an error can never leave a half-filtered image.
bool RunFilter(int filter, const FilterParams& p) {
    if (!g.hasImage) {
        ShowError(L"Please open an image first.");
        return false;
    }

    HCURSOR oldCursor = SetCursor(LoadCursor(nullptr, IDC_WAIT));
    SetStatus(wstring(L"Applying ") + FILTERS[filter].name + L" ...", false);
    UpdateWindow(g.hMain);

    wstring error;
    bool success = false;
    try {
        Image candidate = g.working;

        switch (filter) {
        case FILTER_GRAYSCALE: GrayscaleFilter(candidate); break;
        case FILTER_BW:        BW(candidate); break;
        case FILTER_INVERT:    Invert(candidate); break;
        case FILTER_FRAME:     Frame(candidate, p.option == 0 ? 1 : 2); break;
        case FILTER_FLIP:      Flip(candidate); break;
        case FILTER_ROTATE:    getAngle(candidate, (p.option + 1) * 90); break;
        case FILTER_DARKLIGHT: DarkenandLighten(candidate, p.option == 0, p.a); break;
        case FILTER_RESIZE:    Resize(candidate, p.a, p.b); break;
        case FILTER_MERGE: {
            Image second = g.secondImage;      // copy: Merge functions may resize it
            if (p.option == 0) Merge_With_Resize(candidate, second);
            else               Merge(candidate, second);
            break;
        }
        case FILTER_EDGE: {
            // as in the original: edge detection works on a grayscale copy
            Image gray = candidate;
            GrayscaleFilter(gray);
            candidate = EdgeDetection(gray);
            break;
        }
        case FILTER_CROP:
            if (!Crop(candidate, p.a, p.b, p.c, p.d)) throw std::runtime_error("Invalid crop rectangle.");
            break;
        case FILTER_BLUR:      Blur(candidate, p.a); break;
        case FILTER_SUNLIGHT:  SunlightCorrection(candidate); break;
        case FILTER_OLDTV:     applyOldTV(candidate); break;
        case FILTER_PURPLE:    Purple(candidate); break;
        case FILTER_INFRARED:  infraredFilter(candidate); break;
        case FILTER_WARP:      candidate = warpImage(candidate, p.a / 100.0); break;
        case FILTER_OIL:       oilPaint(candidate, p.a, p.b); break;
        default: throw std::runtime_error("Unknown filter.");
        }

        if (candidate.imageData == nullptr || candidate.width <= 0 || candidate.height <= 0) {
            throw std::runtime_error("The filter produced an empty image.");
        }
        g.working = candidate;
        g.modified = true;
        success = true;
    }
    catch (const std::bad_alloc&) {
        error = L"Not enough memory to apply this filter to an image of this size.";
    }
    catch (const std::exception& e) {
        error = L"The filter could not be applied: " + WidenAnsi(e.what());
    }

    SetCursor(oldCursor);

    if (!success) {
        ShowError(error);
        return false;
    }

    RefreshPreview();
    ShowSuccess(wstring(FILTERS[filter].name) + L" applied. New size: " +
        std::to_wstring(g.working.width) + L" x " + std::to_wstring(g.working.height) + L" px.");
    return true;
}

// Called by the Apply button: validate every field, then run the filter.
void ApplySettings() {
    int filter = g.selectedFilter;
    if (filter < 0) return;
    if (!g.hasImage) { ShowError(L"Please open an image first."); return; }

    FilterParams p;
    p.option = g.selectedOption;
    wstring error;
    int imgW = g.working.width, imgH = g.working.height;

    switch (filter) {
    case FILTER_DARKLIGHT:
        if (!ReadIntField(0, L"Level", 0, 100, p.a, error)) { ShowError(error); return; }
        break;

    case FILTER_RESIZE:
        if (!ReadIntField(0, L"Width", 1, MAX_RESIZE_SIDE, p.a, error)) { ShowError(error); return; }
        if (!ReadIntField(1, L"Height", 1, MAX_RESIZE_SIDE, p.b, error)) { ShowError(error); return; }
        if ((long long)p.a * p.b > MAX_PIXELS) {
            ShowError(L"That size is too large (more than 60 million pixels). Please choose smaller dimensions.");
            return;
        }
        break;

    case FILTER_MERGE:
        if (!g.hasSecond) { ShowError(L"Please click \"Choose second image...\" first."); return; }
        break;

    case FILTER_CROP:
        if (!ReadIntField(0, L"Start X", 0, imgW - 1, p.a, error)) { ShowError(error); return; }
        if (!ReadIntField(1, L"Start Y", 0, imgH - 1, p.b, error)) { ShowError(error); return; }
        if (!ReadIntField(2, L"New width", 1, imgW - p.a, p.c, error)) { ShowError(error + L"\n(The image is " + std::to_wstring(imgW) + L" px wide and Start X is " + std::to_wstring(p.a) + L".)"); return; }
        if (!ReadIntField(3, L"New height", 1, imgH - p.b, p.d, error)) { ShowError(error + L"\n(The image is " + std::to_wstring(imgH) + L" px high and Start Y is " + std::to_wstring(p.b) + L".)"); return; }
        break;

    case FILTER_BLUR:
        if (!ReadIntField(0, L"Blur level", 1, MAX_BLUR_LEVEL, p.a, error)) { ShowError(error); return; }
        break;

    case FILTER_WARP: {
        if (!ReadIntField(0, L"Skew", -100, 100, p.a, error)) { ShowError(error); return; }
        long long newWidth = (long long)imgW + (long long)std::ceil(std::fabs(p.a / 100.0) * (imgH - 1));
        if (newWidth * imgH > MAX_PIXELS) { ShowError(L"The skewed image would be too large. Use a smaller skew value."); return; }
        break;
    }

    case FILTER_OIL:
        if (!ReadIntField(0, L"Radius", 1, MAX_OIL_RADIUS, p.a, error)) { ShowError(error); return; }
        if (!ReadIntField(1, L"Intensity levels", MIN_OIL_LEVELS, MAX_OIL_LEVELS, p.b, error)) { ShowError(error); return; }
        if (imgW < 2 * p.a + 1 || imgH < 2 * p.a + 1) {
            ShowError(L"The image is too small for this radius. Choose a smaller radius.");
            return;
        }
        break;

    default:
        break;   // Frame and Rotate only need the chosen option
    }

    if (RunFilter(filter, p)) {
        CloseSettings();
    }
}

// Called when a filter button is clicked.
void OnFilterClicked(int filter) {
    if (!g.hasImage) {
        ShowError(L"Please open an image first (click \"Open Image\").");
        return;
    }
    if (FILTERS[filter].needsSettings) {
        OpenSettingsFor(filter);
    }
    else {
        CloseSettings();
        FilterParams noParams;
        RunFilter(filter, noParams);
    }
}

void OnPickSecondImage() {
    wstring path;
    if (!ShowOpenDialog(g.hMain, L"Choose the second image for Merge", path)) return;

    Image loaded;
    wstring error;
    if (!LoadImageFile(path, loaded, error)) {
        ShowError(error);
        return;
    }
    g.secondImage = loaded;
    g.hasSecond = true;
    g.secondName = FileNameOnly(path);
    wstring label = L"Second image: " + g.secondName + L" (" + std::to_wstring(loaded.width) + L" x " + std::to_wstring(loaded.height) + L")";
    SetWindowTextW(g.hSecondLabel, label.c_str());
    ShowSuccess(L"Second image loaded: " + g.secondName);
}

// ---- Open / Save / Save As / Reset ---------------------------------------

bool ConfirmDiscardChanges() {
    if (!g.hasImage || !g.modified) return true;
    int answer = MessageBoxW(g.hMain,
        L"The current image has unsaved changes.\n\nDiscard them?",
        L"Unsaved changes", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2);
    return answer == IDYES;
}

void OnOpenImage() {
    if (!ConfirmDiscardChanges()) return;

    wstring path;
    if (!ShowOpenDialog(g.hMain, L"Open image", path)) return;

    Image loaded;
    wstring error;
    if (!LoadImageFile(path, loaded, error)) {
        ShowError(error);          // the previously opened image stays untouched
        return;
    }

    g.original = loaded;
    g.working = loaded;
    g.hasImage = true;
    g.modified = false;
    g.currentPath = path;
    g.pathIsOriginalFile = true;

    CloseSettings();
    RefreshPreview();
    ShowSuccess(L"Opened " + FileNameOnly(path) + L" (" + std::to_wstring(loaded.width) + L" x " + std::to_wstring(loaded.height) + L" px).");
}

bool SaveWorkingImageTo(const wstring& path) {
    wstring error;
    HCURSOR oldCursor = SetCursor(LoadCursor(nullptr, IDC_WAIT));
    bool ok = SaveImageFile(g.working, path, error);
    SetCursor(oldCursor);
    if (!ok) {
        ShowError(error);
        return false;
    }
    g.currentPath = path;
    g.pathIsOriginalFile = false;
    g.modified = false;
    UpdateWindowTitleAndButtons();

    wstring ext = GetLowerExtension(path);
    wstring message = L"Saved " + FileNameOnly(path) + L".";
    if (ext == L".jpg" || ext == L".jpeg") message += L" (JPEG is lossy, quality 90)";
    ShowSuccess(message);
    return true;
}

void OnSaveAs() {
    if (!g.hasImage) { ShowError(L"There is no image to save."); return; }
    wstring suggested = FileNameOnly(g.currentPath);
    wstring path;
    if (!ShowSaveDialog(g.hMain, suggested, path)) return;
    SaveWorkingImageTo(path);
}

// Save policy: Save writes to the file the image came from. Because that
// would destroy the user's original picture, we ask first (once). The user can
// choose Yes (overwrite), No (go to Save As) or Cancel.
void OnSave() {
    if (!g.hasImage) { ShowError(L"There is no image to save."); return; }

    if (g.pathIsOriginalFile) {
        wstring question = L"\"" + FileNameOnly(g.currentPath) + L"\" is the original file.\n"
            L"Saving will overwrite it with the edited image.\n\n"
            L"Yes  = overwrite the original\n"
            L"No   = choose a new file (Save As)\n"
            L"Cancel = do nothing";
        int answer = MessageBoxW(g.hMain, question.c_str(), L"Overwrite original file?",
            MB_YESNOCANCEL | MB_ICONWARNING | MB_DEFBUTTON2);
        if (answer == IDCANCEL) return;
        if (answer == IDNO) { OnSaveAs(); return; }
    }
    SaveWorkingImageTo(g.currentPath);
}

void OnReset() {
    if (!g.hasImage) return;
    g.working = g.original;        // exact copy of the image as loaded
    g.modified = false;
    CloseSettings();
    RefreshPreview();
    ShowSuccess(L"Image reset to the original (" + std::to_wstring(g.working.width) + L" x " + std::to_wstring(g.working.height) + L" px).");
}

// ---------------------------------------------------------------------
// PART 7 - Layout and theme drawing
// ---------------------------------------------------------------------

void LayoutFilterButtons() {
    static bool busy = false;      // SetScrollInfo can trigger WM_SIZE again
    if (busy || !g.hFilterPanel) return;
    busy = true;

    RECT rc;
    GetClientRect(g.hFilterPanel, &rc);
    const int rowHeight = 40;
    int totalHeight = FILTER_COUNT * rowHeight + 6;
    int visibleHeight = rc.bottom;
    int maxScroll = max(0, totalHeight - visibleHeight);
    g.filterScroll = min(max(g.filterScroll, 0), maxScroll);

    SCROLLINFO si = {};
    si.cbSize = sizeof(si);
    si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
    si.nMin = 0;
    si.nMax = totalHeight - 1;
    si.nPage = (UINT)visibleHeight;
    si.nPos = g.filterScroll;
    SetScrollInfo(g.hFilterPanel, SB_VERT, &si, TRUE);

    GetClientRect(g.hFilterPanel, &rc);      // width may have changed (scrollbar)
    int buttonWidth = max(60, (int)rc.right - 12);
    for (int i = 0; i < FILTER_COUNT; i++) {
        SetWindowPos(g.filterButtons[i], nullptr, 6, 6 + i * rowHeight - g.filterScroll, buttonWidth, 34,
            SWP_NOZORDER | SWP_NOACTIVATE);
    }
    busy = false;
}

void LayoutMainWindow() {
    if (!g.hFilterPanel) return;
    RECT rc;
    GetClientRect(g.hMain, &rc);
    int w = rc.right, h = rc.bottom;

    int top = HEADER_H + TOOLBAR_H;
    int bottom = h - STATUS_H - MARGIN;
    int contentH = max(100, bottom - top);

    // toolbar buttons
    int buttonY = HEADER_H + 9;
    int x = MARGIN;
    HWND toolbar[4] = { g.hOpen, g.hSave, g.hSaveAs, g.hReset };
    for (int i = 0; i < 4; i++) {
        MoveWindow(toolbar[i], x, buttonY, 140, 36, TRUE);
        x += 148;
    }

    int settingsX = w - MARGIN - RIGHT_W;
    int previewX = MARGIN + LEFT_W + MARGIN;
    int previewW = max(100, settingsX - MARGIN - previewX);

    MoveWindow(g.hFilterPanel, MARGIN, top, LEFT_W, contentH, TRUE);
    MoveWindow(g.hPreview, previewX, top, previewW, contentH, TRUE);
    MoveWindow(g.hSettings, settingsX, top, RIGHT_W, contentH, TRUE);

    LayoutFilterButtons();
    LayoutSettingsControls();
}

COLORREF Darker(COLORREF c) {
    return RGB(GetRValue(c) * 80 / 100, GetGValue(c) * 80 / 100, GetBValue(c) * 80 / 100);
}

// Draws every owner-draw button (toolbar, filter list, option choices, Apply...).
void DrawOwnerButton(const DRAWITEMSTRUCT* dis) {
    int id = (int)dis->CtlID;
    HDC dc = dis->hDC;
    RECT rc = dis->rcItem;
    bool pressed = (dis->itemState & ODS_SELECTED) != 0;
    bool disabled = (dis->itemState & ODS_DISABLED) != 0;
    bool onMainWindow = (GetParent(dis->hwndItem) == g.hMain);

    COLORREF fill = COLOR_BUTTON;
    COLORREF textColor = COLOR_TEXT;
    bool leftAlign = false;

    if (id >= CMD_FILTER_FIRST && id < CMD_FILTER_FIRST + FILTER_COUNT) {
        leftAlign = true;
        if (id - CMD_FILTER_FIRST == g.selectedFilter) fill = COLOR_ACCENT;
    }
    else if (id >= CMD_OPTION1 && id <= CMD_OPTION3) {
        if (id - CMD_OPTION1 == g.selectedOption) fill = COLOR_ACCENT;
    }
    else if (id == CMD_OPEN || id == CMD_APPLY) {
        fill = COLOR_ACCENT;
    }

    if (pressed) fill = Darker(fill);
    if (disabled) { fill = COLOR_BUTTON_OFF; textColor = COLOR_MUTED; }

    // background behind the rounded corners
    HBRUSH backBrush = CreateSolidBrush(onMainWindow ? COLOR_BG : COLOR_PANEL);
    FillRect(dc, &rc, backBrush);
    DeleteObject(backBrush);

    HBRUSH brush = CreateSolidBrush(fill);
    HPEN pen = CreatePen(PS_SOLID, 1, fill);
    HGDIOBJ oldBrush = SelectObject(dc, brush);
    HGDIOBJ oldPen = SelectObject(dc, pen);
    RoundRect(dc, rc.left, rc.top, rc.right, rc.bottom, 10, 10);
    SelectObject(dc, oldPen);
    SelectObject(dc, oldBrush);
    DeleteObject(pen);
    DeleteObject(brush);

    wchar_t text[128] = L"";
    GetWindowTextW(dis->hwndItem, text, 128);
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, textColor);
    HGDIOBJ oldFont = SelectObject(dc, g.fontNormal);
    RECT textRect = rc;
    if (leftAlign) {
        textRect.left += 14;
        DrawTextW(dc, text, -1, &textRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
    }
    else {
        DrawTextW(dc, text, -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
    }
    SelectObject(dc, oldFont);
}

// Header bar and status bar are painted directly on the main window.
void PaintMainChrome(HDC dc, const RECT& client) {
    SetBkMode(dc, TRANSPARENT);

    // header
    RECT header = { 0, 0, client.right, HEADER_H };
    FillRect(dc, &header, g.brushPanel);
    RECT accent = { 0, HEADER_H - 3, client.right, HEADER_H };
    HBRUSH accentBrush = CreateSolidBrush(COLOR_ACCENT);
    FillRect(dc, &accent, accentBrush);
    DeleteObject(accentBrush);

    HGDIOBJ oldFont = SelectObject(dc, g.fontTitle);
    SetTextColor(dc, COLOR_TEXT);
    RECT titleRect = { 18, 0, client.right / 2, HEADER_H - 3 };
    DrawTextW(dc, L"CS213 Photo Editor", -1, &titleRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

    SelectObject(dc, g.fontSmall);
    SetTextColor(dc, COLOR_MUTED);
    RECT subtitleRect = { client.right / 2, 0, client.right - 18, HEADER_H - 3 };
    DrawTextW(dc, L"18 filters  |  Win32 GUI", -1, &subtitleRect, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

    // status bar
    RECT status;
    GetStatusRect(status);
    FillRect(dc, &status, g.brushPanel);

    SelectObject(dc, g.fontNormal);
    wstring info;
    if (g.hasImage) {
        info = L"File: " + FileNameOnly(g.currentPath) + L"   |   " +
            std::to_wstring(g.working.width) + L" x " + std::to_wstring(g.working.height) + L" px";
        if (g.modified) info += L"   |   unsaved changes";
    }
    else {
        info = L"No image loaded";
    }
    SetTextColor(dc, COLOR_TEXT);
    RECT infoRect = { 16, status.top, status.right / 2, status.bottom };
    DrawTextW(dc, info.c_str(), -1, &infoRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

    SetTextColor(dc, g.statusIsError ? COLOR_ERROR : COLOR_OK);
    RECT messageRect = { status.right / 2 + 10, status.top, status.right - 16, status.bottom };
    DrawTextW(dc, g.statusMessage.c_str(), -1, &messageRect, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

    SelectObject(dc, oldFont);
}

// ---------------------------------------------------------------------
// PART 8 - Window procedures (event handling)
// ---------------------------------------------------------------------

LRESULT HandleControlColor(UINT msg, HDC dc, HWND control) {
    if (msg == WM_CTLCOLOREDIT) {
        SetTextColor(dc, COLOR_TEXT);
        SetBkColor(dc, COLOR_EDIT_BG);
        return (LRESULT)g.brushEdit;
    }
    // static labels
    bool muted = (control == g.hHelpLabel || control == g.hSecondLabel);
    SetTextColor(dc, muted ? COLOR_MUTED : COLOR_TEXT);
    SetBkColor(dc, COLOR_PANEL);
    return (LRESULT)g.brushPanel;
}

void ScrollFilterPanelBy(int deltaPixels) {
    g.filterScroll += deltaPixels;
    LayoutFilterButtons();
}

// Window procedure shared by the two container panels (filter list, settings).
// Children send their notifications to the panel; the panel passes the ones
// the program cares about on to the main window.
LRESULT CALLBACK PanelProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_ERASEBKGND: {
        RECT rc;
        GetClientRect(hwnd, &rc);
        FillRect((HDC)wParam, &rc, g.brushPanel);
        return 1;
    }
    case WM_COMMAND:
    case WM_DRAWITEM:
        return SendMessageW(g.hMain, msg, wParam, lParam);
    case WM_CTLCOLORSTATIC:
    case WM_CTLCOLOREDIT:
        return HandleControlColor(msg, (HDC)wParam, (HWND)lParam);
    case WM_SIZE:
        if (hwnd == g.hFilterPanel) LayoutFilterButtons();
        return 0;
    case WM_VSCROLL: {
        if (hwnd != g.hFilterPanel) break;
        SCROLLINFO si = {};
        si.cbSize = sizeof(si);
        si.fMask = SIF_ALL;
        GetScrollInfo(hwnd, SB_VERT, &si);
        int pos = si.nPos;
        switch (LOWORD(wParam)) {
        case SB_LINEUP:        pos -= 30; break;
        case SB_LINEDOWN:      pos += 30; break;
        case SB_PAGEUP:        pos -= (int)si.nPage; break;
        case SB_PAGEDOWN:      pos += (int)si.nPage; break;
        case SB_THUMBTRACK:
        case SB_THUMBPOSITION: pos = si.nTrackPos; break;
        default: break;
        }
        g.filterScroll = pos;
        LayoutFilterButtons();
        return 0;
    }
    case WM_MOUSEWHEEL:
        if (hwnd == g.hFilterPanel) {
            int notches = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
            ScrollFilterPanelBy(-notches * 60);
            return 0;
        }
        break;
    default:
        break;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK PreviewProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_ERASEBKGND:
        return 1;                       // we paint everything ourselves
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        DrawPreview(hwnd, hdc);         // only DRAWS; never changes the image
        EndPaint(hwnd, &ps);
        return 0;
    }
    default:
        break;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

HWND MakeButton(HWND parent, const wchar_t* text, int id) {
    HWND button = CreateWindowExW(0, L"BUTTON", text, WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | WS_TABSTOP,
        0, 0, 10, 10, parent, (HMENU)(INT_PTR)id, GetModuleHandleW(nullptr), nullptr);
    SendMessageW(button, WM_SETFONT, (WPARAM)g.fontNormal, TRUE);
    return button;
}

HWND MakeLabel(HWND parent, HFONT font) {
    HWND label = CreateWindowExW(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT,
        0, 0, 10, 10, parent, nullptr, GetModuleHandleW(nullptr), nullptr);
    SendMessageW(label, WM_SETFONT, (WPARAM)font, TRUE);
    return label;
}

void CreateAllControls(HWND hwnd) {
    HINSTANCE inst = GetModuleHandleW(nullptr);

    // toolbar buttons
    g.hOpen = MakeButton(hwnd, L"Open Image", CMD_OPEN);
    g.hSave = MakeButton(hwnd, L"Save", CMD_SAVE);
    g.hSaveAs = MakeButton(hwnd, L"Save As...", CMD_SAVE_AS);
    g.hReset = MakeButton(hwnd, L"Reset", CMD_RESET);

    // the three big areas
    g.hFilterPanel = CreateWindowExW(0, L"CS213Panel", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_CLIPCHILDREN,
        0, 0, 10, 10, hwnd, nullptr, inst, nullptr);
    g.hPreview = CreateWindowExW(0, L"CS213Preview", L"", WS_CHILD | WS_VISIBLE,
        0, 0, 10, 10, hwnd, nullptr, inst, nullptr);
    g.hSettings = CreateWindowExW(0, L"CS213Panel", L"", WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
        0, 0, 10, 10, hwnd, nullptr, inst, nullptr);

    // 18 filter buttons inside the (scrollable) filter panel
    for (int i = 0; i < FILTER_COUNT; i++) {
        wstring text = std::to_wstring(i + 1) + L".  " + FILTERS[i].name;
        g.filterButtons[i] = MakeButton(g.hFilterPanel, text.c_str(), CMD_FILTER_FIRST + i);
    }

    // settings panel controls
    g.hTitleLabel = MakeLabel(g.hSettings, g.fontBold);
    g.hHelpLabel = MakeLabel(g.hSettings, g.fontSmall);
    g.hSecondLabel = MakeLabel(g.hSettings, g.fontSmall);
    g.hPickSecond = MakeButton(g.hSettings, L"Choose second image...", CMD_PICK_SECOND);
    for (int i = 0; i < 3; i++) g.hOption[i] = MakeButton(g.hSettings, L"", CMD_OPTION1 + i);
    for (int i = 0; i < 4; i++) {
        g.hEditLabel[i] = MakeLabel(g.hSettings, g.fontNormal);
        g.hEdit[i] = CreateWindowExW(0, L"EDIT", L"", WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | WS_TABSTOP,
            0, 0, 10, 10, g.hSettings, (HMENU)(INT_PTR)(CMD_EDIT1 + i), inst, nullptr);
        SendMessageW(g.hEdit[i], WM_SETFONT, (WPARAM)g.fontNormal, TRUE);
    }
    g.hApply = MakeButton(g.hSettings, L"Apply", CMD_APPLY);
    g.hCancel = MakeButton(g.hSettings, L"Cancel", CMD_CANCEL);

    CloseSettings();
    UpdateWindowTitleAndButtons();
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        g.hMain = hwnd;
        CreateAllControls(hwnd);
        SetStatus(L"Welcome! Click \"Open Image\" to begin.", false);
        return 0;

    case WM_SIZE:
        if (wParam != SIZE_MINIMIZED) {
            LayoutMainWindow();
            InvalidateRect(hwnd, nullptr, FALSE);
        }
        return 0;

    case WM_GETMINMAXINFO: {
        MINMAXINFO* info = (MINMAXINFO*)lParam;
        info->ptMinTrackSize.x = 1000;
        info->ptMinTrackSize.y = 650;
        return 0;
    }

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC dc = BeginPaint(hwnd, &ps);
        RECT client;
        GetClientRect(hwnd, &client);
        PaintMainChrome(dc, client);
        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_DRAWITEM:
        DrawOwnerButton((const DRAWITEMSTRUCT*)lParam);
        return TRUE;

    case WM_CTLCOLORSTATIC:
    case WM_CTLCOLOREDIT:
        return HandleControlColor(msg, (HDC)wParam, (HWND)lParam);

    case WM_MOUSEWHEEL: {
        POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
        RECT panelRect;
        GetWindowRect(g.hFilterPanel, &panelRect);
        if (PtInRect(&panelRect, pt)) {
            SendMessageW(g.hFilterPanel, WM_MOUSEWHEEL, wParam, lParam);
            return 0;
        }
        break;
    }

    case WM_COMMAND: {
        int id = LOWORD(wParam);
        if (HIWORD(wParam) != BN_CLICKED) break;     // ignore edit-box notifications

        if (id >= CMD_FILTER_FIRST && id < CMD_FILTER_FIRST + FILTER_COUNT) {
            OnFilterClicked(id - CMD_FILTER_FIRST);
        }
        else if (id >= CMD_OPTION1 && id <= CMD_OPTION3) {
            g.selectedOption = id - CMD_OPTION1;
            InvalidateOptionButtons();
        }
        else {
            switch (id) {
            case CMD_OPEN:        OnOpenImage(); break;
            case CMD_SAVE:        OnSave(); break;
            case CMD_SAVE_AS:     OnSaveAs(); break;
            case CMD_RESET:       OnReset(); break;
            case CMD_APPLY:       ApplySettings(); break;
            case CMD_CANCEL:      CloseSettings(); SetStatus(L"Settings cancelled.", false); break;
            case CMD_PICK_SECOND: OnPickSecondImage(); break;
            default: break;
            }
        }
        return 0;
    }

    case WM_CLOSE:
        if (!ConfirmDiscardChanges()) return 0;
        DestroyWindow(hwnd);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        break;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

// ---------------------------------------------------------------------
// PART 9 - WinMain
// ---------------------------------------------------------------------

HFONT MakeFont(int height, int weight) {
    return CreateFontW(height, 0, 0, 0, weight, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int showCommand) {
    // GDI objects used everywhere (deleted at the end of this function)
    g.fontNormal = MakeFont(-15, FW_NORMAL);
    g.fontBold = MakeFont(-18, FW_BOLD);
    g.fontTitle = MakeFont(-28, FW_BOLD);
    g.fontSmall = MakeFont(-14, FW_NORMAL);
    g.brushBg = CreateSolidBrush(COLOR_BG);
    g.brushPanel = CreateSolidBrush(COLOR_PANEL);
    g.brushEdit = CreateSolidBrush(COLOR_EDIT_BG);
    g.brushPreview = CreateSolidBrush(COLOR_PREVIEW_BG);

    WNDCLASSEXW mainClass = {};
    mainClass.cbSize = sizeof(mainClass);
    mainClass.lpfnWndProc = MainWndProc;
    mainClass.hInstance = instance;
    mainClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    mainClass.hbrBackground = g.brushBg;
    mainClass.lpszClassName = L"CS213PhotoEditorWindow";
    mainClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);

    WNDCLASSEXW panelClass = {};
    panelClass.cbSize = sizeof(panelClass);
    panelClass.lpfnWndProc = PanelProc;
    panelClass.hInstance = instance;
    panelClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    panelClass.hbrBackground = nullptr;
    panelClass.lpszClassName = L"CS213Panel";

    WNDCLASSEXW previewClass = {};
    previewClass.cbSize = sizeof(previewClass);
    previewClass.lpfnWndProc = PreviewProc;
    previewClass.hInstance = instance;
    previewClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    previewClass.hbrBackground = nullptr;
    previewClass.lpszClassName = L"CS213Preview";

    if (!RegisterClassExW(&mainClass) || !RegisterClassExW(&panelClass) || !RegisterClassExW(&previewClass)) {
        MessageBoxW(nullptr, L"Could not register the window classes.", L"CS213 Photo Editor", MB_OK | MB_ICONERROR);
        return 1;
    }

    HWND window = CreateWindowExW(0, L"CS213PhotoEditorWindow", L"CS213 Photo Editor",
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CW_USEDEFAULT, CW_USEDEFAULT, 1220, 780, nullptr, nullptr, instance, nullptr);
    if (!window) {
        MessageBoxW(nullptr, L"Could not create the main window.", L"CS213 Photo Editor", MB_OK | MB_ICONERROR);
        return 1;
    }
    ShowWindow(window, showCommand);
    UpdateWindow(window);

    MSG message;
    while (GetMessageW(&message, nullptr, 0, 0) > 0) {
        TranslateMessage(&message);
        DispatchMessageW(&message);
    }

    DeleteObject(g.fontNormal);
    DeleteObject(g.fontBold);
    DeleteObject(g.fontTitle);
    DeleteObject(g.fontSmall);
    DeleteObject(g.brushBg);
    DeleteObject(g.brushPanel);
    DeleteObject(g.brushEdit);
    DeleteObject(g.brushPreview);
    return (int)message.wParam;
}
