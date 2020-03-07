#include "../lib/progressbar.h"
#ifdef _WIN32
#include "Windows.h"
#else
#include "unistd.h"
#endif

int main(int argc, char const *argv[])
{
	// 设置循环长度
	int loop_size = 200;

	// 声明一个进度条 同时设置其长度与名称
	ProgressBar bar1(loop_size,"bar1");
	// 在循环中更新进度条 使用usleep函数放缓循环间隔至0.1秒
	for (int i = 0; i < loop_size; i++)
	{
		bar1.Progressed(i);
		usleep(1e+5);
	}

	// 声明第二个进度条 并设置更新间隔为10次 即大约每10%更新一次进度条
	ProgressBar bar2(loop_size,"bar2");
	bar2.SetFrequencyUpdate(10);
	// 查看第二个进度条
	for (int i = 0; i < loop_size; i++)
	{
		bar2.Progressed(i);
		usleep(1e+5);
	}

	// 声明第三个进度条 并设置已完成进度条符号为> 未完成进度条符号为空格
	ProgressBar bar3(loop_size,"bar3");
	bar3.SetStyle(">"," ");
	// 查看第三个进度条
	for (int i = 0; i < loop_size; i++)
	{
		bar3.Progressed(i);
		usleep(1e+5);
	}

	return 0;
}