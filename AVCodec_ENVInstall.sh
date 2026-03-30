#!/bin/bash
clear
m_EnvRelease=0
#检查

function InstallEnv_CheckSystem()
{
	echo -e "\033[94m 检测系统环境...\033[0m"

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
	echo -e "\033[94m系统环境为:${m_EnvCurrent}...\033[0m"
}
#安装框架
function InstallEnv_XEngine()
{
	echo -e "\033[94m安装环境框架...\033[0m"
	cd XEngine_Package

	if [ "$m_EnvRelease" -eq "1" ] ; then
		rm -rf ./XEngine_RockyLinux_10_x86-64
		unzip ./XEngine_RockyLinux_10_x86-64.zip -d ./XEngine_RockyLinux_10_x86-64
		cd ./XEngine_RockyLinux_10_x86-64

		chmod 777 ./XEngine_LINEnv.sh
		./XEngine_LINEnv.sh -b -i 6
		./XEngine_LINEnv.sh -i 3
	elif [ "$m_EnvRelease" -eq "2" ] ; then 
		rm -rf ./XEngine_UBuntu_24.04_x86-64
		unzip ./XEngine_UBuntu_24.04_x86-64.zip -d ./XEngine_UBuntu_24.04_x86-64
		cd ./XEngine_UBuntu_24.04_x86-64

		chmod 777 ./XEngine_LINEnv.sh
		./XEngine_LINEnv.sh -b -i 6
		./XEngine_LINEnv.sh -i 3
	elif [ "$m_EnvRelease" -eq "3" ] ; then 
		rm -rf ./XEngine_Mac_Arm64
		unzip ./XEngine_Mac_Arm64.zip -d ./XEngine_Mac_Arm64
		cd ./XEngine_Mac_Arm64

		chmod 777 ./XEngine_LINEnv.sh
		 ./XEngine_LINEnv.sh -i 0
		sudo mkdir -p /usr/local/include
  		sudo mkdir -p /usr/local/lib
  		sudo cp -rf ./XEngine_Include /usr/local/include
  		sudo find ./XEngine_Mac -name "*.dylib" -exec cp {} /usr/local/lib \;
	else 
		echo -e "not support"
	fi
	
    cd ..
}
#安装tsduck
function InstallEnv_Execution()
{
	echo -e "\033[94m安装运行环境完毕。。。done...\033[0m"
	if [ "$m_EnvRelease" -eq "1" ] ; then
		dnf remove sdl2-compat -y
		dnf install SDL2-devel opencv-devel ffmpeg-devel --allowerasing -y
		dnf install ./tsduck-el10.x86_64.rpm ./tsduck-devel-el10.x86_64.rpm -y
	elif [ "$m_EnvRelease" -eq "2" ] ; then 
		apt install libopencv-dev libsdl2-dev -y
    	dpkg -i ./tsduck.ubuntu24_amd64.deb ./tsduck-dev.ubuntu24_amd64.deb
    	apt -f install -y
	elif [ "$m_EnvRelease" -eq "3" ] ; then 
		brew install openssl@3 opencv sdl2 tsduck
	else
		echo -e "not support"
	fi
}

InstallEnv_CheckSystem
InstallEnv_XEngine
InstallEnv_Execution

echo -e "\033[92m安装运行环境完毕。。。done...\033[0m"
