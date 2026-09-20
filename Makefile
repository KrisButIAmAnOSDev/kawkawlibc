include .config

CC ?= gcc
CFLAGS ?= -ffreestanding -fno-builtin -fno-stack-protector -nostdinc -Iinclude -std=c11
ASM ?= gcc
ASMFLAGS ?= -masm=intel

ifeq ($(ARCH),arm64)
  CFLAGS += -march=armv8-a
  ASMFLAGS += -march=armv8-a
endif

LIB_OBJ := src/arch/x86_64/entry.o src/arch/x86_64/syscall.o src/syscall.o src/errno.o

ifeq ($(ENABLE_STRING),1)
LIB_OBJ += src/string.o
endif
ifeq ($(ENABLE_STDIO),1)
LIB_OBJ += src/stdio.o
endif
ifeq ($(ENABLE_MALLOC),1)
  LIB_OBJ += src/stdlib.o
endif
ifeq ($(ENABLE_CTYPE),1)
LIB_OBJ += src/ctype.o
endif
ifeq ($(ENABLE_ASSERT),1)
LIB_OBJ += src/assert.o
endif

ifeq ($(ENABLE_WCHAR),1)
LIB_OBJ += src/wchar.o
endif

ifeq ($(ENABLE_WCTYPE),1)
LIB_OBJ += src/wctype.o
endif

ifeq ($(ENABLE_LOCALE),1)
LIB_OBJ += src/locale.o
endif

ifeq ($(ENABLE_MATH),1)
LIB_OBJ += src/math.o
endif

.PHONY: all clean run run-full full verified menuconfig config

all: libkawkaw.a tests/all

full: all tests/easter
	@echo "full build complete (easter egg enabled)"

libkawkaw.a: $(LIB_OBJ)
	ar rcs $@ $^

src/arch/x86_64/entry.o: src/arch/x86_64/entry.S
	$(ASM) $(ASMFLAGS) -c -o $@ $<

src/arch/x86_64/syscall.o: src/arch/x86_64/syscall.S
	$(ASM) $(ASMFLAGS) -c -o $@ $<

src/syscall.o: src/syscall.c include/kawkawlibc.h include/stat.h
	$(CC) $(CFLAGS) -c -o $@ $<

src/string.o: src/string.c include/string.h include/kawkawlibc.h
	$(CC) $(CFLAGS) -c -o $@ $<

src/errno.o: src/errno.c include/kawkawlibc.h
	$(CC) $(CFLAGS) -c -o $@ $<

src/stdio.o: src/stdio.c include/stdio.h include/string.h include/kawkawlibc.h
	$(CC) $(CFLAGS) -c -o $@ $<

src/stdlib.o: src/stdlib.c include/stdlib.h include/string.h include/kawkawlibc.h
	$(CC) $(CFLAGS) -c -o $@ $<

src/ctype.o: src/ctype.c include/ctype.h include/kawkawlibc.h
	$(CC) $(CFLAGS) -c -o $@ $<

src/assert.o: src/assert.c include/assert.h include/string.h include/stdio.h include/stdlib.h include/kawkawlibc.h
	$(CC) $(CFLAGS) -c -o $@ $<

src/wchar.o: src/wchar.c include/wchar.h include/wctype.h include/string.h include/kawkawlibc.h
	$(CC) $(CFLAGS) -c -o $@ $<

src/wctype.o: src/wctype.c include/wctype.h include/wchar.h include/string.h include/kawkawlibc.h
	$(CC) $(CFLAGS) -c -o $@ $<

src/locale.o: src/locale.c include/locale.h include/kawkawlibc.h
	$(CC) $(CFLAGS) -c -o $@ $<

src/math.o: src/math.c include/math.h include/kawkawlibc.h
	$(CC) $(CFLAGS) -c -o $@ $<

tests/all.o: tests/all.c libkawkaw.a
	$(CC) $(CFLAGS) -c -o $@ $<

tests/all: tests/all.o libkawkaw.a
	$(CC) -nostdlib -static -o $@ $< -L. -lkawkaw

tests/easter: src/easter.o tests/easter.o libkawkaw.a
	$(CC) -nostdlib -static -o $@ $^ -L. -lkawkaw

src/easter.o: src/easter.c
	$(CC) $(CFLAGS) -c -o $@ $<

run: tests/all
	./tests/all

run-full: full
	./tests/easter

run-stdio: tests/all
	./tests/all

headers: tests/all
	./tests/all

run-headers: tests/all
	./tests/all

run-verify: tests/all
	./tests/all

run-stdlib: tests/all
	./tests/all

run-more: tests/all
	./tests/all

run-ctype: tests/all
	./tests/all

run-errno: tests/all
	./tests/all

run-assert: tests/all
	./tests/all

run-inttypes: tests/all
	./tests/all

verified: tests/all
	@echo "ldd: " && ldd ./tests/all 2>&1 | head -1
	@readelf -d ./tests/all | grep -q "no dynamic section" && echo "readelf: no dynamic section"
	@nm ./tests/all | grep -q " U " && echo "nm: HAS undefined symbols" || echo "nm: zero undefined symbols"

menuconfig:
	@${EDITOR:-nano} .config

config:
	@cat .config

clean:
	rm -f libkawkaw.a $(LIB_OBJ) src/easter.o tests/all.o tests/all tests/hello.o tests/hello tests/stdio.o tests/stdio tests/headers.o tests/headers tests/verify.o tests/verify tests/stdlib.o tests/stdlib tests/more.o tests/more tests/easter.o tests/easter tests/ctype.o tests/ctype tests/errno.o tests/errno tests/inttypes.o tests/inttypes tests/assert.o tests/assert src/wchar.o src/wctype.o src/locale.o src/math.o
