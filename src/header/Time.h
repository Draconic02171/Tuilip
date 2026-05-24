#ifdef _WIN32
    #include <windows.h>
#else
    #include <time.h>
    #include <errno.h>
#endif

inline void WaitInMilisec(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#endif
}