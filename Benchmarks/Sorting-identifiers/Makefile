smallcompile:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge  sortingids.c -o Small_dataset/C/sortingids_runSMALL -DSMALL_DATASET

mediumcompile:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge  sortingids.c -o Medium_dataset/C/sortingids_runMEDIUM -DMEDIUM_DATASET

largecompile:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge  sortingids.c -o Large_dataset/C/sortingids_runLARGE -DLARGE_DATASET

wasmsmall:
	emcc sortingids.c -DSMALL_DATASET -o Small_dataset/WASM/sortingids_runSMALL.js -O2 -s WASM=1

jssmall:
	emcc sortingids.c -DSMALL_DATASET -o Small_dataset/JS/sortingids_runSMALL.js -O2 -s WASM=0

wasmmedium:
	emcc sortingids.c -DMEDIUM_DATASET -o Medium_dataset/WASM/sortingids_runMEDIUM.js -O2 -s WASM=1

jsmedium:
	emcc sortingids.c -DMEDIUM_DATASET -o Medium_dataset/JS/sortingids_runMEDIUM.js -O2 -s WASM=0

wasmlarge:
	emcc sortingids.c -DLARGE_DATASET -o Large_dataset/WASM/sortingids_runLARGE.js -O2 -s WASM=1

jslarge:
	emcc sortingids.c -DLARGE_DATASET -o Large_dataset/JS/sortingids_runLARGE.js -O2 -s WASM=0

compileall:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge  sortingids.c -o Small_dataset/C/sortingids_runSMALL -DSMALL_DATASET
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge  sortingids.c -o Medium_dataset/C/sortingids_runMEDIUM -DMEDIUM_DATASET
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge  sortingids.c -o Large_dataset/C/sortingids_runLARGE -DLARGE_DATASET
	emcc sortingids.c -DSMALL_DATASET -o Small_dataset/WASM/sortingids_runWASM_SMALL.js -O2 -s WASM=1
	emcc sortingids.c -DSMALL_DATASET -o Small_dataset/JS/sortingids_runJS_SMALL.js -O2 -s WASM=0
	emcc sortingids.c -DMEDIUM_DATASET -o Medium_dataset/WASM/sortingids_runWASM_MEDIUM.js -O2 -s WASM=1
	emcc sortingids.c -DMEDIUM_DATASET -o Medium_dataset/JS/sortingids_runJS_MEDIUM.js -O2 -s WASM=0
	emcc sortingids.c -DLARGE_DATASET -o Large_dataset/WASM/sortingids_runWASM_LARGE.js -O2 -s WASM=1
	emcc sortingids.c -DLARGE_DATASET -o Large_dataset/JS/sortingids_runJS_LARGE.js -O2 -s WASM=0
