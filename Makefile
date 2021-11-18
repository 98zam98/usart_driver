all:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o out.o main.c
	avr-gcc -mmcu=atmega328p out.o -o out
	avr-objcopy -O ihex -R .eeprom out out.hex
	#burn
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:out.hex
dev :
	ls /dev/ | grep ACM

compile :
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o out.o main.c
	avr-gcc -mmcu=atmega328p out.o -o out
	avr-objcopy -O ihex -R .eeprom out out.hex

burn:
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:out.hex