

#include "header.h"
// ham chuyen du lieu diem anh vao du lieu pix cua hinh 8bit
pix8* convertDataToPixelArray8(char*& data, dib& src) {
    // khai bao kich thuoc cua hinh
    int sizearray = src.width * src.height;

    // cap phat vung nho cho mang du lieu pix8
    pix8* pixels = new pix8[sizearray * 2];

    // tinh papdding
    int padding = (4 - (src.width * src.bpp / 8) % 4) % 4;

    char* temp = data;

    // ghi cac du lieu diem anh vao mang du lieu pix8
    for (int i = 0; i < src.height; i++) {
        for (int j = 0; j < src.width; j++) {
            pixels[i * src.width + j].color = *(temp++);
        }
        // bo qua cac padding
        temp += padding;
    }
    return pixels;
}

// ham chuyen du lieu diem anh vao du lieu pix cua hinh 24bit
pix24* convertDataToPixelArray24(char*& data, dib& src) {
    // khai bao kich thuoc cua hinh
    int sizearray = src.width * src.height;

    // cap phat vung nho cho mang du lieu pix24
    pix24* pixels = new pix24[sizearray * 2];

    // tinh padding
    int padding = (4 - (src.width * src.bpp / 8) % 4) % 4;

    char* temp = data;

    // ghi cac du lieu diem anh vao mang du lieu pix24
    for (int i = 0; i < src.height; i++) {
        for (int j = 0; j < src.width; j++) {
            pixels[i * src.width + j].b = *(temp++);
            pixels[i * src.width + j].g = *(temp++);
            pixels[i * src.width + j].r = *(temp++);
        }
        // bo qua cac padding
        temp += padding;
    }
    return pixels;
}

// ham chuyen du lieu diem anh vao du lieu pix cua hinh 32bit
pix32* convertDataToPixelArray32(char*& data, dib& src) {
    // khai bao kich thuoc cua hinh
    int sizearray = src.width * src.height;

    // cap phat vung nho cho mang du lieu pix32
    pix32* pixels = new pix32[sizearray * 2];

    // tinh padding
    int padding = (4 - (src.width * src.bpp / 8) % 4) % 4;

    char* temp = data;

    // ghi cac du lieu diem anh vao mang du lieu pix32
    for (int i = 0; i < src.height; i++) {
        for (int j = 0; j < src.width; j++) {
            pixels[i * src.width + j].b = *(temp++);
            pixels[i * src.width + j].g = *(temp++);
            pixels[i * src.width + j].r = *(temp++);
            pixels[i * src.width + j].a = *(temp++);
        }
        // bo qua cac padding
        temp += padding;
    }
    return pixels;
}

// ham chuyen du lieu pix cua hinh 8bit sang du lieu diem anhSS
char* convertPixelArray8ToData(pix8*& pixels, dib& dst) {
    // tinh padding
    int padding = (4 - (dst.width * dst.bpp / 8) % 4) % 4;

    // tinh kich thuoc cua mang du lieu diem anh
    int size = dst.width * dst.height * (dst.bpp / 8) + padding * dst.height;

    // cap phat vung nho cho mang du lieu diem anh
    char* data = new char[size];
    char* temp = data;

    // ghi cac du lieu pix vao mang du lieu diem anh
    for (int i = 0; i < dst.height; i++) {
        for (int j = 0; j < dst.width; j++) {
            *(temp++) = pixels[i * dst.width + j].color;
        }
        for (int k = 0; k < padding; k++) {
            *(temp++) = 0;
        }
    }
    return data;
}

// ham chuyen du lieu pix cua hinh 24bit sang du lieu diem anh
char* convertPixelArray24ToData(pix24*& pixels, dib& dst) {
    // tinh padding
    int padding = (4 - (dst.width * dst.bpp / 8) % 4) % 4;

    // tinh kich thuoc cua mang du lieu diem anh
    int size = dst.width * dst.height * (dst.bpp / 8) + padding * dst.height;

    // cap phat vung nho cho mang du lieu diem anh
    char* data = new char[size];
    char* temp = data;

    // ghi cac du lieu pix vao mang du lieu diem anh
    for (int i = 0; i < dst.height; i++) {
        for (int j = 0; j < dst.width; j++) {
            *(temp++) = pixels[i * dst.width + j].b;
            if (dst.bpp != 8) {
                *(temp++) = pixels[i * dst.width + j].g;
                *(temp++) = pixels[i * dst.width + j].r;
            }
        }
        for (int k = 0; k < padding; k++) {
            *(temp++) = 0;
        }
    }
    return data;
}

// ham chuyen du lieu pix cua hinh 32bit sang du lieu diem anh
char* convertPixelArray32ToData(pix32*& pixels, dib& dst) {
    // tinh padding
    int padding = (4 - (dst.width * dst.bpp / 8) % 4) % 4;

    // tinh kich thuoc cua mang du lieu diem anh
    int size = dst.height * dst.width * (dst.bpp / 8) + padding * dst.height;

    // cap phat vung nho cho mang du lieu diem anh
    char* data = new char[size];
    char* temp = data;

    // ghi cac du lieu pix vao mang du lieu diem anh
    for (int i = 0; i < dst.height; i++) {
        for (int j = 0; j < dst.width; j++) {
            *(temp++) = pixels[i * dst.width + j].b;
            if (dst.bpp != 8) {
                *(temp++) = pixels[i * dst.width + j].g;
                *(temp++) = pixels[i * dst.width + j].r;
                *(temp++) = pixels[i * dst.width + j].a;
            }
        }
        for (int k = 0; k < padding; k++) {
            *(temp++) = 0;
        }
    }

    return data;
}

// ham chuyen doi file bmp 24bit sang file bmp 8bit
int convert24to8bit(bmp24 src, bmp8& dst) {
    // kiem tra bpp cua file src
    if (src.dib.bpp != 24 || src.dib.bpp == NULL)
        return 0;

    // gan header,dib,reveresed cua file source cho destination
    dst.header = src.header;
    dst.dib = src.dib;
    dst.pdibreversed = src.pdibreversed;

    // gan bpp cua file destinaton bang 8
    dst.dib.bpp = 8;

    // tinh padding
    int padding = (4 - (dst.dib.width * dst.dib.bpp / 8) % 4) % 4;

    // tinh kich thuoc cua anh
    dst.dib.imagesize = dst.dib.width * dst.dib.height * dst.dib.bpp / 8 + padding * dst.dib.height;

    // gan mau cho bang mau cua file bmp 8bit
    for (int i = 0; i < 256; i++) {
        dst.colortable[i].b = i;
        dst.colortable[i].g = i;
        dst.colortable[i].r = i;
        dst.colortable[i].reserved = 0;
    }

    // tao mot mang srcpixel chua cac du lieu pix cua file bmp 24bit
    pix24* srcpixels = convertDataToPixelArray24(src.pimagedata, src.dib);

    // cap phat bo nho cho mang du lieu pix cua file bmp 8bit 
    // tam thoi luu pix cua file bmp8bit vao trong mang pix24
    pix24* dstpixels = new pix24[dst.dib.width * dst.dib.height];


    char ave;
    // tinh gia tri trung binh cua 1 diem anh pix va gan vao pix cua destination
    for (int i = 0; i < dst.dib.height; i++) {
        for (int j = 0; j < dst.dib.width; j++) {
            int index = i * dst.dib.width + j;
            ave = (char)((srcpixels[index].r + srcpixels[index].g + srcpixels[index].b) / 3);
            dstpixels[index].r = dstpixels[index].g = dstpixels[index].b = ave;
        }
    }

    // mang pix cua destination khi vao trong ham convert se chuyen thanh du lieu diem anh cua file bmp8bit
    dst.pimagedata = convertPixelArray24ToData(dstpixels, dst.dib);


    // giai phong bo nho cho 2 mang pix cua src va dst file
    releasepix24(srcpixels);
    releasepix24(dstpixels);

    return 1;
}

// ham chuyen doi file bmp 24bit sang file bmp 8bit
int convert32to8bit(bmp32 src, bmp8& dst) {
    // kiem tra bpp cua file src
    if (src.dib.bpp != 32 || src.dib.bpp == NULL)
        return 0;

    // gan header,dib,reveresed cua file source cho destination
    dst.header = src.header;
    dst.dib = src.dib;
    dst.pdibreversed = src.pdibreversed;

    // gan bpp cua file destinaton bang 8
    dst.dib.bpp = 8;

    // tinh padding
    int padding = (4 - (dst.dib.width * dst.dib.bpp / 8) % 4) % 4;

    // tinh kich thuoc cua anh
    dst.dib.imagesize = dst.dib.width * dst.dib.height * dst.dib.bpp / 8 + padding * dst.dib.height;

    // gan mau cho bang mau cua file bmp 8bit
    for (int i = 0; i < 256; i++) {
        dst.colortable[i].b = i;
        dst.colortable[i].g = i;
        dst.colortable[i].r = i;
        dst.colortable[i].reserved = 0;
    }

    // tao mot mang srcpixel chua cac du lieu pix cua file bmp 32bit
    pix32* srcpixels = convertDataToPixelArray32(src.pimagedata, src.dib);

    // cap phat bo nho cho mang du lieu pix cua file bmp 8bit 
    // tam thoi luu pix cua file bmp8bit vao trong mang pix32
    pix32* dstpixels = new pix32[dst.dib.width * dst.dib.height];

    char ave;
    // tinh gia tri trung binh cua 1 diem anh pix va gan vao pix cua destination
    for (int i = 0; i < dst.dib.height; i++) {
        for (int j = 0; j < dst.dib.width; j++) {
            int index = i * dst.dib.width + j;
            ave = (char)((srcpixels[index].r + srcpixels[index].g + srcpixels[index].b) / 3);
            dstpixels[index].r = dstpixels[index].g = dstpixels[index].b = dstpixels[index].a = ave;
        }
    }
    // mang pix cua destination khi vao trong ham convert se chuyen thanh du lieu diem anh cua file bmp8bit
    dst.pimagedata = convertPixelArray32ToData(dstpixels, dst.dib);

    // giai phong bo nho cho 2 mang pix cua src va dst file
    releasepix32(srcpixels);
    releasepix32(dstpixels);

    return 1;
}

// ham tinh trung binh mang pixel theo ti le s cua file bmp 8bit 
void average8(pix8* srcpixels, pix8*& dstpixels, bmp8 dst, int s) {
    unsigned int color;

    int squarex, squarey, index = 0;

    // hai vong for dau tien - chay qua tung o vuong co kich thuoc s*s trong mang du lieu diem anh
    // hai vong for tiep theo - chay qua tung pixel trong cac o vuong cua 2 vong for dau tien
    for (int i = 0; i <= dst.dib.height - s; i += s) {
        for (int j = 0; j <= dst.dib.width - s; j += s) {
            color = 0;
            squarey = 0;
            for (int k = i; squarey < s; k++) {
                squarex = 0;
                for (int l = j; squarex < s; l++) {
                    // tinh tong cac pix của file bmp 8bit trong mang pix 
                    color += srcpixels[k * dst.dib.width + l].color;
                    squarex++;
                }
                squarey++;
            }
            // chia trung binh tong cac pix trong mang 
            color = (char)(color / (s * s));
            // gan vao mang pix cua file destination
            dstpixels[index].color = (char)color;
            index++;
        }

    }
}

// ham tinh trung binh mang pixel theo ti le s cua file bmp 24bit 
void average24(pix24* srcpixels, pix24*& dstpixels, bmp24 dst, int s) {
    unsigned int avebgr[3] = {0};

    int squarex, squarey, index = 0;
    int padding = (4 - (dst.dib.width * dst.dib.bpp / 8) % 4) % 4;
    // hai vong for dau tien - chay qua tung o vuong co kich thuoc s*s trong mang du lieu diem anh
    // hai vong for tiep theo - chay qua tung pixel trong cac o vuong cua 2 vong for dau tien
    for (int i = 0; i <= dst.dib.height - s; i += s) {
        for (int j = 0; j <= dst.dib.width - s; j += s) {
            avebgr[0] = avebgr[1] = avebgr[2] = 0;
            squarey = 0;
            for (int k = i; squarey < s; k++) {
                squarex = 0;
                for (int l = j; squarex < s; l++) {
                    // tinh tong cac pix của file bmp 8bit trong mang pix 
                    avebgr[0] += srcpixels[k * dst.dib.width + l].b;
                    avebgr[1] += srcpixels[k * dst.dib.width + l].g;
                    avebgr[2] += srcpixels[k * dst.dib.width + l].r;
                    squarex++;
                }
                squarey++;
            }
            // chia trung binh tong cac pix trong mang
            avebgr[0] = (char)(avebgr[0] / (s * s));
            avebgr[1] = (char)(avebgr[1] / (s * s));
            avebgr[2] = (char)(avebgr[2] / (s * s));

            // gan vao mang pix cua file destination
            dstpixels[index].b = (char)avebgr[0];
            dstpixels[index].g = (char)avebgr[1];
            dstpixels[index].r = (char)avebgr[2];
            index++;
        }
    }

}

// ham tinh trung binh mang pixel theo ti le s cua file bmp 24bit 
void average32(pix32* srcpixels, pix32*& dstpixels, bmp32 dst, int s) {
    unsigned int avebgr[4] = {0};

    int squarex, squarey, index = 0;

    // hai vong for dau tien - chay qua tung o vuong co kich thuoc s*s trong mang du lieu diem anh
    // hai vong for tiep theo - chay qua tung pixel trong cac o vuong cua 2 vong for dau tien
    for (int i = 0; i <= dst.dib.height - s; i += s) {
        for (int j = 0; j <= dst.dib.width - s; j += s) {
            avebgr[0] = avebgr[1] = avebgr[2] = avebgr[3] = 0;
            squarey = 0;
            for (int k = i; squarey < s; k++) {
                squarex = 0;
                for (int l = j; squarex < s; l++) {
                    // tinh tong cac pix của file bmp 8bit trong mang pix 
                    avebgr[0] += srcpixels[k * dst.dib.width + l].a;
                    avebgr[1] += srcpixels[k * dst.dib.width + l].b;
                    avebgr[2] += srcpixels[k * dst.dib.width + l].g;
                    avebgr[3] += srcpixels[k * dst.dib.width + l].r;
                    squarex++;
                }
                squarey++;
            }
            // chia trung binh tong cac pix trong mang
            avebgr[0] = (char)(avebgr[0] / (s * s));
            avebgr[1] = (char)(avebgr[1] / (s * s));
            avebgr[2] = (char)(avebgr[2] / (s * s));
            avebgr[3] = (char)(avebgr[3] / (s * s));

            // gan vao mang pix cua file destination
            dstpixels[index].a = (char)avebgr[0];
            dstpixels[index].b = (char)avebgr[1];
            dstpixels[index].g = (char)avebgr[2];
            dstpixels[index].r = (char)avebgr[3];

            index++;
        }

    }

}

// ham thu nho file bmp 8bit
int resize8(bmp8 src, bmp8& dst, int s) {
    // kiem tra bpp
    if (src.dib.bpp != 8)
        return 0;

    // gan du lieu cua src vao dst
    dst = src;

    // tinh padding 
    int paddingsrc = (4 - (src.dib.width * src.dib.bpp / 8) % 4) % 4;

    // chuyen du lieu diem anh cua file src vao du lieu pix cua file src
    pix8* srcpixels = convertDataToPixelArray8(src.pimagedata, src.dib);

    // cap phat bo nho
    pix8* dstpixels = new pix8[dst.dib.width * dst.dib.height];

    // ham xu li
    average8(srcpixels, dstpixels, dst, s);

    // tinh lai chieu dai , chieu rong 
    dst.dib.height = (dst.dib.height / s);
    dst.dib.width = (dst.dib.width / s);

    // tinh lai padding anh 
    int paddingdst = (4 - (dst.dib.width * dst.dib.bpp / 8) % 4) % 4;
    // tinh lai kich thuoc anh 
    dst.dib.imagesize = dst.dib.height * dst.dib.width * dst.dib.bpp / 8 + paddingdst * dst.dib.height;

    // chuyen du lieu pix cua hinh 8bit sang du lieu diem anh
    dst.pimagedata = convertPixelArray8ToData(dstpixels, dst.dib);

    // giai phong bo nho cho 2 mang pix cua src va dst file
    releasepix8(srcpixels);
    releasepix8(dstpixels);

    return 1;
}

// ham thu nho file bmp 24bit
int resize24(bmp24 src, bmp24& dst, int s) {
    // kiem tra bpp
    if (src.dib.bpp != 24)
        return 0;

    // gan du lieu cua src vao dst
    dst = src;

    // tinh padding
    int paddingsrc = (4 - (src.dib.width * src.dib.bpp / 8) % 4) % 4;

    // chuyen du lieu diem anh cua file src vao du lieu pix cua file src
    pix24* srcpixels = convertDataToPixelArray24(src.pimagedata, dst.dib);

    // cap phat bo nho
    pix24* dstpixels = new pix24[dst.dib.width * dst.dib.height];

    // ham xu li
    average24(srcpixels, dstpixels, dst, s);

    // tinh lai chieu dai , chieu rong 
    dst.dib.height /= s;
    dst.dib.width /= s;

    int paddingdst = (4 - (dst.dib.width * dst.dib.bpp / 8) % 4) % 4;

    // chuyen du lieu pix cua hinh 8bit sang du lieu diem anh
    dst.dib.imagesize = dst.dib.height * dst.dib.width * dst.dib.bpp / 8 + paddingdst * dst.dib.height;

    // chuyen du lieu pix cua hinh 8bit sang du lieu diem anh
    dst.pimagedata = convertPixelArray24ToData(dstpixels, dst.dib);

    // giai phong bo nho cho 2 mang pix cua src va dst file
    releasepix24(srcpixels);
    releasepix24(dstpixels);

    return 1;
}

// ham thu nho file bmp 32bit
int resize32(bmp32 src, bmp32& dst, int s) {
    // kiem tra bpp
    if (src.dib.bpp != 32)
        return 0;

    // gan du lieu cua src vao dst
    dst = src;

    // tinh padding
    int paddingsrc = (4 - (src.dib.width * src.dib.bpp / 8) % 4) % 4;

    // chuyen du lieu diem anh cua file src vao du lieu pix cua file src
    pix32* srcpixels = convertDataToPixelArray32(dst.pimagedata, dst.dib);

    // cap phat bo nho
    pix32* dstpixels = new pix32[dst.dib.width * dst.dib.height];

    average32(srcpixels, dstpixels, dst, s);

    // tinh lai chieu dai , chieu rong
    dst.dib.height /= s;
    dst.dib.width /= s;

    // tinh lai padding
    int paddingdst = (4 - (dst.dib.width * dst.dib.bpp / 8) % 4) % 4;

    // chuyen du lieu pix cua hinh 8bit sang du lieu diem anh
    dst.dib.imagesize = dst.dib.height * dst.dib.width * dst.dib.bpp / 8 + paddingdst * dst.dib.height;

    // chuyen du lieu pix cua hinh 8bit sang du lieu diem anh
    dst.pimagedata = convertPixelArray32ToData(dstpixels, dst.dib);

    // giai phong bo nho cho 2 mang pix cua src va dst file
    releasepix32(srcpixels);
    releasepix32(dstpixels);

    return 1;
}

int main(int argc, char* argv[]) {
    // tao mot bien global dang bmp de kiem tra xem file input co bpp bang bao nhieu
    bmp global;

    bmp24 src24;
    bmp32 src32;
    bmp8 src8;
    bmp8 dst;

    introduce();
    if (argc == 1) {
        // Menu
        cout << endl << "Menu" << endl;
        cout << "1. Convert anh 24/32 bit sang anh 8 bit" << endl;
        cout << "2. Thu nho anh 8/24/32 bit theo ti le S " << endl;
        cout << "0. Ngung chuong trinh" << endl;
        cout << "Nhap lua chon : ";


        int selection = -1;
        cin >> selection;

        while (selection < 0 || selection > 2) {
            cout << "Lua chon khong hop le. Moi ban nhap lai : ";
            cin >> selection;
        }

        if (selection == 0)
            return 0;

        cin.ignore();
        input_path(path_in);
        output_path(path_out);

        if (selection == 1) {

            // doc file input vao global
            readglobal(path_in, global);

            if (global.dib.bpp == 24) {
                if (read24(path_in, src24)) {            
                    cout << "Doc file 24 thanh cong!\n";
                }
                else
                    cout << "Doc file that bai!\n";

                if (convert24to8bit(src24, dst)) {         
                    cout << "Chuyen bit thanh cong!\n";
                }
                else
                    cout << "Chuyen bit that bai\n";

                if (write8(path_out, dst)) {    
                    cout << "Ghi file thanh cong!\n";
                    releasebmp24(src24);
                    releasebmp8(dst);
                }
                else {
                    cout << "Ghi file that bai!";
                }
            }

            if (global.dib.bpp == 32) {
                if (read32(path_in, src32)) {           
                    cout << "Doc file 32 thanh cong!\n";
                }
                else
                    cout << "Doc file that bai!\n";

                if (convert32to8bit(src32, dst)) {        
                    cout << "Chuyen bit thanh cong!\n";
                }
                else
                    cout << "Chuyen bit that bai\n";


                if (write8(path_out, dst)) {    
                    cout << "Ghi file thanh cong!\n";
                    releasebmp32(src32);
                    releasebmp8(dst);
                }
                else
                    cout << "Ghi file that bai!";
            }

            if (global.dib.bpp != 24 && global.dib.bpp != 32) {
                cout << "File bmp co bit per pixel khong hop le.\n";
                cout << "Vui long chon file bmp co bit per pixel bang 24/32.\n";
            }
        }
        if (selection == 2) {

            readglobal(path_in, global);

            int s;
            cout << "Nhap ti le s : ";
            cin >> s;
            bmp8 zoom8;
            bmp24 zoom24;
            bmp32 zoom32;


            if (global.dib.bpp == 8) {
                if (read8(path_in, src8)) {           
                    cout << "Doc file 8 thanh cong!\n";
                }
                else
                    cout << "Doc file that bai!\n";

                if (resize8(src8, zoom8, s)) {  
                    cout << "resize 8 thanh cong\n ";
                    write8(path_out, zoom8);
                    releasebmp8(src8);
                    releasebmp8(zoom8);
                }
                else {
                    cout << "ghi file that bai!\n";
                }
            }

            if (global.dib.bpp == 24) {

                if (read24(path_in, src24)) {           
                    cout << "Doc file 8 thanh cong!\n";
                }

                if (resize24(src24, zoom24, s)) {    
                    cout << "resize 24 thanh cong \n";
                    write24(path_out, zoom24);
                    releasebmp24(src24);
                    releasebmp24(zoom24);
                }
                else {
                    cout << "ghi file that bai!\n";
                }
            }

            if (global.dib.bpp == 32) {

                if (read32(path_in, src32)) {         
                    cout << "Doc file 32 thanh cong!\n";
                }

                if (resize32(src32, zoom32, s)) {    
                    cout << "resize 32 thanh cong\n ";
                    write32(path_out, zoom32);
                    releasebmp32(src32);
                    releasebmp32(zoom32);
                }
                else {
                    cout << "ghi file that bai!\n";
                }
            }

            if (global.dib.bpp != 24 && global.dib.bpp != 32 && global.dib.bpp != 8) {
                cout << "File bmp co bit per pixel khong hop le.\n";
                cout << "Vui long chon file bmp co bit per pixel bang 8/24/32.\n";
            }

        }
    }

    if (argc == 4) {

        if (strcmp(argv[1], "-conv") != 0) {
            cout << "Lenh Nhap Vao Khong Hop Le !\n";
            cout << "Cau truc cau lenh: 20120219.exe -conv <Input Path> <Output Path>\n";
            return 0;
        }

        readglobal(argv[2], global);

        if (global.dib.bpp == 24) {
            if (read24(argv[2], src24)) {
                cout << "Doc file 24 thanh cong!\n";
            }
            else
                cout << "Doc file 24 that bai!\n";

            if (convert24to8bit(src24, dst)) {        
                cout << "Chuyen bit thanh cong!\n";
            }
            else
                cout << "Chuyen bit that bai\n";

            if (write8(argv[3], dst)) {  
                cout << "Ghi file 8 thanh cong!\n";
            }
            else {
                cout << "Ghi file 8 that bai!\n";
            }
        }

        if (global.dib.bpp == 32) {
            if (read32(argv[2], src32)) {           
                cout << "Doc file 32 thanh cong!\n";
            }
            else
                cout << "Doc file 32 that bai!\n";

            if (convert32to8bit(src32, dst)) {       
                cout << "Chuyen bit thanh cong!\n";
            }
            else
                cout << "Chuyen bit that bai\n";


            if (write8(argv[3], dst)) {    
                cout << "Ghi file 8 thanh cong!\n";
            }
            else
                cout << "Ghi file 8 that bai!\n";
        }

        if (global.dib.bpp != 24 && global.dib.bpp != 32) {
            cout << "File bmp co bit per pixel khong hop le.\n";
            cout << "Vui long chon file bmp co bit per pixel bang 24/32.\n";
        }
    }

    if (argc == 5) {
        if (strcmp(argv[1], "-zoom") != 0) {
            cout << "Lenh Nhap Vao Khong Hop Le !\n";
            cout << "Cau truc cau lenh: 20120219.exe -zoom <Input Path> <Output Path> S\n";
            return 0;
        }

        readglobal(argv[2], global);

        bmp8 zoom8;
        bmp24 zoom24;
        bmp32 zoom32;


        if (global.dib.bpp == 8) {
            if (read8(argv[2], src8)) {        
                cout << "Doc file 8 thanh cong!\n";
            }
            else
                cout << "Doc file that bai!\n";

            if (resize8(src8, zoom8, atoi(argv[4]))) {  
                cout << "resize 8 thanh cong\n ";
                write8(argv[3], zoom8);
            }
            else {
                cout << "ghi file 8 that bai! \n";
            }
        }
        if (global.dib.bpp == 24) {

            if (read24(argv[2], src24)) {           
                cout << "Doc file 24 thanh cong!\n";
            }

            if (resize24(src24, zoom24, atoi(argv[4]))) {  
                cout << "resize 24 thanh cong \n" ;
                write24(argv[3], zoom24);
            }
            else {
                cout << "ghi file 24 that bai!";
            }
        }

        if (global.dib.bpp == 32) {

            if (read32(argv[2], src32)) {            
                cout << "Doc file 32 thanh cong!\n";
            }

            if (resize32(src32, zoom32, atoi(argv[4]))) {    
                cout << "resize 32 thanh cong " << endl;
                write32(argv[3], zoom32);
            }
            else {
                cout << "ghi file 32 that bai!";
            }
        }
        
        if (global.dib.bpp != 24 && global.dib.bpp != 32 && global.dib.bpp != 8) {
            cout << "File bmp co bit per pixel khong hop le.\n";
            cout << "Vui long chon file bmp co bit per pixel bang 8/24/32.\n";
        }

    }

    return 1;
  
}