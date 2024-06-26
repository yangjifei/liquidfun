# Copyright (c) 2014 Google, Inc.
#
# This software is provided 'as-is', without any express or implied
# warranty.  In no event will the authors be held liable for any damages
# arising from the use of this software.
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
# 1. The origin of this software must not be misrepresented; you must not
# claim that you wrote the original software. If you use this software
# in a product, an acknowledgment in the product documentation would be
# appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
# misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

ifneq (,$(findstring armeabi-v7a,$(APP_ABI)))
  LOCAL_ARM_NEON := true
  b2_cflags := -DLIQUIDFUN_SIMD_NEON -mfloat-abi=softfp -mfpu=neon
  b2_extensions := cpp s
else ifneq (,$(findstring arm64-v8a,$(APP_ABI)))
  LOCAL_ARM_NEON := true
  b2_cflags := -DLIQUIDFUN_SIMD_NEON -mfloat-abi=softfp -mfpu=neon
  b2_extensions := cpp s
else
  b2_extensions := cpp
endif


