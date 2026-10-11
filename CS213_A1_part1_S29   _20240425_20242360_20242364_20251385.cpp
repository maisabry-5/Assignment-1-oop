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
             Section: 

    •	Marwa Mohamed 
            {ID: }
            Section:s





Solves Filters:
        -Filters 1 & 5 & 9  & 13 solved by Kinzy Ahmed
        -Filters 2 & 6 & 10 & 14 solved by Mai Sabry
        -Filters 3 & 7 & 11 & 15 solved by Nadeen Osama
        -Filters 4 & 8 & 12 & 16 solved by Marwa Mohamed    


        ----



Project Links

     Video Link :

     Repo link :

     Document Link :


*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "Image_Class.h"

using namespace std;

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

// Add Frame Image 
void Frame(Image& img, int n) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            if (i <= 10 || j <= 10 || i >= img.width - 10 || j >= img.height - 10) {
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

void getAngle(Image& img) 
{
    int rotateAngle;
    while (true) {
        cout << "Enter Rotation Angle (90, 180, 270): ";
        cin >> rotateAngle;
        if (rotateAngle == 90 || rotateAngle == 180 || rotateAngle == 270) break;
        cout << "Invalid Angle!" << endl;
    }
    int rotations = rotateAngle / 90;
    while (rotations--) {
        Rotate(img);
    }
}

//  Darken & Lighten Image 
void DarkenandLighten(Image& img) {
    cout << "Dark OR light: ";
    string choice;
    cin >> choice;
    int constant = 0;

    if (choice == "Dark" || choice == "dark") {
        cout << "Choose the level of darkening from 0 to 100: ";
        cin >> constant;
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
    else if (choice == "light" || choice == "Light") {
        cout << "Choose the level of lighting from 0 to 100: ";
        cin >> constant;
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
    int threshold = 100;
    for (int i = 1; i < grayscale.width - 1; ++i) {
        for (int j = 1; j < grayscale.height - 1; ++j) 
        {
            int gx = grayscale(i + 1, j - 1, 0) + 2 * grayscale(i + 1, j, 0) + grayscale(i + 1, j + 1, 0) - grayscale(i - 1, j - 1, 0) - 2 * grayscale(i - 1, j, 0) - grayscale(i - 1, j + 1, 0);
            int gy = grayscale(i - 1, j + 1, 0) + 2 * grayscale(i, j + 1, 0) + grayscale(i + 1, j + 1, 0) - grayscale(i - 1, j - 1, 0) - 2 * grayscale(i, j - 1, 0) - grayscale(i + 1, j - 1, 0);
            int magnitude = sqrt(gx * gx + gy * gy);
            unsigned char color = (magnitude > threshold) ? 0 : 255;
            output(i, j, 0) = color;
            output(i, j, 1) = color;
            output(i, j, 2) = color;
        }
    }
    return output;
}

//  Crop Image 
void Crop(Image& my_image) {
    int new_w, new_h, new_x, new_y;
    cout << "Please enter start point (x y), new pic width and height: \n";
    cin >> new_x >> new_y >> new_w >> new_h;

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
    }
    else {
        cout << "Please enter valid numbers \n";
    }
}

//  Blur Image 
void Blur(Image& image2) {
    int level;
    cout << "Enter the level of blurring: ";
    cin >> level;
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
    for (int j = 0; j < img.height; j++) {
        for (int i = 0; i < img.width; i++) {
            unsigned char red = img(i, j, 0);
            unsigned char green = img(i, j, 1);
            unsigned char blue = img(i, j, 2);

            int nred = min(255, max(0, (int)(red * 1.1)));
            int ngreen = min(255, max(0, (int)(green * 0.6)));
            int nblue = min(255, max(0, (int)(blue * 1.4)));

            img(i, j, 0) = (unsigned char)nred;
            img(i, j, 1) = (unsigned char)ngreen;
            img(i, j, 2) = (unsigned char)nblue;
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
Image warpImage(Image& image) {
    return image;
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


int main() {
    bool editing = true;
    while (editing) {
        cout << "=============================================\n";
        cout << "        Welcome to CS213 Photo Editor        \n";
        cout << "=============================================\n\n";

        cout << "  01 - Grayscale Filter\n";
        cout << "  02 - Black and White Filter\n";
        cout << "  03 - Invert Image\n";
        cout << "  04 - Add Frame Image\n";
        cout << "  05 - Flip Image\n";
        cout << "  06 - Rotate Image\n";
        cout << "  07 - Darken and Lighten Image\n";
        cout << "  08 - Resizing Images\n";
        cout << "  09 - Merge Images\n";
        cout << "  10 - Detect Image Edges\n";
        cout << "  11 - Crop Images\n";
        cout << "  12 - Blur Images\n";
        cout << "  13 - Sunlight Correction\n";
        cout << "  14 - Old TV Filter\n";
        cout << "  15 - Purple Filter\n";
        cout << "  16 - Infrared Filter\n";
        cout << "  17 - Image Skewing (BONUS)\n";
        cout << "  18 - Oil Painting (BONUS)\n\n";
        cout << "  0  -> Back / Choose Another Image\n\n";


        cout << "Enter The File Name with its extension (e.g., image.jpg): ";
        string filename;
        cin >> filename;
        Image img(filename);

        cout << "Choose a filter by typing its number (1-18):\n";
        int choice;
        cin >> choice;

        
            
        if (choice == 0)
        {
            continue;


        if (choice == 1)
        {
            GrayscaleFilter(img);
        }
        else if (choice == 2) 
        {
            BW(img);
        }
        else if (choice == 3) 
        {
            Invert(img);
        }
        else if (choice == 4) 
        {
            while (true) 
            {
                cout << "Choose Frame Color/Type:\nSimple -> 1\nOrnamental -> 2\n";
                int color;
                cin >> color;
                if (color == 1 || color == 2)
                {
                    Frame(img, color);
                    break;
                }
                else {
                    cout << "Choose valid option (1, 2)\n";
                }
            }
        }
        else if (choice == 5)
        {
            Flip(img);
        }
        else if (choice == 6)
        {
            getAngle(img);
        }
        else if (choice == 7) 
        {
            DarkenandLighten(img);
        }
        else if (choice == 8)
        {
            int w, h;
            cout << "Enter Width then Height: ";
            cin >> w >> h;
            Resize(img, w, h);
        }
        else if (choice == 9)
        {
            int merge_option;
            cout << "Enter second filename: ";
            string filename2;
            cin >> filename2;
            Image img2(filename2);

            while (true) {
                cout << "Choose Merge mode:\n";
                cout << "1 - Resize smaller image to match the bigger one\n";
                cout << "2 - Merge only the common overlapping area\n";
                cout << "Enter your choice (1, 2): ";
                cin >> merge_option;

                if (merge_option == 1)
                {
                    Merge_With_Resize(img, img2);
                    break;
                }
                else if (merge_option == 2) 
                {
                    Merge(img, img2);
                    break;
                }
                else {
                    cout << "Choose valid option (1, 2)\n";
                }
            }
        }
        else if (choice == 10) 
        {
            cout << "To detect edges, we first need a grayscale image.\n";
            Image gray = img;
            GrayscaleFilter(gray);
            img = EdgeDetection(gray);
        }
        else if (choice == 11) 
        {
            Crop(img);
        }
        else if (choice == 12)
        {
            Blur(img);
        }
        else if (choice == 13)
        {
            SunlightCorrection(img);
        }
        else if (choice == 14) 
        {
            applyOldTV(img);
        }
        else if (choice == 15) 
        {
            Purple(img);
        }
        else if (choice == 16) 
        {
            infraredFilter(img);
        }
        else if (choice == 17) 
        
        {
            img = warpImage(img);
        }
        else if (choice == 18) 
        {
            oilPaint(img);
        }
        else 
        {
            cout << "Invalid choice! Please try again.\n";
            continue;
        }

        string savedFileName = filename;
        while (true) 
        {
            cout << "Save in same file -> 1\nSave in new file -> 2\nEnter choice: ";
            int n;
            cin >> n;
            if (n == 1) 
            {
                img.saveImage(filename);
                savedFileName = filename;
                break;
            }
            else if (n == 2) 
            {

                string newName;
                cout << "Enter the new name with extension (.jpg, .bmp, .png): ";
                cin >> newName;
                img.saveImage(newName);
                savedFileName = newName;
                break;
            }
            else
            {
                cout << "Choose valid option (1, 2)\n";
            }
        }

        system(savedFileName.c_str());

        cout << "\nDid you like the result? (Rate 1 to 10): ";
        int rate;
        cin >> rate;
        if (rate >= 9) cout << "Glad you loved it! \n";
        else if (rate == 7) cout << "Not bad! We'll keep improving \n";
        else cout << "Thanks for the feedback, we will do better next time!\n";

        while (true) 
        {
            char option;
            cout << "\nContinue editing -> C\nExit program -> E\nEnter choice: "<< endl;
            cin >> option;
            option = toupper(option);
            if (option == 'E') 
            {
                editing = false;
                break;
            }
            else if (option == 'C') 
            {
                break;
            }
            else
            {
                cout << "Choose valid option (C, E)\n" <<endl;
            }
        }
    }

    return 0;
}