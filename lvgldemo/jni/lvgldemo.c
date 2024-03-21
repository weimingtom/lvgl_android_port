#include "sdl_api.h"

#include <unistd.h> //usleep
#include <pthread.h>
#include "lvgl/lvgl.h"
#include "lv_examples/src/lv_demo_widgets/lv_demo_widgets.h"
#include "lv_my_dev/touchpad.h"
#include "lv_my_dev/tft.h"

static int tick_thread(void *data)
{
	//FIXME:PORT
	while (1) {
		lv_tick_inc(5);
		usleep(5000);//::Sleep(5);   /*Sleep for 1 millisecond*/
	}
	return 0;
}

void* ThreadProc(void* arg){
	tick_thread(arg);
	return 0;
}

int my_main()
{
//	DWORD threadID;
//	HANDLE hThread;
	//https://blog.csdn.net/tq384998430/article/details/96841247
	//https://blog.lvgl.io/2018-01-03/linux_fb
	//https://github.com/lvgl/lv_port_linux_frame_buffer
	lv_init();
	tft_init();
	touchpad_init();
	lv_demo_widgets();
//	hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, &threadID);

    pthread_t tid;
	pthread_create(&tid, NULL, ThreadProc, NULL);
	

	while (1) {
		//FIXME:PORT
		//CanvasSetColor(WINDOW_BGCOLOR);
		if (MainFrameGetMsg() != 0) {
			break;
		}
		//CanvasLock();
		usleep(5000); //::Sleep(5)
		lv_task_handler();
		//CanvasUnlock();
		MainFrameRefresh();
	}

	return 0;
}
