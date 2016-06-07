#ifndef Action_H
#define Action_H

struct Action {
    int surface;
    bool isSide;
    bool cw;
public:
    Action(int surface = -1, bool cw = true, bool isSide = true) {
        this->surface = surface;
        this->isSide = isSide;
        this->cw = cw;
    }
};

//前后->左右
//上下->前后
//左右->上下
static Action ACTIONS[6][9]{
        {Action(3,false),Action(1,true,false),Action(1),Action(5,true,false),Action(),Action(4,true,false),Action(3),Action(3,true,false),Action(1,false)},
        {Action(5),Action(2,true,false),Action(5,false),Action(5,true,false),Action(),Action(4,true,false),Action(4,false),Action(0,true,false),Action(4)},
        {Action(1,false),Action(3,true,false),Action(3),Action(5,true,false),Action(),Action(4,true,false),Action(1),Action(1,true,false),Action(3,false)},
        {Action(5),Action(0,true,false),Action(5,false),Action(5,true,false),Action(),Action(4,true,false),Action(4,false),Action(2,true,false),Action(4)},
        {Action(0),Action(1,true,false),Action(0,false),Action(0,true,false),Action(),Action(2,true,false),Action(2,false),Action(3,true,false),Action(2)},
        {Action(2),Action(1,true,false),Action(2,false),Action(2,true,false),Action(),Action(0,true,false),Action(0,false),Action(3,true,false),Action(0)},
};

#endif //Action_H
