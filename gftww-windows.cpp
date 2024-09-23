#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <shlobj.h>
#include <ctime>

using namespace std;

string simpleEncrypt(const string& text) {
    string encrypted;
    for (char c : text) {
        encrypted += c + 3;
    }
    return encrypted;
}

string simpleDecrypt(const string& text) {
    string decrypted;
    for (char c : text) {
        decrypted += c - 3;
    }
    return decrypted;
}

void setTextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printWithAnimation(const string& text, int color = 7, int speed = 30) {
    setTextColor(color);
    for (char c : text) {
        cout << c;
        Sleep(speed);
    }
    setTextColor(7); 
}

string getDesktopPath() {
    char path[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, path))) {
        return string(path);
    }
    else {
        return "";
    }
}

void createFile() {
    system("cls");

    printWithAnimation("Enter text to encrypt: ", 10);
    string text;
    getline(cin, text);

    string encryptedText = simpleEncrypt(text);

    string desktopPath = getDesktopPath();
    if (desktopPath.empty()) {
        printWithAnimation("Error: Could not determine Desktop path!\n", 12);
        system("pause");
        return;
    }

    printWithAnimation("Enter file name (without extension): ", 10);
    string fileName;
    getline(cin, fileName);

    string fullPath = desktopPath + "\\" + fileName + ".gftww";

    ofstream outFile(fullPath);
    if (!outFile) {
        printWithAnimation("Error: Could not create file! Check the path or permissions.\n", 12);
        system("pause");
        return;
    }

    outFile << encryptedText;
    outFile.close();

    printWithAnimation("File successfully created at: " + fullPath + "\n", 10);
    system("pause");
}

void decryptFile() {
    system("cls");

    string desktopPath = getDesktopPath();
    if (desktopPath.empty()) {
        printWithAnimation("Error: Could not determine Desktop path!\n", 12);
        system("pause");
        return;
    }

    printWithAnimation("Enter file name (without extension): ", 14);
    string fileName;
    getline(cin, fileName);

    string fullPath = desktopPath + "\\" + fileName + ".gftww";

    ifstream inFile(fullPath);
    if (!inFile) {
        printWithAnimation("Error: File not found! Make sure the file exists on your Desktop.\n", 12);
        system("pause");
        return;
    }

    string encryptedText((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();

    string decryptedText = simpleDecrypt(encryptedText);

    system("cls");
    printWithAnimation("Decrypted text: ", 14);
    cout << decryptedText << endl;
    system("pause");
}

void showAuthor() {
    system("cls");
    printWithAnimation("=== authors ===\n", 11);
    printWithAnimation("Program created by mkfs.ext4\n", 14, 50);
    printWithAnimation("Special thanks to Drom\n", 11, 50);
    printWithAnimation("This utility encrypts and decrypts files.\n", 10, 50);
    system("pause");
}

int main() {
    while (true) {
        system("cls");

        printWithAnimation("=== gftww-windows-stable ===\n", 11);
        printWithAnimation("1. mkfile\n", 10);
        printWithAnimation("2. decrypt\n", 10);
        printWithAnimation("3. authors\n", 10);
        printWithAnimation("4. quit\n", 10);

        char choice = _getch();
        switch (choice) {
        case '1':
            createFile();
            break;
        case '2':
            decryptFile();
            break;
        case '3':
            showAuthor();
            break;
        case '4':
            return 0;
        default:
            break;
        }
    }
}
