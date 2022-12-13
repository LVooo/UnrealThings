# UnrealThings
## *ActionRouguelike开发日记（C++）*
&nbsp;
## **12.11** VisualStudio配置；新建character类
此处我下载的是Visual Studio 2019对应UE 4.27版本，需要勾选使用C++的游戏开发中的任一SDK，Unreal Engine安装程序；在之后运行时报错我又修改了单个组件中的.Net Framework为4.7.2 SDK版本。<br>
**Unreal代码提示**：下载Visual Assist插件

**为人物新建第三人称摄像头**<br>
新建对应摄像头的Component类，这里新建了两个摄像头，**SpringArmCom是为了控制与物体的collision**，当摄像头与物体碰撞时会使摄像头产生碰撞跟随移动。使用UE的UPPROERTY来expose蓝图中的细节。
```cpp
UPROPERTY(VisibleAnywhere)
USpringArmComponent* SpringArmComp;

UPROPERTY(VisibleAnywhere)
UCameraComponent* CameraComp;
```
直接include头文件的话会导致加载过慢，所以在private文件中创建对象，每次调用的时候才会用到，并用指针将摄像头绑定在固定位置。
```cpp
SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
SpringArmComp->SetupAttachment(RootComponent);

CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
CameraComp->SetupAttachment(SpringArmComp);
```

## **12.13** 控制角色和摄像头旋转
```cpp
// X = Forward (Red)
// Y = Right (Green)
// Z = Up（Blue） 
```
用springCamera来控制，设置角色会朝着镜头指向方向进行移动和旋转，同时在前后和左右移动时设置pitch和roll值为0以保证只在水平方向进行移动。