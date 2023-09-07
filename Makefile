slide : main.c
	gcc main.c -o slide

install :
	cp slide /bin/slide

clean : 
	sudo rm /bin/slide