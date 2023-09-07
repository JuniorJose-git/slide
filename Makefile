CC ?= gcc
DESTDIR ?= /usr/local/bin

.PHONY: install clean

slide: main.c
	$(CC) main.c -o slide

install: slide
	install slide $(DESTDIR)/slide

clean: 
	rm -f slide