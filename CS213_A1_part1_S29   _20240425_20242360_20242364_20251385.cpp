
/* 
//Team Members & Work Distribution:

1- Name:kinzy ahmed raouf
  ID:20240425
  filter:1,5
  Section:s39,40
2- Name: Mai sabry shappan
   ID:20242360
    filter:2,6
    Sectiion:s39,40
3- Name: Nadeen osama marzok
   ID:20242364
   filter:3,7
   Section:s
4- Name: Marwa mohamed abdelsamad
   ID:20251385
   filter:4,8
   Section:s33,34

*/

#include <iostream>
#include <string>
#include <cmath> 
#include <algorithm>
#include "Image_Class.h"

using namespace std;


//Grayscale Filter
Image image("../OIP.png");

for (int y = 0; y < image.height; y++)
{
    for (int x = 0; x < image.width; x++)
    {
        unsigned char r = image(x, y, 0);
        unsigned char g = image(x, y, 1);
        unsigned char b = image(x, y, 2);

        unsigned char gray = (r + g + b) / 3;

        image(x, y, 0) = gray;
        image(x, y, 1) = gray;
        image(x, y, 2) = gray;
    }
}

image.saveImage("grayscale.png");

return 0;
}

//Black & White Filter
void BW(Image& img) {
    for (int j = 0; j < img.height; j++) {
        for (int i = 0; i < img.width; i++) {
            int avg = 0;
            for (int k = 0; k < 3; k++) {
                avg += img(i, j, k);
            }
            avg /= 3;
            unsigned char bw = (avg >= 128) ? 255 : 0;
            for (int k = 0; k < 3; k++) {
                img(i, j, k) = bw;
            }
        }
    }
}


//Invert Image   
    Image my_image("my_image.jpg");
    for (int x = 0; x < my_image.height; x++)
    {
        for (int y = 0; y < my_image.width; y++)
        {
            for (int c = 0; c <= 2; c++)
            {
                unsigned char& new_pixel = my_image(y, x, c);
                new_pixel = 255 - new_pixel;
            }
        }
    }
    my_image.saveImage("inverted_2.jpg");
}


//Add Frame Image
void Photoframe() {
    cout << "1-simple frame  2-ornamental frame " << endl << "enter number" << endl;
    int n;
    cin >> n;
    Image image("luffy.jpg");
    for (int i = 0; i < image.width; i++) {

        for (int j = 0; j < image.height; j++) {

            for (int k = 0; k < image.channels; ++k) {

                if (i <= 10 || j <= 10 || i >= image.width - 10 || j >= image.height - 10)
                {
                    if (n == 1)
                    {
                        image(i, j, 0) = 0;    // Red
                        image(i, j, 1) = 0;    // Green
                        image(i, j, 2) = 255;  // Blue
                    }
                    else if (n == 2)
                    {

                        image(i, j, 0) = 0;    // Red
                        image(i, j, 1) = 0;    // Green
                        image(i, j, 2) = 255;  // Blue

                        if (i < 20 && j < 20)
                        {
                            image(i, j, 0) = 255;
                            image(i, j, 1) = 255;
                            image(i, j, 2) = 255;
                        }

                        if (i >= image.width - 20 && j < 20)
                        {
                            image(i, j, 0) = 255;
                            image(i, j, 1) = 255;
                            image(i, j, 2) = 255;
                        }
                        if (i < 20 && j >= image.height - 20)
                        {
                            image(i, j, 0) = 255;
                            image(i, j, 1) = 255;
                            image(i, j, 2) = 255;
                        }
                        if (i >= image.width - 20 && j >= image.height - 20)
                        {
                            image(i, j, 0) = 255;
                            image(i, j, 1) = 255;
                            image(i, j, 2) = 255;
                        }


                    }
                }

            }
        }
    }




    image.saveImage("hello.png");

}

   //Flip Image
Image vertical("../OIP.png");

for (int y = 0; y < vertical.height / 2; y++)
{
    for (int x = 0; x < vertical.width; x++)
    {
        for (int c = 0; c < 3; c++)
        {
            swap(
                vertical(x, y, c),
                vertical(x, vertical.height - 1 - y, c)
            );
        }
    }
}

vertical.saveImage("flipped_vertical.png");

return 0;
}


//Rotate Image
void Rotate(Image& img) {
    Image rotated_img(img.height, img.width);
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < img.channels; k++) {
                unsigned char value = img.getPixel(i, j, k);
                rotated_img.setPixel(j, rotated_img.height - 1 - i, k, value);
            }
        }
    }
    img = rotated_img;
}

void getAngle(Image& img) {
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


    //Darken & Lighten Image
    Image my_image("my_image.jpg");
    cout << "Dark OR light ";
    int constant = 0;
    string choice = "";
    getFilter7Input(choice, constant);
    if (choice == "Dark") {
        cout << "choose the level of darkening from 0 to 100% ";
        for (int x = 0; x < my_image.height; x++)
        {
            for (int y = 0; y < my_image.width; y++)
            {
                for (int c = 0; c <= 2; c++)
                {
                    unsigned char& pixel_7 = my_image(y, x, c);
                    int value = pixel_7 - constant;
                    if (value >= 0) {
                        pixel_7 = value;
                    }
                    else {
                        pixel_7 = 0;
                    }
                }
            }
        }
        my_image.saveImage("Dark.jpg");
    }
    if (choice == "light") {
        cout << "choose the level of lighting from 0 to 100%";
        cin >> constant;
        for (int x = 0; x < my_image.height; x++)
        {
            for (int y = 0; y < my_image.width; y++)
            {
                for (int c = 0; c <= 2; c++)
                {
                    unsigned char& pixel_7 = my_image(y, x, c);
                    int value_2 = pixel_7 + constant;
                    if (value_2 < 255) {
                        pixel_7 = value_2;
                    }
                    else {
                        pixel_7 = 255;
                    }
                }
            }
        }
        my_image.saveImage("light.jpg");
    }
    return 0;
}}



//Resizing Images
void size() {                               
    Image image("toy1.jpg");
    int w, h;
    cout << "Enter target width and height: ";
    cin >> w >> h;

    Image image2(w, h);
    double avg = (double)image.width / image2.width;
    double avg2 = (double)image.height / image2.height;

    for (int i = 0; i < image2.width; i++) {
        for (int j = 0; j < image2.height; j++) {

            int orgx = min((int)(i * avg), image.width - 1);
            int orgy = min((int)(j * avg2), image.height - 1);

            for (int k = 0; k < image2.channels; ++k) {
                image2.setPixel(i, j, k, image.getPixel(orgx, orgy, k));
            }
        }
    }

    image2.saveImage("toy2.png");
    cout << "Image resized and saved as toy2.png" << endl;
}



int main() {
    string filename;
    Image img;

    while (true) {
        cout << "Enter The Image File Name with extension: ";
        cin >> filename;
        try {
            img.loadNewImage(filename);
            break;
        }
        catch (...) {
            cout << "Error loading image! Make sure the file exists in the directory.\n\n";
        }
    }

    bool editing = true;
    while (editing) {
        cout << "\n=============================================\n";
        cout << "       Welcome to CS213 Photo Editor         \n";
        cout << "=============================================\n\n";

        cout << "  1  - Grayscale Filter         Convert image to shades of gray\n";
        cout << "  2  - Black & White            Convert image to pure black & white\n";
        cout << "  3  - Invert Colors            Invert all pixel colors\n";
        cout << "  4  - Merge Images             Blend two images together\n";
        cout << "  5  - Flip Image               Flip image horizontally or vertically\n";
        cout << "  6  - Rotate Image             Rotate image by a given angle\n";
        cout << "  7  - Brightness Control       Darken or lighten image\n";
        cout << "  8  - Crop Image               Crop a selected region of image\n\n";

        cout << "Choose a filter by typing its number (1-8): ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            Grayscale(img);
        }
        else if (choice == 2) {
            BW(img);
        }
        else if (choice == 3) {
            Invert(img);
        }
        else if (choice == 4) {
            string filename2;
            Image img2;
            while (true) {
                cout << "Enter second image filename: ";
                cin >> filename2;
                try {
                    img2.loadNewImage(filename2);
                    break;
                }
                catch (...) {
                    cout << "Error loading second image! Try again.\n";
                }
            }

            while (true) {
                cout << "\nChoose Merge mode:\n";
                cout << "1 - Resize smaller image to match the bigger one\n";
                cout << "2 - Merge only the common overlapping area\n";
                cout << "Enter your choice (1, 2): ";
                int merge_option;
                cin >> merge_option;

                if (merge_option == 1) {
                    Merge_With_Resize(img, img2);
                    break;
                }
                else if (merge_option == 2) {
                    Merge(img, img2);
                    break;
                }
                else {
                    cout << "Invalid option! Choose 1 or 2.\n";
                }
            }
        }
        else if (choice == 5) {
            Flip(img);
        }
        else if (choice == 6) {
            getAngle(img);
        }
        else if (choice == 7) {
            DarkenandLighten(img);
        }
        else if (choice == 8) {
            Crop(img);
        }
        else {
            cout << "Invalid Option! Please enter a number from 1 to 8.\n";
            continue;
        }

        // --- Save Section ---
        string savedFileName = filename;
        while (true) {
            cout << "\n1. Save in same file\n2. Save in new file\nChoice: ";
            int n;
            cin >> n;
            if (n == 1) {
                img.saveImage(filename);
                savedFileName = filename;
                break;
            }
            else if (n == 2) {
                string newName;
                cout << "Enter new filename with extension (.jpg, .bmp, .png): ";
                cin >> newName;
                img.saveImage(newName);
                savedFileName = newName;
                break;
            }
            else {
                cout << "Invalid option (1, 2)!\n";
            }
        }

        // Auto Preview
        string cmd = "\"" + savedFileName + "\"";
        system(cmd.c_str());

        // --- Rating Section ---
        cout << "\nDid you like the result? (Rate 1 to 5): ";
        int rate;
        cin >> rate;

        if (rate >= 4) cout << "Glad you loved it!\n";
        else if (rate == 3) cout << "Not bad! We'll keep improving.\n";
        else cout << "Thanks for the feedback!\n";

        // --- Continue / Exit Section ---
        while (true) {
            char option;
            cout << "\nContinue editing this image -> C\nLoad new image -> N\nExit program -> E\nChoice: ";
            cin >> option;
            option = toupper(option);
            if (option == 'E') {
                editing = false;
                break;
            }
            else if (option == 'C') {
                break;
            }
            else if (option == 'N') {
                while (true) {
                    cout << "Enter new Image File Name with extension: ";
                    cin >> filename;
                    try {
                        img.loadNewImage(filename);
                        break;
                    }
                    catch (...) {
                        cout << "Error loading image! Try again.\n";
                    }
                }
                break;
            }
            else {
                cout << "Invalid option (C, N, E)!\n";
            }
        }
    }

    cout << "Thank you for using Pixora/CS213 Photo Editor. Goodbye!\n";
    return 0;
}
