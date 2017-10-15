CC = gcc
LD = ld
RM = -rm
PERL = perl

CFLAGS = -g -m64
INCLUDES = -Iinclude

BANNER = @echo "\n=== $@\n"

MACH = $(shell uname -m)

AES = run_aes
AES_OBJS = aes/aes.o aes/aesp8-ppc.o

CHACHA = run_chacha20
CHACHA_OBJS = chacha20/chacha.o chacha20/chacha-ppc.o

ECDSA = run_ecdsa
ECDSA_OBJS = ecdsa/ecdsa.o ecdsa/ecp_nistz256-ppc64.o

all: $(AES) $(CHACHA) $(ECDSA)

$(AES): $(AES_OBJS)
	$(BANNER)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(AES_OBJS) $(LFLAGS) $(LIBS)

$(CHACHA): $(CHACHA_OBJS)
	$(BANNER)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(CHACHA_OBJS) $(LFLAGS) $(LIBS)

$(ECDSA): $(ECDSA_OBJS)
	$(BANNER)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(ECDSA_OBJS) $(LFLAGS) $(LIBS)

%.S: %.pl
	$(BANNER)
	$(PERL) $< linux-$(MACH) > $@

%-ppc.o: %-ppc.S
	$(BANNER)
	$(CC) $(CFLAGS) $(INCLUDES) -c -mno-strict-align -nostdinc \
		-D__KERNEL__ -DHAVE_AS_ATHIGH=1 -D__ASSEMBLY__ -Iarch/powerpc \
		-mabi=elfv2 -Wa,-maltivec -Wa,-gdwarf-2  -DCC_HAVE_ASM_GOTO \
		$< -o $@

%.o: %.c
	$(BANNER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(BANNER)
	$(RM) -f aes/*.o aes/*.S chacha20/*.o chacha20/*.S run_*

.PRECIOUS: %.S
