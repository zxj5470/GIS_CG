# GIS CG 计算机图形学
All functions are in class MyCDC.h/MyCDC.cpp
````
class MyCDC 
````

##
- Alloc Console in MFC
````
    //add console to "debug"
    // 开辟控制台
    AllocConsole();                          
    SetConsoleTitle(_T("Debug Title"));
    // 设置控制台窗口标题
    FILE* pf;
    freopen_s(&pf, "CONOUT$", "w", stdout);
````
- point to line in CG_algorithms.h
````
/**
* 向量法计算
* @param x,y 点C
* @param xa,ya 点A坐标
* @param xb,yb 点B坐标
* @return distance from point C to line AB
*/
    double distanceVector(double x, double y, double xa, double ya, double xb, double yb);
````