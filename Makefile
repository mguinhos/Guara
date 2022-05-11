NAME= guara
CC= clang
CC_INCLUDES= -Iinclude
CC_LIBS= -Llib -lguara
CC_FLAGS= -Wno-deprecated-declarations

AR= llvm-ar

ifeq ($(OS),Windows_NT)
	NAME_EXT= $(NAME).exe
	LIBNAME_EXT= $(NAME).lib
else
	NAME_EXT= $(NAME)
	LIBNAME_EXT= lib$(NAME).a
endif

all: $(LIBNAME_EXT)
	$(CC) main.c -o bin/$(NAME_EXT) $(CC_INCLUDES) $(CC_LIBS) $(CC_FLAGS)

run:
	./bin/$(NAME_EXT)

$(LIBNAME_EXT): lib/object.o lib/str.o lib/int.o lib/list.o lib/exception.o lib/tracer.o
	$(AR) rc lib/$@ $^

lib/%.o: src/%.c
	$(CC) -c $< -o $@ $(CC_INCLUDES) $(CC_FLAGS)
