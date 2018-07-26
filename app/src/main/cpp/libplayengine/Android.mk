LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include

LOCAL_MODULE := libplayengine

include $(BUILD_SHARED_LIBRARY)
#include $(BUILD_STATIC_LIBRARY)
