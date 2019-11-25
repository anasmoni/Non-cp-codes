#include<bits/stdc++.h>

#define pi (2*acos(0.0))
using namespace std;


double eyeX, eyeY,eyeZ; //in Line 1
double lookX,lookY,lookZ; //in Line 2
double upX, upY, upZ ;//in Line 3
//Line 4
double fovY; //field of view along Y axis
double aspectRatio;// aspect ratio indicating the ratio between the field of view along X and the field of view along Y axis
double near; //near distance
double far ; //far distance

ifstream in;
ofstream out;

struct point
{
    double x,y,z,w;
    point(double xx, double yy, double zz, double ww=1)
    {
        x = xx;
        y = yy;
        z = zz;
        w = ww;
    }
    point()
    {
        x = y = z = 0.0;
        w=1;
    }
};
struct Matrix
{
    double m[4][4];
    Matrix()  // default identity matrix
    {
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
                m[i][j] = 0;
            m[i][i] = 1;
        }
    }
} I; // identity matrix

stack<Matrix>S;

point CrossProduct(point a, point b)
{
    point c;
    c.x = a.y*b.z - a.z*b.y;
    c.y = a.z*b.x - a.x*b.z;
    c.z = a.x*b.y - a.y*b.x;
    return c;
}

double DotProduct(point a, point b)
{
    double ret;
    ret = a.x*b.x + a.y*b.y + a.z*b.z;
    return ret;
}

point AddPoint(point a, point b)
{
    point ret = point(a.x+b.x, a.y+b.y, a.z+b.z);
    return ret;
}

point MulPoint(point a, double m)
{
    point ret = point(a.x*m, a.y*m, a.z*m);
    return ret;
}

double Radian(double deg)
{
    deg = (deg*pi)/180.0;
    return deg;
}

point Normalize(point a)
{
    double m = a.x*a.x + a.y*a.y + a.z*a.z;
    m = sqrt(m);
    if(m>0)
    {
        a.x /= m;
        a.y /= m;
        a.z /= m;
    }
    return a;
}

point R(point x, point a, double angle)    /// rotate I with respect to a by angle degree
{

    angle = Radian(angle);

    point ret = AddPoint( MulPoint(CrossProduct(a,x),sin(angle)), MulPoint(x,cos(angle)));

    double temp = (1-cos(angle)) * DotProduct(a,x);

    ret = AddPoint(ret, MulPoint(a,temp));

    return ret;
}

void printMatrix(Matrix M){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++) cout<<M.m[i][j]<<" ";
        cout<<endl;
    }
}

point FixW(point a)
{

    if(a.w == 0 || a.w==1)
        return a;

    a.x /= a.w;
    a.y /= a.w;
    a.z /= a.w;
    a.w = 1;

    return a;
}

Matrix TranslationMatrix(double tx,double ty,double tz)
{
    Matrix ret;

    ret.m[0][3] = tx;
    ret.m[1][3] = ty;
    ret.m[2][3] = tz;

    return ret;
}

Matrix MulMatrix(Matrix M1, Matrix M2)
{
    Matrix ret;

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            double sum = 0;

            for(int k=0; k<4; k++)
            {
                sum += M1.m[i][k]*M2.m[k][j];
            }

            ret.m[i][j] = sum;
        }
    }

    return ret;
}

Matrix RotationMatrix(double angle, double ax,double ay, double az)
{
    Matrix ret;
    point a(ax,ay,az);
    a = Normalize(a);

    point c[3];
    c[0] = R(point(1,0,0),a,angle);
    c[1] = R(point(0,1,0),a,angle);
    c[2] = R(point(0,0,1),a,angle);

    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {

            if(i==0 )
                ret.m[i][j] = c[j].x;
            if(i==1 )
                ret.m[i][j] = c[j].y;
            if(i==2 )
                ret.m[i][j] = c[j].z;
        }
    }

    return ret;
}
Matrix ScalingMatrix(double sx, double sy, double sz)
{
    Matrix ret;

    ret.m[0][0] = sx;
    ret.m[1][1] = sy;
    ret.m[2][2] = sz;

    return ret;
}

double GetByPos(point a, int pos)
{

    if(pos == 0)
        return a.x;
    if(pos == 1)
        return a.y;
    if(pos == 2)
        return a.z;
    if(pos == 3)
        return a.w;
    return 0;
}

point TransformPoint(Matrix M,point p)
{
    point ret ;

    for(int j=0; j<4; j++)
    {
        double sum = 0;

        for(int i=0; i<4; i++)
        {
            sum += M.m[j][i]*GetByPos(p,i);
        }
        if(j == 0)
            ret.x = sum;
        if(j == 1)
            ret.y = sum;
        if(j == 2)
            ret.z = sum;
        if(j == 3)
            ret.w = sum;
    }

    return FixW(ret);
}

void stage1()
{

    S.push(I);
    string command;
    out.open("stage1.txt");

    while(true)
    {
        in>>command;

        if(S.size() == 0)
            S.push(I);

        if(command == "triangle")
        {

            point p[3];

            for(int i=0; i<3; i++)
                in>>p[i].x>>p[i].y>>p[i].z;

            for(int i=0; i<3; i++)
            {
                point pp = TransformPoint(S.top(),p[i]);
                out<<pp.x<<" "<<pp.y<<" "<<pp.z<<endl;
            }
            out<<endl<<endl;
        }
        else if (command == "translate")
        {
            double tx,ty,tz;
            in>>tx>>ty>>tz;

            Matrix T = TranslationMatrix(tx,ty,tz);
           // S.push(MulMatrix(S.top(),T));

            Matrix newM = MulMatrix(S.top(),T);
            S.pop();
            //printMatrix(newM);
            S.push(newM);

        }
        else if(command == "scale")
        {
            double sx,sy,sz;
            in>>sx>>sy>>sz;

            Matrix SM = ScalingMatrix(sx,sy,sz);
            //S.push(MulMatrix(S.top(),SM));
            Matrix newM = MulMatrix(S.top(),SM);
            S.pop();
            S.push(newM);
        }
        else if(command == "rotate")
        {

            double angle, ax,ay,az;
            in>>angle>>ax>>ay>>az;

            Matrix RM = RotationMatrix(angle,ax,ay,az);
            //S.push(MulMatrix(S.top(),RM));
            Matrix newM = MulMatrix(S.top(),RM);
            S.pop();
            S.push(newM);
        }
        else if(command == "push")
        {
            S.push(S.top());
        }
        else if(command == "pop")
        {
            S.pop();
        }
        else if(command == "end")
        {
            break;
        }
    }
}

void stage2(){

    point l,r,u;
    l = AddPoint(point(lookX,lookY,lookZ) , MulPoint(point(eyeX,eyeY,eyeZ),-1) );
    l = Normalize(l);
    r = CrossProduct(l,point(upX,upY,upZ));
    r = Normalize(r);
    u = CrossProduct(r,l);

    in.open("stage1.txt");
    out.open("stage2.txt");

    Matrix T , R;

    T.m[0][3] = -eyeX;
    T.m[1][3] = -eyeY;
    T.m[2][3] = -eyeZ;

    R.m[0][0] = r.x;
    R.m[0][1] = r.y;
    R.m[0][2] = r.z;

    R.m[1][0] = u.x;
    R.m[1][1] = u.y;
    R.m[1][2] = u.z;

    R.m[2][0] = -l.x;
    R.m[2][1] = -l.y;
    R.m[2][2] = -l.z;

    Matrix V = MulMatrix(R,T);

    point p[3];

    while(in>>p[0].x>>p[0].y>>p[0].z){

        for(int i=1; i<=2; i++) in>>p[i].x>>p[i].y>>p[i].z;

        for(int i=0; i<3; i++){
            point pp = TransformPoint(V,p[i]);
            out<<pp.x<<" "<<pp.y<<" "<<pp.z<<endl;
        }
        out<<endl;
    }

}

void stage3(){

    in.open("stage2.txt");
    out.open("stage3.txt");

    double fovX = fovY * aspectRatio;
    double t = near * tan(Radian(fovY/2.0));
    double r = near * tan(Radian(fovX/2));

    Matrix P;

    P.m[0][0] = near/r;
    P.m[1][1] = near/t;
    P.m[2][2] = -(far+near)/(far-near);
    P.m[2][3] = -(2*far*near)/(far-near);
    P.m[3][2] = -1;
    P.m[3][3] = 0;

    point p[3];

    while(in>>p[0].x>>p[0].y>>p[0].z){

        for(int i=1; i<=2; i++) in>>p[i].x>>p[i].y>>p[i].z;

        for(int i=0; i<3; i++){
            point pp = TransformPoint(P,p[i]);
            out<<pp.x<<" "<<pp.y<<" "<<pp.z<<endl;
        }
        out<<endl;
    }
}

void closeAll(){
    in.close();
    out.close();
}

void init()
{

    out<<setprecision(7)<<fixed;

    in.open("scene.txt");

    in>>eyeX>>eyeY>>eyeZ;
    in>>lookX>>lookY>>lookZ;
    in>>upX>>upY>>upZ;
    in>>fovY>>aspectRatio>>near>>far;
}

int main()
{

    init();

    stage1();

    closeAll();

    stage2();

    closeAll();

    stage3();

    closeAll();

    return 0;
}

