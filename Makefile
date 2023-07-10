
ifndef ($(exe_name)) 
exe_name = example
endif
exe_name = Rotating_3D

CPP_VER = c++20
CMAKE_CXX_DEBUG_FLAGS = "$${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -Wpointer-arith -Wcast-qual -Wno-missing-braces -Wshadow -Wunused -Wcast-align -g -O0 -std=$(CPP_VER)"
CMAKE_CXX_RELEASE_FLAGS = "$${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -Wpointer-arith -Wcast-qual -Wno-missing-braces -Wshadow -Wunused -Wcast-align -Os -s -std=$(CPP_VER)"

bin/Debug: CMakeLists.txt lib/CMakeLists.txt $(wildcard $(src/*.c)) src/*.cpp $(wildcard $(include/*.h)) $(wildcard $(include/*.hpp))
	cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="Debug" -DEXE_NAME=$(exe_name) -DCMAKE_CXX_FLAGS=$(CMAKE_CXX_DEBUG_FLAGS) -B "./bin/Debug/"
	cmake --build "./bin/Debug/" --config Debug

release: $(wildcard $(src/*.c)) $(wildcard $(src/*.cpp)) $(wildcard $(include/*.h)) $(wildcard $(include/*.hpp))
	cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="Release" -DEXE_NAME=$(exe_name) -DCMAKE_CXX_FLAGS=$(CMAKE_CXX_RELEASE_FLAGS) -B "./bin/Release/"
	cmake --build "./bin/Release" --config Release

run: bin/Debug
	./bin/Debug/$(exe_name)

debug: bin/Debug
	gdb ./bin/Debug/$(exe_name)

run_release: release
	./bin/Release/$(exe_name)

clean:
	rm -rf bin/Debug bin/Release
