# 🎨 C++ Image Processing Studio

-----------


### ****Cairo University**** - *Faculty of Computing and Artificial Intelligence (FCAI)*


--------
**Course:** *CS213 - Object-Oriented Programming* 

**Academic Year:** *2026 / 2027*  

**Supervised by:** *Dr. Mohammad El-Ramly* 

---------

---------

## 📌 Program Description

*This project is a **baby photoshop** that allows users to apply different filters to images.  
The program supports **16 filters and 2 bonus filters and GUI** (18 filters in total).*

---------

## 👥 Team Members
*Developed by:*

- **Kinzy Ahmed Raouf** - *ID: 20240425*
- **Mai Sabry Shapaan** - *ID: 20242360*
- **Nadeen Osama Marzouq** - *ID: 20242364*
- **Marwa Mohamed Abdelsamd** - *ID: 20251385*

---------


## 🎨 Available Filters (16 Filters Total)

| # | Filter Name |
|---|-------------|
| **01** | *Grayscale Filter* | 
| **02** | *Black and White Filter* |
| **03** | *Invert Image* | 
| **04** | *Add Frame Image* |
| **05** | *Flip Image* | 
| **06** | *Rotate Image* |
| **07** | *Darken and Lighten Image* |
| **08** | *Resizing Images* | 
| **09** | *Merge Images* | 
| **10** | *Detect Image Edges* | 
| **11** | *Crop Images* | 
| **12** | *Blur Images* | 
| **13** | *Sunlight Correction* | 
| **14** | *Old TV Filter* |
| **15** | *Purple Filter* | 
| **16** | *Infrared Filter* | 


--------

## 🤝 Work Division

- **Kinzy Ahmed Raouf (Filters 1, 5, 9, 13):** *Grayscale , Flip Image , Merge Image ,Sunlight Correction*
                                                
- **Mai Sabry Shapaan (Filters 2, 6, 10, 14):** *Black and White , Rotate Image , Detect Image , Old TV*

- **Nadeen Osama Marzouq (Filters 3, 7, 11, 15):** *Invert Image, Darken and Lighten Image, Crop Images,  Purple Filter*

- **Marwa Mohamed Abdelsamd (Filters 4, 8, 12, 16):** *Add Frame, Resizing Images, Blur Images, Infrared Filter*

     *(**Repo & Menu & README** are common between all members)*

--------

## ⚙️ How to Run
1. Clone the repo:
   ```bash
   git clone [https://github.com/Moon124-bit/Pixora---Inage-Filters.git](https://github.com/Moon124-bit/Pixora---Inage-Filters.git)
   cd Pixora---Inage-Filters
   
2. Compile:
   ```bash
   g++ main.cpp -o OOP-Ass.-no.1 -std=c++11
   ```

3. Run:
   ```bash
./OOP-Ass.-no.1

---------

### MENU:
*. At first we had to apply the Image Libraries Dr. Ramly shared to be able to use the images.*
*. We will use functions for every filter we will make and the menu to minimize the int main.*
*. What does the menu include?*
*. We will use all numbers to make it easy for the user to choose the one he wants to apply on the image.*
*. We will make a function for each filter that will includes the way the filter is runned.*

--------

### FILTERS:

--------
### [1] GREYSCALE FILTER:

*This filter converts an image to grayscale by looping through every pixel. For each pixel, the average intensity of RGB is calculated by summing the values of all its colors and dividing by 3. It applies this single average value back to every color of each pixel. By this, all the image colors change to grey shades.*

---------

### [2] Black & White filter:

 *This function converts a color image to black and white by calculating the average of each pixel's RGB values. If the average is 128 or more, the pixel becomes white. If the average less than 128, it becomes black. Finally, it applies this new value to all the colors of each pixel.*

---------
### [3] INVERT FILTER:

*The Invert Filter transforms an image into its negative by replacing each pixel value with 255 - current value. This flips all colors to their opposites, turning black to white, white to black, and other colors into their complementary shades. It’s commonly used to create a negative effect.*

---------
### [4] ADD FRAME:
*The user enters the desired frame thickness and RGB color. A new larger image is created to accommodate the frame. The entire new image is filled with the selected color, and the original image is placed precisely in the center, enhancing its appearance.*

 -------
### [5] Flip filter:

*This filter flips an image horizontally or vertically based on user input. For horizontal flip, it swaps pixels between left and right sides through half the width. For vertical flip, it swaps pixels between top and bottom halves through half the height. The swapping is done color by color for each pixel position.*

-------
### [6] ROTATE FILTER:

*The Rotate Filter is one of the fundamental operations in image processing. Its purpose is to change the orientation of an image so it can be displayed correctly or to create a visual effect. In our code, the user can choose an angle:**90°, 180°, or 270°**clockwise or counterclockwise, swapping dimensions when required.*

-------
### [7] Darken & lighten filter:

*This filter makes the image brighter or darker with a simple number. If you use a positive number, the image gets lighter by that percentage of the original brightness; if you use a negative number, it gets darker. The filter works on every single color in every pixel.*

-------
### [8] Crop filter:

*This function asks the user for the place they want to start cropping and the new dimensions for cropping. It checks if these dimensions are valid (not outside the original image). If valid, it creates a new image with the cropped size and copies the pixel data into it.*

-------
### [9] MERGE FILTER:

*This filter merges a second image into the first one by using intersection rules, resizing, or overlapping the common area, calculating the average values of the pixels and colors to blend them together seamlessly.*

--------
### [10] Edge detection filter:

*This filter detects edges in an image and removes internal details. It first turns the image into black and white for higher efficiency. It calculates how quickly brightness changes side to side and up and down, coloring the edge pixels black if the magnitude is high and white otherwise.*

-------
### [11] Resize filter:

*This filter resizes the image dimensions by calculating the ratios between the original and newly requested dimensions using the nearest-neighbor method, changing each pixel in the new image to the closest pixel in the original image.*

------
### [12] BLUR FILTER:

*The blur function makes the image look smoother by averaging each pixel with its surrounding pixels using a 3x3 area, adding color values together and dividing the sum by 9 to replace the original pixel value and create a soft blur effect.*

### [13] Sunlight filter:

*This filter applies a warm sunlight effect by changing the RGB color shades of every pixel, brightening the image and shifting the color towards yellow and orange shades by raising Red and Green and reducing Blue within the [0, 255] range.*

-------
### [14] Old TV filter:

*This filter makes an old TV effect by creating horizontal lines with alternating dark and light shades, applying a purple-blue color shade to simulate vintage television displays.*

------
### [15] Nightfall Purple Glow:

*This filter tints image color channels with a rich, atmospheric violet and deep night-purple glow to give images a distinctive stylized nighttime ambiance.*

-------
### [16] Infrared Camera Effect:

*This filter recreates thermal infrared camera visuals, inverting and shifting color spectrums to mimic high-tech thermal imaging photography.*

--------



