.PHONY: build

all: clean init prepare build

init:
	python3 init.py
prepare:
	python3 init.py
build:
	cd build && cmake .. && make imagine_tool
clean:
	cd build && make clean
