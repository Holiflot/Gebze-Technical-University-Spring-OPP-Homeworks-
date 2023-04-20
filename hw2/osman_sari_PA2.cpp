#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
class ImageConverter{
    public:
        ImageConverter();
        void openImageMenu();
        void saveImageMenu();
        void grayscaleMenu();
        void scriptsMenu();
    private:
        vector<int>pixels;
        int width;
        int height;
        int max_color;
        string file_type;
};
ImageConverter::ImageConverter(): width(0), height(0), pixels() {}
void ImageConverter::openImageMenu(){
    int choice;
    string fileName;
    cout << "OPEN AN IMAGE MENU" << endl;
    cout << "0 - UP" << endl;
    cout << "1 - Enter The Name Of The Image File" << endl;
    cin >> choice;
    while(choice !=0){
        if(choice==0)
            return;
        else if(choice==1){
            cin >> fileName;
            ifstream input_file(fileName);
            if (!input_file.is_open()) {
                cout << "File is not open!" << endl;
                exit(1);
            }
            input_file >> file_type >> width >> height >> max_color;
            if (file_type != "P3") {
                cout << "File format not supported!" << endl;
                exit(1);
            }
            pixels.resize(height * width * 3);
            int value;
            for (int i = 0; i < height * width * 3; i++) {
                input_file >> value;
                pixels[i] = value;
            }
            input_file.close();
            return;
        }
        else
            cout << "Invalid choice. Please try again." << endl;
    }
    
}
void ImageConverter::saveImageMenu(){
    int choice;
    string fileName;
    cout << "SAVE IMAGE DATA MENU" << endl;
    cout << "0 - UP" << endl;
    cout << "1 - Enter A File Name" << endl;
    cin >> choice; 
    while(choice !=0){
        if(choice ==0)
            return;
        else if(choice == 1){
            cin >> fileName;
            ofstream outfile(fileName);
            if(!outfile) {
                cout << "File is not open!" << endl;
                exit(1);
            }
            outfile << file_type << endl;
            outfile << width << " "  << height  << endl;
            outfile << max_color << endl;
            for (int i = 0; i < width*height*3; i++) {
                outfile << pixels[i];
                if ((i+1) % 12 == 0)
                    outfile << endl;
                else
                    outfile <<" ";
            }
            outfile.close();
            return;
        }
        else
            cout << "Invalid choice. Please try again." << endl;
    }
}
void ImageConverter::grayscaleMenu(){
    int choice;
    cout << "CONVERT TO GRAYSCALE MENU" << endl;
    cout << "0 - UP" << endl;
    cout << "1 - Enter Coefficients For RED GREEN And BLUE Channels." << endl;
    cin >> choice;
    while(choice !=0){
        switch (choice)
        {
            case 0:
                return;
                break;
            case 1:
                double n1,n2,n3;
                cin >> n1 >> n2 >> n3;
                while((n1>=1 || n1<0) || (n2>=1 || n2<0) || (n3>=1 || n3<0)){
                    cout << "it must between 0 to 1. 1 is not valid!" << endl;
                    cin >> n1 >> n2 >> n3;
                }
                int temp;
                for (int i = 0; i < width*height*3; i++) {
                    if(i%3==0){
                        temp=pixels[i]*n1+ pixels[i+1]*n2+pixels[i+2]*n3;
                        pixels[i]=temp;
                        pixels[i+1]=temp;
                        pixels[i+2]=temp;
                    }
                    if(pixels[i]>max_color)
                        pixels[i]=max_color;
                }
                return;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}
void ImageConverter::scriptsMenu(){
    int choice;
    cout << "SCRIPTS MENU" << endl;
    cout << "0 - UP" << endl;
    cout << "1 - Convert To Grayscale(D)" << endl;
    cin >> choice;
    while(choice !=0){
        switch (choice)
        {
            case 0:
                return;
                break;
            case 1:
                grayscaleMenu();
                return;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}

int main(){
    int choose;
    ImageConverter image;
    do
    {
        cout << "Main Menu" << endl;
        cout << "0 - Exit" << endl;
        cout << "1 - Open An Image(D)" << endl;
        cout << "2 - Save Image Data(D)" << endl;
        cout << "3 - Scripts(D)" << endl;
        cin >> choose;
        switch (choose)
        {
        case 0:
            break;
        case 1:
            image.openImageMenu();
            break;
        case 2:
            image.saveImageMenu();
            break;
        case 3:
            image.scriptsMenu();
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choose!=0);
    
}