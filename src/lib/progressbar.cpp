#include "progressbar.h"

ProgressBar::ProgressBar(){}

ProgressBar::ProgressBar(unsigned long n_, const char* description_, std::ostream& out_){
    
    n = n_;
    frequency_update = n_;
    description = description_;
    out = &out_;
    
    unit_bar = "\u2588";
    unit_space = "-";
    desc_width = std::strlen(description);  // character width of description field

}

void ProgressBar::SetFrequencyUpdate(unsigned long frequency_update_){
    
    if(frequency_update_ > n){
        frequency_update = n;    // prevents crash if freq_updates_ > n_
    }
    else{
        frequency_update = frequency_update_;
    }
}

void ProgressBar::SetStyle(const char* unit_bar_, const char* unit_space_){
    
    unit_bar = unit_bar_;
    unit_space = unit_space_;
}

int ProgressBar::GetConsoleWidth(){

    int width;

    #ifdef _WINDOWS
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        width = csbi.srWindow.Right - csbi.srWindow.Left;
    #else
        struct winsize win;
        //注意！当我们使用pipe here-doc等通道获取程序参数时无法正确的获取窗口大小 此时我们将使用预定值
        if (ioctl(0, TIOCGWINSZ, &win) != -1)
            width = win.ws_col;
        else width = 100;
    #endif

    return width;
}

int ProgressBar::GetBarLength(){

    // get console width and according adjust the length of the progress bar

    int bar_length = static_cast<int>((GetConsoleWidth() - desc_width - CHARACTER_WIDTH_PERCENTAGE) / 2.);

    return bar_length;
}

void ProgressBar::ClearBarField(){

    for(int i=0;i<GetConsoleWidth();++i){
        *out << " ";
    }
    *out << "\r" << std::flush;
}

void ProgressBar::Progressed(unsigned long idx_)
{
    try{
        if(idx_ > n) throw idx_;

        // determines whether to update the progress bar from frequency_update
        if ((idx_ != n-1) && ((idx_+1) % (n/frequency_update) != 0)) return;

        // calculate the size of the progress bar
        int bar_size = GetBarLength();
    
        // calculate percentage of progress
        double progress_percent;
        if (n == 1)
            progress_percent = 100.0;
        else progress_percent = idx_* TOTAL_PERCENTAGE/(n-1);

        // calculate the percentage value of a unit bar 
        double percent_per_unit_bar = TOTAL_PERCENTAGE/bar_size;

        // display progress bar
        *out << " " << description << " |";

        for(int bar_length=0;bar_length<=bar_size-1;++bar_length){
            if(bar_length*percent_per_unit_bar<progress_percent){
                *out << unit_bar;
            }
            else{
                *out << unit_space;
            }
        }

        if(idx_ == n-1)
            *out << "|" << std::setw(CHARACTER_WIDTH_PERCENTAGE + 1) << std::setprecision(1) << std::fixed << progress_percent << "%\r" << std::flush << std::endl;
        else *out << "|" << std::setw(CHARACTER_WIDTH_PERCENTAGE + 1) << std::setprecision(1) << std::fixed << progress_percent << "%\r" << std::flush;
    }
    catch(unsigned long e){
        ClearBarField();
        std::cerr << "PROGRESS_BAR_EXCEPTION: _idx (" << e << ") went out of bounds, greater than n (" << n << ")." << std::endl << std::flush;
    }

}