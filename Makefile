CC = gcc
LD = ld
RM = -rm
PERL = perl

CFLAGS = -g -m64
INCLUDES = -Iinclude

MAIN = run_aes
OBJS = aes/aes.o aes/aesp8-ppc.o

BANNER = @echo "\n=== $@\n"

MACH = $(shell uname -m)

all: $(MAIN)

$(MAIN): $(OBJS)
	$(BANNER)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

aes/aesp8-ppc.S: aes/aesp8-ppc.pl
	$(BANNER)
	$(PERL) $< linux-$(MACH) > $@

aes/aesp8-ppc.o: aes/aesp8-ppc.S
	$(BANNER)
	$(CC) $(CFLAGS) $(INCLUDES) -c -mno-strict-align -nostdinc -D__KERNEL__ -DHAVE_AS_ATHIGH=1 -D__ASSEMBLY__ -Iarch/powerpc -mabi=elfv2 -Wa,-maltivec -Wa,-gdwarf-2  -DCC_HAVE_ASM_GOTO $< -o $@

%.o: %.c
	$(BANNER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

view:
	objdump -Drl $(MAIN)

gdb:
	gdb -tui -x $(MAIN)

clean:
	$(BANNER)
	$(RM) -f aes/*.o aes/aesp8-ppc.S $(MAIN)
