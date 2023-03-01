slide : main.c
	gcc main.c -o slide
	sudo cp slide /bin/slide

clean : 
	rm slide
	sudo rm /bin/slide