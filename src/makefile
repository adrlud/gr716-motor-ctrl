PREFIX=sparc-gaisler-elf-
CC = $(PREFIX)gcc
INCDIR=../include
CFLAGS = -g -O3  -qbsp=gr716 -mcpu=leon3 -I$(INCDIR) 
DESTDIR = ../bin
OBJS_RELATIVE= bldc_commutate.o bldc_init.o bldc_interrupt.o gr716_pwm.o gr716_gpio.o gr716_misc.o gr716_timestamp.o gr716_spi.o gr716_sram.o gr716_adc.o gr716_io.o
OBJS= $(addprefix $(DESTDIR)/,$(OBJS_RELATIVE))

all: main.elf

$(DESTDIR)/bldc_commutate.o: bldc_commutate.c $(INCDIR)/bldc/bldc_commutate.h $(INCDIR)/gr716/gr716.h
	$(CC) $(CFLAGS) -c bldc_commutate.c -o $@

$(DESTDIR)/bldc_init.o: bldc_init.c $(INCDIR)/bldc/bldc_init.h $(INCDIR)/gr716/gr716.h
	$(CC) $(CFLAGS) -c bldc_init.c -o $@

$(DESTDIR)/bldc_interrupt.o: bldc_interrupt.c $(INCDIR)/bldc/bldc_interrupt.h $(INCDIR)/gr716/gr716.h
	$(CC) $(CFLAGS) -c bldc_interrupt.c -o $@

$(DESTDIR)/gr716_timestamp.o: gr716_timestamp.c $(INCDIR)/gr716/gr716_timestamp.h $(INCDIR)/gr716/gr716.h
	$(CC) $(CFLAGS) -c gr716_timestamp.c -o $@

$(DESTDIR)/gr716_pwm.o: gr716_pwm.c $(INCDIR)/gr716/gr716_pwm.h $(INCDIR)/gr716/gr716.h
	$(CC) $(CFLAGS) -c gr716_pwm.c -o $@

$(DESTDIR)/gr716_gpio.o: gr716_gpio.c $(INCDIR)/gr716/gr716.h
	$(CC) $(CFLAGS) -c gr716_gpio.c -o $@

$(DESTDIR)/gr716_misc.o: gr716_misc.c $(INCDIR)/gr716/gr716_misc.h $(INCDIR)/gr716/gr716.h
	$(CC) $(CFLAGS) -c gr716_misc.c -o $@

$(DESTDIR)/gr716_spi.o: gr716_spi.c $(INCDIR)/gr716/gr716_spi.h $(INCDIR)/gr716/gr716.h
	$(CC) $(CFLAGS) -c gr716_spi.c -o $@

$(DESTDIR)/gr716_sram.o: gr716_sram.c $(INCDIR)/gr716/gr716_sram.h $(INCDIR)/gr716/gr716.h
	$(CC) $(CFLAGS) -c gr716_sram.c -o $@

$(DESTDIR)/gr716_adc.o: gr716_adc.c $(INCDIR)/gr716/gr716_adc.h $(INCDIR)/gr716/gr716.h
	$(CC) $(CFLAGS) -c gr716_adc.c -o $@

$(DESTDIR)/gr716_io.o: gr716_io.c $(INCDIR)/gr716/gr716_io.h $(INCDIR)/gr716/gr716.h
	$(CC) $(CFLAGS) -c gr716_io.c -o $@

main.elf: bldc_main.c $(OBJS)
	$(CC) $(CFLAGS) bldc_main.c /opt/bcc-2.0.8-rc.3-gdb8-gcc/sparc-gaisler-elf/lib/libdrv.a -o $(DESTDIR)/$@ $(OBJS) 

clean:
	rm -f $(OBJS)

