#include "head.h"

bool find_tg(float a, float b, float c, double *res){
    if(a+b<c || b+c<a || c+a<b){
        res[0] = 0;
        res[1] = 0;
        res[2] = 0;
        cout<<"Not triangle..";
        return 0;
    }
    else{
        double cos, sin;
        cos = (pow(c,2)+pow(b,2)-pow(a,2))/(2*c*b);
        sin = sqrt(1-pow(cos,2));
        res[0] = (sin/cos);
        cos = (pow(c,2)+pow(a,2)-pow(b,2))/(2*c*a);
        sin = sqrt(1-pow(cos,2));
        res[1] = (sin/cos);
        cos = (pow(a,2)+pow(b,2)-pow(c,2))/(2*a*b);
        sin = sqrt(1-pow(cos,2));
        res[2] = (sin/cos);
        return 1;
    }
}
