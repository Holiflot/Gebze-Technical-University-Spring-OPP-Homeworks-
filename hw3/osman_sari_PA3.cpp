#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Define a struct to represent a single pixel
struct Pixel {
    int red;
    int green;
    int blue;
};

// Define a class to represent a PPM image
class ppmImage {
    private:
        string fileName;
        int height;
        int width;
        int maxValue;
        string fileType;
        vector<Pixel> pixels;
    public:
        // Constructors
        ppmImage(); // Default constructor
        ppmImage(const string& f); // Constructor that takes a filename
        ppmImage(int w, int h); // Constructor that takes width and height

        // Accessors and mutators
        string getFileName() const { return fileName; };
        int getHeight() const { return height; };
        int getWidth() const { return width; };
        int getMaxValue() const { return maxValue; };
        const vector<Pixel>& getPixels() const { return pixels; };
        string getFileType() const { return fileType; };
        void setFileName(string fN);
        void setHeigth(int h);
        void setWidth(int w);
        void setMaxValue(int mV);
        void setPixels(const vector<Pixel>& imageData);

        // Member functions
        int savePpmImage(const string& f) const;
        int readPpmImage(const string& f);
        void printDimension();
        Pixel getPixel(int index) const;
        void setPixel(int index, const Pixel& p);

        // Operator overloads
        ppmImage operator+(const ppmImage& image);
        ppmImage operator-(const ppmImage& image);
        friend ostream& operator <<(ostream& out, const ppmImage& image);
        int& operator()(int x, int y, int colorChanel);
        const int& operator()(int x, int y, int colorChanel) const;
        void swap(int &n1, int &n2);
};

// Default constructor
ppmImage::ppmImage() : width(0), height(0), maxValue(0) {}

// Constructor that takes a filename
ppmImage::ppmImage(const string& f): fileName(f), width(0), height(0), maxValue(0) {
    ifstream input_file(fileName);
    if (!input_file.is_open()) {
        cout << "File is not open!" << endl;
        exit(1);
    }
    input_file >> fileType >> width >> height >> maxValue;
    if (fileType != "P3") {
        cout << "File format not supported!" << endl;
        exit(1);
    }
    pixels.resize(height * width);
    input_file.close();            
}

// Constructor that takes width and height
ppmImage::ppmImage(int w, int h) : width(w), height(h), maxValue(255) {
    fileType = "P3";
    Pixel white = {255, 255, 255};
    pixels.resize(height * width);
    for (int i = 0; i < height * width; i++) {
        pixels[i] = white;
    }
}

void ppmImage::setFileName(string fN) {
    fileName = fN;
}

void ppmImage::setHeigth(int h) {
    height = h;
}

void ppmImage::setWidth(int w) {
    width = w;
}

void ppmImage::setMaxValue(int mV) {
    maxValue = mV;
}
void ppmImage::setPixels(const vector<Pixel>& imageData){
    for(int i=0;i<imageData.size();i++)
        pixels[i]=imageData[i]; // set each pixel in the image to the corresponding pixel in the input data
}

int ppmImage::savePpmImage(const string& f) const {
    ofstream outfile(f);
    if (!outfile) {
        cerr << "Error: Unable to open file " << f << endl; // print error message if unable to open output file
        return 0;
    }
    outfile << fileType << endl; // write image file type to output file
    outfile << width << " "  << height  << endl; // write image dimensions to output file
    outfile << maxValue << endl; // write maximum pixel value to output file
    for (int i = 0; i < width * height; i++) {
        outfile << pixels[i].red << " " << pixels[i].green << " " << pixels[i].blue; // write the RGB values of each pixel to output file
        if ((i + 1) % 4 == 0)
            outfile << endl; // start new line every 4 pixels
        else
            outfile <<" "; // add a space between each pixel
    }
    outfile.close(); // close the output file
    return 1;
}

int ppmImage::readPpmImage(const string& f){
    setFileName(f);
    ifstream input_file(fileName);
            if (!input_file.is_open()) {
                cout << "File is not open!" << endl; // print error message if unable to open input file
                return 0;
                exit(1); // exit the program
            }
            input_file >> fileType >> width >> height >> maxValue; // read the image type, dimensions, and maximum pixel value from the input file
            if (fileType != "P3") {
                cout << "File format not supported!" << endl; // print error message if the image format is not supported
                exit(1); // exit the program
            }
            pixels.resize(height * width); // resize the pixels vector to match the image dimensions
            int r,g,b;
            for (int i = 0; i < height * width; i++) {
                input_file >> r >> g >> b; // read the RGB values of each pixel from the input file
                pixels[i].red=r; // set the red value of the current pixel
                pixels[i].green=g; // set the green value of the current pixel
                pixels[i].blue=b; // set the blue value of the current pixel
            }
            input_file.close(); // close the input file
            
    return 1;
}

void ppmImage::printDimension(){
    cout << "dimension of ppm image" << pixels.size() << endl; // print the total number of pixels in the image
}

Pixel ppmImage::getPixel(int index)const{
    return pixels[index]; // return the pixel at the specified index
}

void ppmImage::setPixel(int index,const Pixel& p){
    pixels[index]=p; // set the pixel at the specified index to the given Pixel object
}
// This function overloads the addition operator to add two ppmImage objects.
// It takes a reference to another ppmImage object as an input, and returns
// a new ppmImage object that is the sum of the two images.
ppmImage ppmImage::operator+(const ppmImage& image){

    // Check if the two images have the same size.
    if(pixels.size() != image.pixels.size()){
        cerr << "Error: Images have different sizes." << endl;
        exit(1);
    }

    // Create a copy of the left-hand side image.
    ppmImage result(*this);

    // Iterate over all pixels in the images and add their corresponding RGB values.
    for(int i = 0; i < pixels.size(); i++){
        result.pixels[i].red += image.pixels[i].red;
        if(result.pixels[i].red > result.maxValue)
            result.pixels[i].red = result.maxValue;
        result.pixels[i].green += image.pixels[i].green;
        if(result.pixels[i].green > result.maxValue)
            result.pixels[i].green = result.maxValue;
        result.pixels[i].blue += image.pixels[i].blue;
        if(result.pixels[i].blue > result.maxValue)
            result.pixels[i].blue = result.maxValue;
    }

    // Return the resulting ppmImage object.
    return result;
}

// This function overloads the subtraction operator to subtract two ppmImage objects.
// It takes a reference to another ppmImage object as an input, and returns
// a new ppmImage object that is the difference between the two images.
ppmImage ppmImage::operator-(const ppmImage& image){

    // Check if the two images have the same size.
    if(getPixels().size() != image.getPixels().size()){
        exit(1);
    }

    // Create a copy of the left-hand side image.
    ppmImage result(*this);

    // Iterate over all pixels in the images and subtract their corresponding RGB values.
    for(int i = 0; i < pixels.size(); i++){
        result.pixels[i].red -= image.pixels[i].red;
        if(result.pixels[i].red < 0)
            result.pixels[i].red = 0;
        result.pixels[i].green -= image.pixels[i].green;
        if(result.pixels[i].green < 0)
            result.pixels[i].green = 0;
        result.pixels[i].blue -= image.pixels[i].blue;
        if(result.pixels[i].blue < 0)
            result.pixels[i].blue = 0;
    }

    // Return the resulting ppmImage object.
    return result;
}
// Overloaded insertion operator that outputs an image to a stream
ostream& operator <<(ostream& out, const ppmImage& image){
    out << image.fileType << endl;         // Output the file type
    out << image.width << " " << image.height << endl;    // Output the image dimensions
    out << image.maxValue << endl;         // Output the maximum pixel value
    for (int i = 0; i < image.width*image.height; i++) {
        out << image.pixels[i].red << " " << image.pixels[i].green << " " << image.pixels[i].blue;   // Output the pixel values
        if ((i+1) % 4 == 0)
            out << endl;   // Add a newline after every fourth pixel
        else
            out <<" ";     // Add a space between pixel values
    }
    return out;
}

// Overloaded parentheses operator that allows access to individual pixel values
int& ppmImage::operator()(int x,int y,int colorChanel){
    if(colorChanel==0)
        return pixels[x*height+y].red;     // Return the red value of the specified pixel
    if(colorChanel==1)
        return pixels[x*height+y].green;   // Return the green value of the specified pixel
    return pixels[x*height+y].blue;        // Return the blue value of the specified pixel
}

// Overloaded constant parentheses operator that allows access to individual pixel values
const int& ppmImage::operator()(int x,int y,int colorChanel)const{
    if(colorChanel==0)
        return pixels[x*height+y].red;     // Return the red value of the specified pixel
    if(colorChanel==1)
        return pixels[x*height+y].green;   // Return the green value of the specified pixel
    return pixels[x*height+y].blue;        // Return the blue value of the specified pixel
}

// Swaps the values of two integer variables
void ppmImage::swap(int &n1, int &n2)
{
    int temp = n1;
    n1 = n2;
    n2 = temp;
} 

int read_ppm(const string source_ppm_file_name, ppmImage& destination_object);
int write_ppm(const string destination_ppm_file_name, const ppmImage& source_object);
int test_addition(const string filename_image1, const string filename_image2, const string filename_image3);
int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3);
int test_print(const string filename_image1);
int swap_channels(ppmImage& image_object_to_be_modified, int swap_choice);
ppmImage single_color(const ppmImage& source, int color_choice);

// main function with command-line arguments
int main(int argc, char** argv)
{
    // check for correct number of arguments
    if(argc <3  || argc > 5){
        cout << "Error" << endl;
        return 0;
    }

    // convert first argument to integer
    int choice = stoi(argv[1]);

    // get filenames from arguments
    string ppm_file_name1 = argv[2];
    string ppm_file_name2;
    string ppm_file_name3;
    if(argc==4)
        ppm_file_name2=argv[3];
    if(argc==5){
        ppm_file_name2=argv[3];
        ppm_file_name3=argv[4];
    }

    // create ppmImage objects
    ppmImage image;
    ppmImage resultImage;

    // switch statement based on user choice
    switch (choice)
    {
    case 1:
        // make sure correct number of arguments for this option
        if(argc!=5)
            exit(1);
        // call test_addition function with filenames
        test_addition(ppm_file_name1, ppm_file_name2, ppm_file_name3);
        break;
    case 2:
        // make sure correct number of arguments for this option
        if(argc!=5)
            exit(1);
        // call test_subtraction function with filenames
        test_subtraction(ppm_file_name1, ppm_file_name2, ppm_file_name3);
    case 3:
        // read in ppm file
        read_ppm(ppm_file_name1, image);
        // swap the blue and green channels
        swap_channels(image, 2);
        // write out modified image to new file
        write_ppm(ppm_file_name2, image);
        break;
    case 4:
        // read in ppm file
        read_ppm(ppm_file_name1, image);
        // swap the blue and red channels
        swap_channels(image, 3);
        // write out modified image to new file
        write_ppm(ppm_file_name2, image);
        break;
    case 5:
        // read in ppm file
        read_ppm(ppm_file_name1, image);
        // create new image with only red channel values
        resultImage = single_color(image, 0);
        // write out new image to file
        write_ppm(ppm_file_name2, resultImage);
        break;
    case 6:
        // read in ppm file
        read_ppm(ppm_file_name1, image);
        // create new image with only green channel values
        resultImage = single_color(image, 1);
        // write out new image to file
        write_ppm(ppm_file_name2, resultImage);
        break;
    case 7:
        // read in ppm file
        read_ppm(ppm_file_name1, image);
        // create new image with only blue channel values
        resultImage = single_color(image, 2);
        // write out new image to file
        write_ppm(ppm_file_name2, resultImage);
        break;
    default:
        // print error message if user choice not valid
        cout << "Error!" << endl;
        exit(1);
        break;
    }
    // return 0 to indicate successful program execution
    return 0;
}

// Function to test addition of two PPM images and save the result to a file
int test_addition(const string filename_image1, const string filename_image2, const string filename_image3){
    // Create PPM image objects from file names
    ppmImage image1(filename_image1);
    image1.readPpmImage(filename_image1);
    ppmImage image2(filename_image2);
    image2.readPpmImage(filename_image2);
    // Add the two images and save the result to a third PPM image object
    ppmImage image3=image1+image2;
    // Save the result PPM image object to a file
    return write_ppm(filename_image3,image3);
}

// Function to test subtraction of two PPM images and save the result to a file
int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3){
    // Create PPM image objects from file names
    ppmImage image1(filename_image1);
    image1.readPpmImage(filename_image1);
    ppmImage image2(filename_image2);
    image2.readPpmImage(filename_image2);
    // Subtract the second image from the first and save the result to a third PPM image object
    ppmImage image3=image1-image2;
    // Save the result PPM image object to a file
    return write_ppm(filename_image3,image3);
}

// Function to read a PPM image file and store it in a PPM image object
int read_ppm(const string source_ppm_file_name, ppmImage& destination_object){
    return destination_object.readPpmImage(source_ppm_file_name);
}

// Function to write a PPM image object to a file
int write_ppm(const string destination_ppm_file_name, const ppmImage& source_object){
    return source_object.savePpmImage(destination_ppm_file_name);
}

// Function to test reading a PPM image file
int test_print(const string filename_image1){
    // Create PPM image object from file name
    ppmImage image(filename_image1);
    // Return success code
    return 1;
}
/*This function swaps the color channels of an image object based on the swap_choice parameter. If swap_choice is 1, it swaps the red and green channels. If it is 2, it swaps the red and blue channels. If it is 3, it swaps the green and blue channels. If the swap_choice is not one of these values, the function returns 0.
The function uses nested for loops to iterate through each pixel of the image and swap the specified color channels. The swap function is used to exchange the values of the two specified channels.
The function returns 1 if the swap is successful.*/
int swap_channels(ppmImage& image_object_to_be_modified, int swap_choice){
    int i;
    if(swap_choice==1){
        for(i=0;i<image_object_to_be_modified.getHeight();i++){
            for(int j=0;j<image_object_to_be_modified.getWidth();j++){
                swap(image_object_to_be_modified(i, j, 0), image_object_to_be_modified(i, j, 1));
            }
        }
    }
    else if(swap_choice==2){
        for(i=0;i<image_object_to_be_modified.getHeight();i++){
            for(int j=0;j<image_object_to_be_modified.getWidth();j++){
                swap(image_object_to_be_modified(i, j, 0), image_object_to_be_modified(i, j, 2));
            }
        }
    
    }
    else if(swap_choice==3){
        for(i=0;i<image_object_to_be_modified.getHeight();i++){
            for(int j=0;j<image_object_to_be_modified.getWidth();j++){
                swap(image_object_to_be_modified(i, j, 1), image_object_to_be_modified(i, j, 2));
            }
        }
    }
    else
        return 0;
    return 1;
}

// Function to create a new ppmImage with only one color channel from the source image
// Parameters:
// - source: a constant reference to the source ppmImage
// - color_choice: an integer representing the color channel to keep
//      0: Red channel
//      1: Green channel
//      2: Blue channel
// Returns:
// - a new ppmImage with only the chosen color channel
ppmImage single_color(const ppmImage& source, int color_choice){
    // Create a new ppmImage object with the same dimensions as the source image
    ppmImage temp(source.getWidth(), source.getHeight());
    int i;
    // Iterate over each pixel in the source image
    for(i=0;i<source.getHeight();i++){
        for(int j=0;j<source.getWidth();j++){
            // Depending on the chosen color channel, set the other two channels to 0
            if(color_choice==0){
                temp(i, j, 0) = source(i, j, 0); 
                temp(i, j, 1) = 0;              
                temp(i, j, 2) = 0; 
            }
            else if(color_choice==1){
                temp(i, j, 0) = 0;        
                temp(i, j, 1) = source(i, j, 1); 
                temp(i, j, 2) = 0;
            }
             else if(color_choice==2){
                temp(i, j, 0) = 0;            
                temp(i, j, 1) = 0;             
                temp(i, j, 2) = source(i, j, 2);
            }
            // If an invalid color_choice is provided, print an error message
            else
                cout << "Error" << endl;
        }
    }
    // Return the new ppmImage with only the chosen color channel
    return temp;
}
