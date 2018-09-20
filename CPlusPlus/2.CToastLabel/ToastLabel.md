微调自网传代码: [toastLabel](https://github.com/Greedysky/TTKWidgetTools/tree/master/Label/toastLabel)

使用例子:
``` C++
#include "CToastLabel.h"

CToastLabel* pToast = new CToastLabel("Test");
pToast->popup(this);
```

效果如图:  
![](https://github.com/Greedysky/TTKWidgetTools/raw/master/Label/toastLabel/res/demo.gif?raw=true)


原理为:  
1. 设置时间自动关闭窗口
2. 窗口显示和关闭时, 使用动画效果
3. 设置窗口的边框
