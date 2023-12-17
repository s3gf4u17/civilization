#define STB_IMAGE_IMPLEMENTATION
#include "../library/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../library/stb_image_write.h"
#include <cstdlib>
#include <time.h>

// enum LAND_MASS {SMALL,NORMAL,LARGE};
// enum TEMPERATURE {COOL,NORMAL,WARM};
// enum CLIMATE {ARID,NORMAL,WET};
// enum AGE {OLD,NORMAL,YOUNG};

int width=80,height=50,channels=3;

int main() {
    int map[width*height] = {0};
    srand(time(0));
    bool sufficient_landmass = false;

    while (!sufficient_landmass) {
        int rspx = std::rand()%70+4; // random starting position x
        int rspy = std::rand()%35+8; // random starting position y
        int pl = std::rand()%63+1; // path length
        map[rspy*width+rspx] = 15;
        map[rspy*width+rspx+1] = 15;
        map[(rspy+1)*width+rspx] = 15;
        map[rspy*width+rspx-1] = 15;
        map[(rspy-1)*width+rspx] = 15;
        while (pl>0) {
            int nptp = std::rand()%4; // next position to paint;
            switch (nptp) {
                case 0: {rspy-=1; break;}
                case 1: {rspx+=1; break;}
                case 2: {rspy+=1; break;}
                case 3: {rspx-=1; break;}
            };
            if (rspx<3||rspy<3||rspx>76||rspy>45) break;
            map[rspy*width+rspx] = 15;
            map[rspy*width+rspx+1] = 15;
            map[(rspy+1)*width+rspx] = 15;
            map[rspy*width+rspx-1] = 15;
            map[(rspy-1)*width+rspx] = 15;
            pl--;
        }
        int landmass = 0;
        for (int i : map) {
            if (i==15) landmass++;
            if (landmass>1280) sufficient_landmass = true;
        }
    }

    unsigned char *img = new unsigned char[width*height*channels];
    for (int i = 0 ; i < width*height ; i++) {
        switch (map[i]) {
            case 15:
                img[i*channels]=0;
                img[i*channels+1]=255;
                img[i*channels+2]=0;
                break;
            default:
                img[i*channels]=0;
                img[i*channels+1]=0;
                img[i*channels+2]=255;
        }
    }
    stbi_write_png("map.png",width,height,channels,img,width*channels);
    return 0;
}