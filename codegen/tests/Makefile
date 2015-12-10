BUILD = $(shell for file in *.cminor;do file=$${file%.*}; echo $$file.x; done)
COMPILED = $(shell for file in *.cminor;do file=$${file%.*}; echo $$file.s; done)

build: $(BUILD)
gen: $(COMPILED)

%.s: %.cminor
	clear; ../cminor -codegen $< $@

%.x: %.o library.o
	gcc $^ -o $@

%.o: %.s
	gcc -c $< -o $@ -g

library.s: library.c
	gcc -S $< -o $@ -g

clean:
	rm *.s good*.x
