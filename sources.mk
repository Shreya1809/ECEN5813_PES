SOURCES_COMMON = \
	src/debug.c \
	src/data.c\
	src/memory.c \
	src/conversion.c \
	src/circbuf.c \
	src/project1.c

# Must keep main() functions separate between main.c and test
SOURCES_MAIN = src/main.c

SOURCES_TEST = test/project1_test.c

SOURCES_KL25Z_C = \
	src/blink.c \
	src/startup.c \
	src/system_MKL25Z4.c

SOURCES_KL25Z_S = src/startup_MKL25Z4.S


