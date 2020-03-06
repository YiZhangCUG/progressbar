#ifndef _GCTL_PROGRESSBAR_H
#define _GCTL_PROGRESSBAR_H
#include <sys/ioctl.h>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <thread>
#include <chrono>
//进度条宏定义
#define TOTAL_PERCENTAGE 100.0 //!< 设置总的百分比为100%。
#define CHARACTER_WIDTH_PERCENTAGE 4 //!< 设置每显示一个字符所占的百分比为5%。

namespace gctl
{
	/**
	 * @brief      终端显示进度条的类。
	 * @warning    这个类是一个在终端显示进度的通用类型。
	 */
	class ProgressBar
	{
	public: 

	    ProgressBar(); ///< 类默认的构造函数。
	    /**
	     * @brief      类默认的构造函数。
	     *
	     * @param[in]  n_            整形，进度条循环的最大值。
	     * @param[in]  description_  字符串，进度条的名称。
	     * @param      out_          输出至标准错误输出，避免在程序输出重定向时无法显示。
	     */
	    ProgressBar(unsigned long n_, const char *description_="", std::ostream& out_=std::cerr);
	    /**
	     * @brief      设置进度条刷新次数，默认为进度条的长度，即每次都更新。减少更新的次数可适当的减少在屏幕上打印进度条的时间
	     *
	     * @param[in]  frequency_update_  整形，刷新的次数
	     */
	    void SetFrequencyUpdate(unsigned long frequency_update_);
	    /**
	     * @brief      设置进度条的风格。
	     *
	     * @param[in]  unit_bar_    字符串，已达到进度的符号。
	     * @param[in]  unit_space_  字符串，未达到进度的符号。
	     */
	    void SetStyle(const char* unit_bar_, const char* unit_space_);
	    /**
	     * @brief      更新当前已达到的进度值。
	     *
	     * @param[in]  idx_  整形，当前进度条循环的值。
	     */
	    void Progressed(unsigned long idx_);

	private:
		
	    unsigned long n;
	    unsigned int desc_width;
	    unsigned long frequency_update;
	    std::ostream* out;
			
	    const char *description;
	    const char *unit_bar;
	    const char *unit_space;
			
	    void ClearBarField();
	    int GetConsoleWidth();
	    int GetBarLength();

	};
}
#endif //_GCTL_PROGRESSBAR_H