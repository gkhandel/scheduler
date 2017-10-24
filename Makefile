.PHONY: all run configure compile rmbuild rebuild

BUILD = build

all: run

run: compile
	bin/scheduler data/proto-json/instance1.json out.json

test: compile
	bin/scheduler_test

rmbuild:
	rm -rf $(BUILD)

rebuild: | rmbuild $(BUILD)

$(BUILD): CMakeLists.txt
	mkdir -p $(BUILD)
	cd $(BUILD) ; cmake ..

configure:
	mkdir -p $(BUILD)
	cd $(BUILD) ; cmake ..

compile: $(BUILD)
	make -C $(BUILD)
