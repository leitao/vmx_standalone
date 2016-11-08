CC = gcc
LD = ld
RM = -rm
PERL = perl

CFLAGS = -g -m64
INCLUDES = -Iinclude

MAIN = aes
OBJS = aes.o aesp8-ppc.o

BANNER = @echo "\n=== $@\n"

MACH = $(shell uname -m)

all: $(MAIN)

$(MAIN): $(OBJS)
	$(BANNER)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

aesp8-ppc.S: aesp8-ppc.pl
	$(BANNER)
	$(PERL) $< linux-$(MACH) > $@

aesp8-ppc.o: aesp8-ppc.S
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
	$(RM) -f *.o aesp8-ppc.S $(MAIN)
