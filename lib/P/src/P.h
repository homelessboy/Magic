//
// Created by java-xuhui on 2016/3/31.
//

#ifndef P_H
#define P_H

struct P {
    int face;
    int x;
    int y;
public:
    P(int face, int y, int x) {
        this->face = face;
        this->y = y;
        this->x = x;
    }
    P(int index=0){
        this->face=index/9;
        this->y=(index%9)/3;
        this->x=(index%9)%3;
    }
    int getIndex() const {
        return face * 9 + y * 3 + x;
    }
};

static P CIRCLE[6][12]={
        {P(3, 2, 2), P(3, 1, 2), P(3, 0, 2), P(5, 2, 0), P(5, 2, 1), P(5, 2, 2), P(1, 0, 0), P(1, 1, 0), P(1, 2, 0), P(4, 0, 2), P(4, 0, 1), P(4, 0, 0)},
        {P(0, 2, 2), P(0, 1, 2), P(0, 0, 2), P(5, 2, 2), P(5, 1, 2), P(5, 0, 2), P(2, 0, 0), P(2, 1, 0), P(2, 2, 0), P(4, 2, 2), P(4, 1, 2), P(4, 0, 2)},
        {P(1, 2, 2), P(1, 1, 2), P(1, 0, 2), P(5, 0, 2), P(5, 0, 1), P(5, 0, 0), P(3, 0, 0), P(3, 1, 0), P(3, 2, 0), P(4, 2, 0), P(4, 2, 1), P(4, 2, 2)},
        {P(2, 2, 2), P(2, 1, 2), P(2, 0, 2), P(5, 0, 0), P(5, 1, 0), P(5, 2, 0), P(0, 0, 0), P(0, 1, 0), P(0, 2, 0), P(4, 0, 0), P(4, 1, 0), P(4, 2, 0)},
        {P(0, 2, 0), P(0, 2, 1), P(0, 2, 2), P(1, 2, 0), P(1, 2, 1), P(1, 2, 2), P(2, 2, 0), P(2, 2, 1), P(2, 2, 2), P(3, 2, 0), P(3, 2, 1), P(3, 2, 2)},
        {P(0, 0, 2), P(0, 0, 1), P(0, 0, 0), P(3, 0, 2), P(3, 0, 1), P(3, 0, 0), P(2, 0, 2), P(2, 0, 1), P(2, 0, 0), P(1, 0, 2), P(1, 0, 1), P(1, 0, 0)},
};

static P SURFACE[6][8]={
        {P(0,0,0),P(0,0,1),P(0,0,2),P(0,1,2),P(0,2,2),P(0,2,1),P(0,2,0),P(0,1,0)},
        {P(1,0,0),P(1,0,1),P(1,0,2),P(1,1,2),P(1,2,2),P(1,2,1),P(1,2,0),P(1,1,0)},
        {P(2,0,0),P(2,0,1),P(2,0,2),P(2,1,2),P(2,2,2),P(2,2,1),P(2,2,0),P(2,1,0)},
        {P(3,0,0),P(3,0,1),P(3,0,2),P(3,1,2),P(3,2,2),P(3,2,1),P(3,2,0),P(3,1,0)},
        {P(4,0,0),P(4,0,1),P(4,0,2),P(4,1,2),P(4,2,2),P(4,2,1),P(4,2,0),P(4,1,0)},
        {P(5,0,0),P(5,0,1),P(5,0,2),P(5,1,2),P(5,2,2),P(5,2,1),P(5,2,0),P(5,1,0)}
};

static P MIDDLE[6][12]={
        {P(3,2,1),P(3,1,1),P(3,0,1),P(5,1,0),P(5,1,1),P(5,1,2),P(1,0,1),P(1,1,1),P(1,2,1),P(4,1,2),P(4,1,1),P(4,1,0)},//正对0面中心层顺时针
        {P(0,2,1),P(0,1,1),P(0,0,1),P(5,2,1),P(5,1,1),P(5,0,1),P(2,0,1),P(2,1,1),P(2,2,1),P(4,2,1),P(4,1,1),P(4,0,1)},//正对1面中心层顺时针
        {P(4,1,0),P(4,1,1),P(4,1,2),P(1,2,1),P(1,1,1),P(1,0,1),P(5,1,2),P(5,1,1),P(5,1,0),P(3,0,1),P(3,1,1),P(3,2,1)},//正对2面中心层顺时针
        {P(4,0,1),P(4,1,1),P(4,2,1),P(2,2,1),P(2,1,1),P(2,0,1),P(5,0,1),P(5,1,1),P(5,2,1),P(0,0,1),P(0,1,1),P(0,2,1)},//正对3面中心层顺时针
        {P(0,1,0),P(0,1,1),P(0,1,2),P(1,1,0),P(1,1,1),P(1,1,2),P(2,1,0),P(2,1,1),P(2,1,2),P(3,1,0),P(3,1,1),P(3,1,2)},//正对4面中心层顺时针
        {P(3,1,2),P(3,1,1),P(3,1,0),P(2,1,2),P(2,1,1),P(2,1,0),P(1,1,2),P(1,1,1),P(1,1,0),P(0,1,2),P(0,1,1),P(0,1,0)},//正对5面中心层顺时针
};

static int LEFT[6]={3,0,1,2,3,3};
static int RIGHT[6]={1,2,3,0,1,1};
static int UP[6]={5,5,5,5,0,2};
static int DOWN[6]={4,4,4,4,2,0};
static int BACK[6]={2,3,0,1,5,4};

#endif //P_H
