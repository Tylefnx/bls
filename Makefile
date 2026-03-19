CC      = gcc
CFLAGS  = -Wall -O2
LDFLAGS = -lncursesw -ltinfow -lcrypt
TARGET  = based-login
SRCS    = main.c ui_core.c widgets.c auth.c system_utils.c
OBJS    = $(SRCS:.c=.o)
PREFIX  = /usr
DINITDIR = /etc/dinit.d

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

install: $(TARGET)
	install -Dm755 $(TARGET) $(DESTDIR)$(PREFIX)/bin/$(TARGET)
	install -Dm755 bls-wrapper.sh $(DESTDIR)$(PREFIX)/bin/bls-wrapper.sh
	chmod u+s $(DESTDIR)$(PREFIX)/bin/$(TARGET)
	mkdir -p $(DESTDIR)$(DINITDIR)
	printf "type = process\ncommand = $(PREFIX)/bin/bls-wrapper.sh\nsmooth-recovery = true\ndepends-on = login.target\n" > $(DESTDIR)$(DINITDIR)/based-login

clean:
	rm -f *.o $(TARGET)
