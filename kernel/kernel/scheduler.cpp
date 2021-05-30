#include <kernel/arch/i386/pit.h>

#include <kernel/thread.h>

#include <pthread.h>

/*uint8_t scheduler_ticks = 0;

extern "C" void scheduler() {
	scheduler_ticks++;
	if(scheduler_ticks < 10) return;
	scheduler_ticks = 0;
	if(!__this_thread) return;

	pthread_t pid = pthread_self() + 1;

	for(; pid < 65536; pid++) {
		if(!_threads[pid]) continue;
		if(_threads[pid]->sleep_until > system_timer_ms) continue;
		break;
	}
	if(pid == 65536) for(pid = 1; pid < pthread_self(); pid++) {
		if(!_threads[pid]) continue;
		if(_threads[pid]->sleep_until > system_timer_ms) continue;
		break;
	}
	if(pid == pthread_self()) return;

	_load(pid);
}*/
