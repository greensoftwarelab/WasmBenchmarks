smallcompile:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=native -fopenmp -D_FILE_OFFSET_BITS=64 -I/usr/include/apr-1.0 sortingmerge.c -o Small_dataset/C/sortingmerge_runSMALL -lapr-1 -lgomp -lm -DSMALL_DATASET

mediumcompile:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=native -fopenmp -D_FILE_OFFSET_BITS=64 -I/usr/include/apr-1.0 sortingmerge.c -o Medium_dataset/C/sortingmerge_runMEDIUM -lapr-1 -lgomp -lm -DMEDIUM_DATASET

largecompile:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=native -fopenmp -D_FILE_OFFSET_BITS=64 -I/usr/include/apr-1.0 sortingmerge.c -o Large_dataset/C/sortingmerge_runLARGE -lapr-1 -lgomp -lm -DLARGE_DATASET

wasmsmall:
	emcc sortingmerge.c -DSMALL_DATASET -o Small_dataset/WASM/sortingmerge_runSMALL.js -O2 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1

jssmall:
	emcc sortingmerge.c -DSMALL_DATASET -o Small_dataset/JS/sortingmerge_runSMALL.js -O2 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1

wasmmedium:
	emcc sortingmerge.c -DMEDIUM_DATASET -o Medium_dataset/WASM/sortingmerge_runMEDIUM.js -O2 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1

jsmedium:
	emcc sortingmerge.c -DMEDIUM_DATASET -o Medium_dataset/JS/sortingmerge_runMEDIUM.js -O2 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1

wasmlarge:
	emcc sortingmerge.c -DLARGE_DATASET -o Large_dataset/WASM/sortingmerge_runLARGE.js -O2 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1

jslarge:
	emcc sortingmerge.c -DLARGE_DATASET -o Large_dataset/JS/sortingmerge_runLARGE.js -O2 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1

compileall:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=native -fopenmp -D_FILE_OFFSET_BITS=64 -I/usr/include/apr-1.0 sortingmerge.c -o Small_dataset/C/sortingmerge_runSMALL -lapr-1 -lgomp -lm -DSMALL_DATASET
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=native -fopenmp -D_FILE_OFFSET_BITS=64 -I/usr/include/apr-1.0 sortingmerge.c -o Medium_dataset/C/sortingmerge_runMEDIUM -lapr-1 -lgomp -lm -DMEDIUM_DATASET
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=native -fopenmp -D_FILE_OFFSET_BITS=64 -I/usr/include/apr-1.0 sortingmerge.c -o Large_dataset/C/sortingmerge_runLARGE -lapr-1 -lgomp -lm -DLARGE_DATASET
	emcc sortingmerge.c -DSMALL_DATASET -o Small_dataset/WASM/sortingmerge_runWASM_SMALL.js -O2 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1
	emcc sortingmerge.c -DSMALL_DATASET -o Small_dataset/JS/sortingmerge_runJS_SMALL.js -O2 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1
	emcc sortingmerge.c -DMEDIUM_DATASET -o Medium_dataset/WASM/sortingmerge_runWASM_MEDIUM.js -O2 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1
	emcc sortingmerge.c -DMEDIUM_DATASET -o Medium_dataset/JS/sortingmerge_runJS_MEDIUM.js -O2 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1
	emcc sortingmerge.c -DLARGE_DATASET -o Large_dataset/WASM/sortingmerge_runWASM_LARGE.js -O2 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1
	emcc sortingmerge.c -DLARGE_DATASET -o Large_dataset/JS/sortingmerge_runJS_LARGE.js -O2 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1
