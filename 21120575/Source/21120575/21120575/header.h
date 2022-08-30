#pragma once
#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;
#pragma pack(1)

// cau truc header
struct header {
    char type[2];
    uint32_t size;
    uint32_t reserved;
    uint32_t dataoffset;
};

// cau truc dib
struct dib {
    uint32_t size;
    int32_t	 width;
    int32_t  height;
    uint16_t planes;
    uint16_t bpp;

    uint32_t compression;
    uint32_t imagesize;
    int32_t  xpb;
    int32_t  ypb;
    uint32_t colorused;
    uint32_t colorimportant;
};

// cau truc cua 1 pixel diem anh cua hinh bmp 8bit
struct pix8 {
    uint8_t color;
};

// cau truc cua 1 pixel diem anh cua hinh bmp 24bit
struct pix24 {         
    uint8_t b;
    uint8_t r;
    uint8_t g;
};

// cau truc cua 1 pixel diem anh cua hinh bmp 32bit
struct pix32 {
    uint8_t a;
    uint8_t b;
    uint8_t r;
    uint8_t g;
};

// bang mau cua hinh bmp 8bit
struct colortable8 {
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t reserved;
};

struct bmp {
    header header;
    dib dib;
    colortable8 colortable[256];
    char* pdibreversed;
    char* pimagedata;
};

// cau truc cua 1 file bmp 8
struct bmp8 {         
    header header;
    dib dib;
    pix24 pix;
    colortable8 colortable[256];
    char* pdibreversed;
    char* pimagedata;
};

// cau truc của 1 file bmp 24
struct bmp24 {         
    header header;
    dib dib;
    pix24 pix;
    char* pdibreversed;
    char* pimagedata;
};

// cau truc của 1 file bmp 32
struct bmp32 {         
    header header;
    dib dib;
    pix32 pix;
    char* pdibreversed;
    char* pimagedata;
};

// gioi thieu 
void introduce() {
    cout << "------------BTL BMP----------" << endl;
    cout << "|Ho va Ten: Nguyen Thanh Tri |" << endl;
    cout << "|MSSV : 21120575             |" << endl;
    cout << "|Lop : 21CTT5                |" << endl;
    cout << "|GVHD : Pham Minh Hoang      |" << endl;
    cout << "-----------------------------" << endl;
}

char path_in[100], path_out[100];

void input_path(char path_in[512]) {
    cout << "\nNhap dia chi doc file (VD : D:\\pic_in.bmp ) : ";
    cin.getline(path_in, 512);
}

void output_path(char path_out[512]) {
    cout << "\nNhap dia chi xuat file (VD : D:\\pic_out.bmp ) : ";
    cin.getline(path_out, 512);
}

// ham doc file bmp
int read8(const char* filename, bmp8& bmp) {
    ifstream f(filename, ios::binary);
    // kiem tra file mo duoc khong
    if (!f.is_open()) {
        cout << "Khong the mo file ";
        return 0;
    }
    // dua con tro den vi tri dau file
    f.seekg(0, f.beg);

    // doc header
    f.read((char*)&bmp.header, 14);

    // doc dib
    f.read((char*)&bmp.dib, 40);

    // kiem tra xem co phan du khong
    if (bmp.dib.size > 40) {
        // tinh kich thuoc phan du
        int t = bmp.dib.size - 40;
        // cap phat vung nho phan du
        bmp.pdibreversed = new char[t];
        // doc phan du
        f.read(bmp.pdibreversed, t);
    }

    // doc bang mau cua file bmp 8bit (chi danh cho 8bit) 
    if (bmp.dib.bpp == 8) {
        f.read((char*)&bmp.colortable, sizeof(colortable8) * 256);
    }

    // cap phat vung nho cua diem anh
    bmp.pimagedata = new char[bmp.dib.imagesize];

    // doc du lieu diem anh
    f.read(bmp.pimagedata, bmp.dib.imagesize);

    f.close();

    return 1;
}

// ham doc file bmp 24bit
int read24(char* filename, bmp24& bmp) {
    ifstream f(filename, ios::binary);
    // kiem tra file mo duoc khong
    if (!f.is_open()) {
        cout << "Khong the mo file ";
        return 0;
    }

    // dua con tro den vi tri dau file
    f.seekg(0, f.beg);

    // doc header
    f.read((char*)&bmp.header, 14);

    // doc dib
    f.read((char*)&bmp.dib, 40);


    // kiem tra xem co phan du khong
    if (bmp.dib.size > 40) {
        // tinh kich thuoc phan du
        int t = bmp.dib.size - 40;

        // cap phat vung nho phan du
        bmp.pdibreversed = new char[t];

        // doc phan du
        f.read(bmp.pdibreversed, t);
    }

    // cap phat vung nho cua diem anh
    bmp.pimagedata = new char[bmp.dib.imagesize];

    // doc du lieu diem anh
    f.read(bmp.pimagedata, bmp.dib.imagesize);

    f.close();
    return 1;
}

// ham doc file bmp 32bit
int read32(const char* filename, bmp32& bmp) {
    ifstream f(filename, ios::binary);
    // kiem tra file mo duoc khong
    if (!f.is_open()) {
        cout << "Khong the mo file ";
        return 0;
    }

    // dua con tro den vi tri dau file
    f.seekg(0, f.beg);

    // doc header
    f.read((char*)&bmp.header, 14);

    // doc dib
    f.read((char*)&bmp.dib, 40);

    // kiem tra xem co phan du khong
    if (bmp.dib.size > 40) {
        // tinh kich thuoc phan du
        int t = bmp.dib.size - 40;

        // cap phat vung nho phan du
        bmp.pdibreversed = new char[t];

        // doc phan du
        f.read(bmp.pdibreversed, t);
    }

    // cap phat vung nho cua diem anh
    bmp.pimagedata = new char[bmp.dib.imagesize];

    // doc du lieu diem anh
    f.read(bmp.pimagedata, bmp.dib.imagesize);

    f.close();
    return 1;
}

// ham doc file bmp 
int readglobal(char* filename, bmp& bmp) {
    ifstream f(filename, ios::binary);
    
    // kiem tra file mo duoc khong
    if (!f.is_open()) {
        cout << "Khong the mo file ";
        return 0;
    }

    // dua con tro den vi tri dau file
    f.seekg(0, f.beg);

    // doc header
    f.read((char*)&bmp.header, 14);

    // doc dib
    f.read((char*)&bmp.dib, 40);

    // kiem tra xem co phan du khong
    if (bmp.dib.size > 40) {
        // tinh kich thuoc phan du
        int t = bmp.dib.size - 40;

        // cap phat vung nho phan du
        bmp.pdibreversed = new char[t];

        // doc phan du
        f.read(bmp.pdibreversed, t);
    }

    // doc bang mau cua file bmp 8bit
    // chi danh cho 8bit 
    if (bmp.dib.bpp == 8) {
        f.read((char*)&bmp.colortable, sizeof(colortable8) * 256);
    }

    // cap phat vung nho cua diem anh
    bmp.pimagedata = new char[bmp.dib.imagesize];

    // doc du lieu diem anh
    f.read(bmp.pimagedata, bmp.dib.imagesize);

    f.close();
    return 1;
}

// ham ghi file bmp 8bit
int write8( char* filename, bmp8 bmp) {
    ofstream f(filename, ios::binary);

    // kiem tra 
    if (!f) {
        cout << "Khong the ghi file ";
        return 0;
    }

    // ghi header vao file
    f.write((char*)&bmp.header, 14);

    // ghi dib vao file
    f.write((char*)&bmp.dib, 40);

    if (bmp.dib.size > 40) {
        int t = bmp.dib.size - 40;
        // ghi phan du vao file
        f.write(bmp.pdibreversed, t);
    }
    
    // ghi bang mau cua file bmp 8bit vao file
    if (bmp.dib.bpp == 8) {
        f.write((char*)&bmp.colortable, sizeof(colortable8) * 256);
    }
    // ghi du lieu diem anh vao file
    f.write(bmp.pimagedata, bmp.dib.imagesize);

    f.close();
    return 1;
}

// ham ghi file bmp 24bit
int write24(const char* filename, bmp24 bmp) {
    ofstream f(filename, ios::binary);

    // kiem tra 
    if (!f) {
        cout << "Khong the ghi file ";
        return 0;
    }

    // ghi header vao file
    f.write((char*)&bmp.header, 14);

    // ghi dib vao file
    f.write((char*)&bmp.dib, 40);

    if (bmp.dib.size > 40) {
        int t = bmp.dib.size - 40;
        // ghi phan du vao file
        f.write(bmp.pdibreversed, t);
    }

    // ghi du lieu diem anh vao file
    f.write(bmp.pimagedata, bmp.dib.imagesize);

    f.close();
    return 1;
}

// ham ghi file bmp 32 bit
int write32(const char* filename, bmp32 bmp) {
    ofstream f(filename, ios::binary);

    // kiem tra 
    if (!f) {
        cout << "Khong the ghi file ";
        return 0;
    }

    // ghi header vao file
    f.write((char*)&bmp.header, 14);

    // ghi dib vao file
    f.write((char*)&bmp.dib, 40);

    if (bmp.dib.size > 40) {
        int t = bmp.dib.size - 40;
        // ghi phan du vao file
        f.write(bmp.pdibreversed, t);
    }

    // ghi du lieu diem anh vao file
    f.write(bmp.pimagedata, bmp.dib.imagesize);

    f.close();
    return 1;
}

// ham giai phong du lieu mang pix 8 
void releasepix8(pix8*& pixel) {
    delete[] pixel;
}

// ham giai phong du lieu mang pix 24
void releasepix24(pix24*& pixel) {
    delete[] pixel;
}

// ham giai phong du lieu mang pix 32
void releasepix32(pix32*& pixel) {
    delete[] pixel;
}

void releasebmp8(bmp8& bmp) {
    delete[] bmp.pimagedata;
    bmp.pimagedata = NULL;
}

void releasebmp24(bmp24& bmp) {
    delete[] bmp.pimagedata;
    bmp.pimagedata = NULL;
}

void releasebmp32(bmp32& bmp) {
    delete[] bmp.pimagedata;
    bmp.pimagedata = NULL;
}