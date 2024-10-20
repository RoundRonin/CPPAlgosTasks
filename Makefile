# all:
# 	mkdir -p build
# 	cd build && cmake ..
# 	cd build && make
all:
	@mkdir -p build
	@cmake -S . -B build
	@cmake --build build

clean-old:
	rm -rf build

# build:
# 	for dir in tasks/*/ ; do \
# 		(cd "$$dir" && mkdir -p build && cmake -B build -S . && make -C build && mv build/* .); \
#     done
#
# clean:
# 	find . -name 'build' -exec rm -rf {} +


run:
	@./tasks/task1/name1

clean:
	@rm -rf build
	@find . -name 'name1' -delete
