MCU_TARGET=attiny85
STD_CXX=c++20
OPTIMIZE=-Os

CXX=avr-g++
CC=avr-gcc
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump

CXXFLAGS=-std=$(STD_CXX) -g -mmcu=$(MCU_TARGET) -Wall $(OPTIMIZE) -DF_CPU=1000000 -Wno-volatile -I /home/rcosme/build/att85/include -I ../../include -I .

demos = read_rom

all: $(demos:%=%.elf) $(demos:%=%.lst) $(demos:%=%.s)

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(demos:%=%.d)

%.s: %.cpp
	$(CXX) $(CXXFLAGS) -S $^

%.elf: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^ onewire.c

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

.PHONY: flash_%
flash-%: %.hex
	avrdude -p t85 -c usbasp -P usb  -U flash:w:$<

.PHONY: clean
clean:
	rm -f *.hex *.lst *.elf *.o *.d *.s

