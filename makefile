PREFIX=sparc-gaisler-elf-
CC = $(PREFIX)gcc
CFLAGS = -g -O3 -qbsp=gr716 
DESTDIR = .
pwm.elf: pwm.c librv/src/gpio/gpio.c librv/src/osal/bcc2/autoinit.c  librv/src/osal/bcc2/ldstub.c librv/src/clkgate/clkgate.c| $(DESTDIR) 
	$(CC) $(CFLAGS) $^ -o $@