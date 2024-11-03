CMPLR = gcc
TARGET = main.c
FLGS = -lcurses

a.elf: $(TARGET)
	$(CMPLR) $(TARGET) -o a.elf $(FLGS)

.PHONY: ct c

c: a.elf
	rm a.elf

ct: a.elf
	./a.elf
	rm a.elf
cs: 
	rm -rf saves/
