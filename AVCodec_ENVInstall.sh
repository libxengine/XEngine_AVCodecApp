#!/bin/bash
clear
#权限检查
function InstallEnv_CheckRoot()
{
	echo -e "\033[34m检查你的执行权限中。。。\033[0m"
 	ROOT_UID=0
	if [ "$UID" -eq "$ROOT_UID" ] ; then
		echo -e "\033[32m检查到是ROOT权限执行，继续执行下一步。。。\033[0m"
	else
		echo -e "\033[31m检查到你不是ROOT权限，请切换到ROOT权限执行。。。 \033[0m"
		exit 0
	fi
}
#安装框架
function InstallEnv_XEngine()
{
	cd XEngine_Package
	rm -rf ./XEngine_UBuntu_24.04_x86-64
	unzip ./XEngine_UBuntu_24.04_x86-64.zip -d ./XEngine_UBuntu_24.04_x86-64
	cd ./XEngine_UBuntu_24.04_x86-64
	chmod 777 ./XEngine_LINEnv.sh
	./XEngine_LINEnv.sh -b -i 6
	./XEngine_LINEnv.sh -i 3
    cd ..
}
#安装tsduck
function InstallEnv_Execution()
{
	apt install libopencv-dev libsdl2-dev -y
	 # 不管有没有安装过，都执行 -i（dpkg 会自动覆盖旧版本）
    dpkg -i ./tsduck.ubuntu24_amd64.deb ./tsduck-dev.ubuntu24_amd64.deb
    # 如果依赖未满足，自动修复
    apt -f install -y
}

InstallEnv_CheckRoot
InstallEnv_XEngine
InstallEnv_Execution

echo -e "\033[92m安装运行环境完毕。。。done...\033[0m"
