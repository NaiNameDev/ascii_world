CMPLR = gcc
TARGET = main.c
FLGS = -o

a.elf: $(TARGET)
	$(CMPLR) $(TARGET) $(FLGS) a.elf

.PHONY: ct c

c: a.elf
	rm a.elf

ct: a.elf
	./a.elf
	rm a.elf
