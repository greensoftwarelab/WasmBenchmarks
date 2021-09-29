smallcompile:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge  sortingnatural.c -o Small_dataset/C/sortingnatural_runSMALL -DSMALL_DATASET

mediumcompile:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge  sortingnatural.c -o Medium_dataset/C/sortingnatural_runMEDIUM -DMEDIUM_DATASET

largecompile:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge  sortingnatural.c -o Large_dataset/C/sortingnatural_runLARGE -DLARGE_DATASET

wasmsmall:
	emcc sortingnatural.c -DSMALL_DATASET -o Small_dataset/WASM/sortingnatural_runSMALL.js -O2 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1

jssmall:
	emcc sortingnatural.c -DSMALL_DATASET -o Small_dataset/JS/sortingnatural_runSMALL.js -O2 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1

wasmmedium:
	emcc sortingnatural.c -DMEDIUM_DATASET -o Medium_dataset/WASM/sortingnatural_runMEDIUM.js -O2 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1

jsmedium:
	emcc sortingnatural.c -DMEDIUM_DATASET -o Medium_dataset/JS/sortingnatural_runMEDIUM.js -O2 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1

wasmlarge:
	emcc sortingnatural.c -DLARGE_DATASET -o Large_dataset/WASM/sortingnatural_runLARGE.js -O2 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1

jslarge:
	emcc sortingnatural.c -DLARGE_DATASET -o Large_dataset/JS/sortingnatural_runLARGE.js -O2 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1

compileall:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge  sortingnatural.c -o Small_dataset/C/sortingnatural_runSMALL -DSMALL_DATASET
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge  sortingnatural.c -o Medium_dataset/C/sortingnatural_runMEDIUM -DMEDIUM_DATASET
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge  sortingnatural.c -o Large_dataset/C/sortingnatural_runLARGE -DLARGE_DATASET
	emcc sortingnatural.c -DSMALL_DATASET -o Small_dataset/WASM/sortingnatural_runWASM_SMALL.js -O2 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1
	emcc sortingnatural.c -DSMALL_DATASET -o Small_dataset/JS/sortingnatural_runJS_SMALL.js -O2 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1
	emcc sortingnatural.c -DMEDIUM_DATASET -o Medium_dataset/WASM/sortingnatural_runWASM_MEDIUM.js -O2 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1
	emcc sortingnatural.c -DMEDIUM_DATASET -o Medium_dataset/JS/sortingnatural_runJS_MEDIUM.js -O2 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1
	emcc sortingnatural.c -DLARGE_DATASET -o Large_dataset/WASM/sortingnatural_runWASM_LARGE.js -O2 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1
	emcc sortingnatural.c -DLARGE_DATASET -o Large_dataset/JS/sortingnatural_runJS_LARGE.js -O2 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1
