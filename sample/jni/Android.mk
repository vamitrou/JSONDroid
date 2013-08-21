# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

#include $(call all-subdir-makefiles) 
#include $(LOCAL_PATH)/bson/Android.mk

include $(CLEAR_VARS)

MY_FILES += $(wildcard $(LOCAL_PATH)/*/*.c)
MY_FILES += $(wildcard $(LOCAL_PATH)/*/*.cpp)

MY_FILES := $(wildcard $(LOCAL_PATH)/*.cpp)

MY_FILES := $(MY_FILES:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += $(MY_FILES)


LOCAL_MODULE    := hello-jni
# LOCAL_SRC_FILES := hello-jni.cpp Database.cpp DiskLoc.cpp Extent.cpp Namespace.cpp Record.cpp

LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog 

//LOCAL_STATIC_LIBRARIES := hello-bson.so

include $(BUILD_SHARED_LIBRARY)

LOCAL_CFLAGS = -g -std=c99 -Wall 
