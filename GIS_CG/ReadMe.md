﻿# GIS CG 计算机图形学
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