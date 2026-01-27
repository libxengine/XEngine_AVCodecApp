#!/bin/bash
clear
m_EnvRelease=0
#检查
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
function InstallEnv_CheckSystem()
{
	if [ $(uname) == "Linux" ] ; then
		if [ -f /etc/redhat-release ]; then
			if grep -Eq "CentOS" /etc/redhat-release; then
				m_EnvRelease=1
				m_EnvCurrent=$(cat /etc/redhat-release)
			elif grep -Eq "Rocky Linux" /etc/redhat-release; then
				m_EnvRelease=1
				m_EnvCurrent=$(cat /etc/redhat-release)
			elif grep -Eq "Red Hat Enterprise Linux Server" /etc/redhat-release; then
				m_EnvRelease=1
				m_EnvCurrent=$(cat /etc/redhat-release)
			else
        		echo -e "不支持的发行版本，无法继续"
				exit
			fi
		elif [ -f /etc/os-release ]; then
			SystemID=$(grep "^ID=" /etc/os-release | cut -d '=' -f 2 | tr -d '"')
			if [ "$SystemID" = "ubuntu" ]; then
				m_EnvRelease=2
				m_EnvCurrent=$(grep "VERSION=" /etc/os-release | cut -d '"' -f 2)
			else
        		echo -e "不支持的发行版本，无法继续"
				exit
			fi
		fi
	elif [ $(uname) == "Darwin" ] ; then
		m_EnvRelease=3
		m_EnvCurrent=$(sw_vers)
	else
		echo -e "不支持的发行版本，无法继续"
		exit
	fi
}
#安装框架
function InstallEnv_XEngine()
{
	cd XEngine_Package

	if [ "$m_EnvRelease" -eq "1" ] ; then
		rm -rf ./XEngine_RockyLinux_10_x86-64
		unzip ./XEngine_RockyLinux_10_x86-64.zip -d ./XEngine_RockyLinux_10_x86-64
		cd ./XEngine_RockyLinux_10_x86-64
	elif [ "$m_EnvRelease" -eq "2" ] ; then 
		rm -rf ./XEngine_UBuntu_24.04_x86-64
		unzip ./XEngine_UBuntu_24.04_x86-64.zip -d ./XEngine_UBuntu_24.04_x86-64
		cd ./XEngine_UBuntu_24.04_x86-64
	elif [ "$m_EnvRelease" -eq "3" ] ; then 
		echo -e "not support"
	else 
		echo -e "not support"
	fi
	
	chmod 777 ./XEngine_LINEnv.sh
	./XEngine_LINEnv.sh -b -i 6
	./XEngine_LINEnv.sh -i 3
    cd ..
}
#安装tsduck
function InstallEnv_Execution()
{
	if [ "$m_EnvRelease" -eq "1" ] ; then
		dnf remove sdl2-compat -y
		dnf install SDL2-devel opencv-devel ffmpeg-devel --allowerasing -y
		dnf install ./tsduck-el10.x86_64.rpm ./tsduck-devel-el10.x86_64.rpm -y
	elif [ "$m_EnvRelease" -eq "2" ] ; then 
		apt install libopencv-dev libsdl2-dev -y
    	dpkg -i ./tsduck.ubuntu24_amd64.deb ./tsduck-dev.ubuntu24_amd64.deb
    	apt -f install -y
	elif [ "$m_EnvRelease" -eq "3" ] ; then 
		echo -e "not support"
	else
		echo -e "not support"
	fi
}

InstallEnv_CheckRoot
InstallEnv_CheckSystem
InstallEnv_XEngine
InstallEnv_Execution

echo -e "\033[92m安装运行环境完毕。。。done...\033[0m"
