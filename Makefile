# all:
# 	mkdir -p build
# 	cd build && cmake ..
# 	cd build && make
all:
	@mkdir -p build
	@cmake -S . -B build
	@cmake --build build

all-deb:
	@mkdir -p build
	@cmake -S . -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo
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
	@./tasks/task1/exec_hello_world
	@./tasks_hash_tables/task1_what_is_a_set/exec_what_is_a_set

test:
	@./tasks/task1/test_hello_world
	@./tasks_hash_tables/task1_what_is_a_set/test_what_is_a_set

clean:
	@rm -rf build
	@find . -name 'exec_hello_world' -delete
	@find . -name 'exec_what_is_a_set' -delete
	@find . -name 'test_hello_world' -delete
	@find . -name 'test_what_is_a_set' -delete
