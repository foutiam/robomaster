###  1    Shell

src/1/find.sh

 	time find ./ -name "*.c" -o -name "*.h" -type f | xargs grep hello -n

in terminal
	
 	cd src/1/
	chmod a+x find.sh


###  2    识别苹果

步骤：

 	1. 通过HSV颜色提取对图像二值化
 	2. 通过滤波对二值化图像进行处理
 	3. 找出轮廓并筛选
 	4. 画图


###  3    识别小弹丸

步骤：

	1. 二值化筛选出运动中的小弹丸
	2. 找出最大的标定为当前帧存在的弹道
	3. 用旋转外接矩形标识小弹丸
	4. 用旋转外接矩形的中心标记出当前帧弹道中点


lcy大佬好可怕ヽ(*。>Д<)o゜












