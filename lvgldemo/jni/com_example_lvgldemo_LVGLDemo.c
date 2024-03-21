#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include "com_example_lvgldemo_LVGLDemo.h"
#include "lvgldemo.h"
#include <stdint.h>

#include <android/log.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#define LOG_TAG "lvgldemo"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

int32_t my_screen[480 * 320] = {0};

jintArray JNICALL Java_com_example_lvgldemo_LVGLDemo_getIntArray
  (JNIEnv *env, jclass cls, jint size)
{
        jint *tmp = (jint *)malloc(sizeof(jint) * size);  /* make sure it is large enough! */
        int j;
        jintArray iarr = (*env)->NewIntArray(env, size);
        if (iarr == NULL) {
            return NULL; /* out of memory error thrown */
        }
        for (j = 0; j < size; j++) {
            //tmp[j] = 0xff00ff00;
        	if (j < 480 * 320) {
        		tmp[j] = (jint)my_screen[j];
        	} else {
        		j = 0xFFFF0000;
        	}
        }
        (*env)->SetIntArrayRegion(env, iarr, 0, size, tmp);
    free(tmp);
    return iarr;
}

void JNICALL Java_com_example_lvgldemo_LVGLDemo_main
  (JNIEnv *env, jclass cls)
{
	LOGI("main");
#if 0
	int j;
	for (j = 0; j < 480 * 320; j++) {
		my_screen[j] = 0xff00ff00;
	}
#endif
	my_main();
}
