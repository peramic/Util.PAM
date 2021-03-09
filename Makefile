ifeq ($(shell uname -m), armv7l)
	ARCH ?= armhf
else
	ARCH ?= amd64
endif

CC ?= gcc
JDK_INCLUDE=/usr/lib/jvm/java-7-openjdk-$(ARCH)/include
CFLAGS=-std=c99 -Iinclude -Itarget/include -I$(JDK_INCLUDE) -I$(JDK_INCLUDE)/linux -O3 -Wall -fmessage-length=0 -fPIC -MMD -MP
LDFLAGS=--std=c99 -lpam -lpam_misc
SOURCES=src/pam_check_user.c
TARGET=target/pam-check-user
OBJS=$(SOURCES:.c=.o)


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET) src/*.d
