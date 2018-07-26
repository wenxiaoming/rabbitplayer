#include <jni.h>
#include <string>
#include "libp2pcore/P2PCoreTest.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_rabbitplayer_kevin_rabbitplayer_RabbitPlayerActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {

    start_p2pcore();

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
