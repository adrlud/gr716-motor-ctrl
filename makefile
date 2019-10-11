PREFIX=sparc-gaisler-elf-
CC = $(PREFIX)gcc
CFLAGS = -g -O3 -qbsp=gr716 
DESTDIR = .
main.elf: init.c interrupt.c src/gr716_pwm.c src/gr716_gpio.c src/gr716_misc.c src/gr716_spi.c src/gr716_sram.c | $(DESTDIR) 
	$(CC) $(CFLAGS) $^ -o $@