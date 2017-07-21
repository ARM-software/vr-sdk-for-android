LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := Native
LOCAL_CFLAGS    := -Werror
LOCAL_SRC_FILES := main.cpp loader.cpp armvr.cpp
LOCAL_LDLIBS    := -llog -lGLESv3 -lEGL -lm

include $(BUILD_SHARED_LIBRARY)