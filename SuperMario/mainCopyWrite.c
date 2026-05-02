#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define mapHeight 80
#define mapWidth 80

typedef struct SObject{
    float x, y;
    float width, hight; 
} TObject;

char map[mapHeight][mapWidth+1];
TObject mario;

void Clearmap(){
    for (int i = 0; i < mapWidth; i++)
        map[0][i] = '.';
    map[0][mapWidth] = '\0';
    for (int j = 1; j < mapHeight; j++)
        sprintf(map[j], map[0]);
}

void ShowMap(){
    map[mapHeight - 1][mapWidth - 1] = '\0';
    for (int j = 0; j < mapHeight; j++)
        printf(map[j], map[0]);
}


void SetObjectPos(TObject *obj, float xPos, float yPos){

    (*obj).x = xPos;
    (*obj).y = yPos;

}
void InitObject(TObject *obj, float xPos, float yPos, float oWidth, float oHight){

    SetObjectPos(obj, oWidth, oHight);
    (*obj).width = oWidth;
    (*obj).hight = oHight;

}



void PutObjectOnMap(TObject obj){
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iWidth = (int)round(obj.width);
    int iHight = (int)round(obj.hight);

    for (int i = ix; i < (ix + iWidth); i++)
        for (int j = iy; j < (iy + iHight); j++)
            map[j][i] = '0';


}

int main(){
    
    InitObject(&mario, 39,10,3,3);
    Clearmap();
    PutObjectOnMap(mario);
    ShowMap();

    return 0;
}