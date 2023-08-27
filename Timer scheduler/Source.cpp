#include "TimerScheduler.hpp"

#include <cmath>
#include <iostream>

using systemClock = std::chrono::system_clock;
using steadyClock = std::chrono::steady_clock;
using s_t = std::chrono::seconds;
using ns_t = std::chrono::nanoseconds;

// ST - single timer, RT - repeating timer
// NB: The printing of the repeating timers might be messed because of the concurrent execution
int main()
{
    TimerScheduler s(2);
    s.start();

    std::cout << "Starting single timers at " << systemClock::now() << std::endl;

    s.scheduleSingle("1", s_t(3), []()
        {
            std::cout << std::endl << "Executing first ST at " << systemClock::now() << std::endl;
        }
    );
    s.scheduleSingle("2", s_t(4), []()
        {
            std::cout << std::endl << "Executing second ST at " << systemClock::now() << std::endl;
            std::this_thread::sleep_for(s_t(7));
        }
    );
    s.scheduleSingle("3", s_t(5), [](int a, double b)
        {
            std::cout << std::endl << "Executing third ST with params " << a << " and " << b << " at " << systemClock::now() << std::endl;
        },
        5, 23
            );

    std::this_thread::sleep_for(s_t(15)); // wait the single timers

    //////////////////////////////////////////////////

    std::cout << std::endl << "Starting repeating timers at " << systemClock::now() << std::endl;

    s.scheduleRepeat("4", TimerScheduler::IntervalReps{ s_t(2), 3 }, []() {std::cout << std::endl << "Executing first RT at " << systemClock::now() << std::endl; });
    s.scheduleRepeat("5", TimerScheduler::IntervalReps{ s_t(2), 4 }, []() {std::cout << std::endl << "Executing second RT at " << systemClock::now() << std::endl; });
    s.scheduleRepeat("6", TimerScheduler::IntervalReps{ s_t(2), 5 }, [](int a, int b) {std::cout << std::endl << "Executing third RT at " << systemClock::now() << std::endl; }, 2, 222);
    s.scheduleRepeat("7", TimerScheduler::IntervalReps{ s_t(2) }, []() {std::cout << std::endl << "Executing unbounded RT " << systemClock::now() << std::endl; });

    std::this_thread::sleep_for(s_t(20)); // wait the repeating timers to be executed several times

    std::cout << std::endl << "Updating the interval of the unbounded repeating timer from 2 to 4 secs" << std::endl;
    s.updateInterval("7", s_t(4));

    std::this_thread::sleep_for(s_t(15)); // wait the unbounded timer to be executed several times with its new interval

    std::cout << std::endl << "Cancelling the unbounded repeating timer" << std::endl;
    s.cancelTimer("7");

    std::cout << std::endl << "Currently scheduled timers (0 is expected): " << s.currentlyScheduled() << std::endl;
    std::cout << std::endl << "Waiting some time to see that the canceled timer won't be executed again..." << std::endl;
    std::this_thread::sleep_for(s_t(10));

    // We can also schedule a single timer and get its result when it's ready
    std::cout << std::endl << "Starting single timer" << std::endl;
    auto res = s.scheduleSingle("1", s_t(0), [](int param) { return sqrt(param); }, 121);
    std::cout << std::endl << "Getting its result... " << res.get() << std::endl;

    return 0;
}