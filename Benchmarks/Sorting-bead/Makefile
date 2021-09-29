smallcompile:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=native -fopenmp -D_FILE_OFFSET_BITS=64 -I/usr/include/apr-1.0 sortbead.c -o Small_dataset/C/sortbead_runSMALL -lapr-1 -lgomp -lm -DSMALL_DATASET

mediumcompile:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=native -fopenmp -D_FILE_OFFSET_BITS=64 -I/usr/include/apr-1.0 sortbead.c -o Medium_dataset/C/sortbead_runMEDIUM -lapr-1 -lgomp -lm -DMEDIUM_DATASET

largecompile:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=native -fopenmp -D_FILE_OFFSET_BITS=64 -I/usr/include/apr-1.0 sortbead.c -o Large_dataset/C/sortbead_runLARGE -lapr-1 -lgomp -lm -DLARGE_DATASET

wasmsmall:
	emcc sortbead.c -DSMALL_DATASET -o Small_dataset/WASM/sortbead_runSMALL.js -O2 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1

jssmall:
	emcc sortbead.c -DSMALL_DATASET -o Small_dataset/JS/sortbead_runSMALL.js -O2 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1

wasmmedium:
	emcc sortbead.c -DMEDIUM_DATASET -o Medium_dataset/WASM/sortbead_runMEDIUM.js -O2 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1

jsmedium:
	emcc sortbead.c -DMEDIUM_DATASET -o Medium_dataset/JS/sortbead_runMEDIUM.js -O2 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1

wasmlarge:
	emcc sortbead.c -DLARGE_DATASET -o Large_dataset/WASM/sortbead_runLARGE.js -O2 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1

jslarge:
	emcc sortbead.c -DLARGE_DATASET -o Large_dataset/JS/sortbead_runLARGE.js -O2 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1

compileall:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=native -fopenmp -D_FILE_OFFSET_BITS=64 -I/usr/include/apr-1.0 sortbead.c -o Small_dataset/C/sortbead_runSMALL -lapr-1 -lgomp -lm -DSMALL_DATASET
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=native -fopenmp -D_FILE_OFFSET_BITS=64 -I/usr/include/apr-1.0 sortbead.c -o Medium_dataset/C/sortbead_runMEDIUM -lapr-1 -lgomp -lm -DMEDIUM_DATASET
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=native -fopenmp -D_FILE_OFFSET_BITS=64 -I/usr/include/apr-1.0 sortbead.c -o Large_dataset/C/sortbead_runLARGE -lapr-1 -lgomp -lm -DLARGE_DATASET
	emcc sortbead.c -DSMALL_DATASET -o Small_dataset/WASM/sortbead_runWASM_SMALL.js -O2 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1
	emcc sortbead.c -DSMALL_DATASET -o Small_dataset/JS/sortbead_runJS_SMALL.js -O2 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1
	emcc sortbead.c -DMEDIUM_DATASET -o Medium_dataset/WASM/sortbead_runWASM_MEDIUM.js -O2 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1
	emcc sortbead.c -DMEDIUM_DATASET -o Medium_dataset/JS/sortbead_runJS_MEDIUM.js -O2 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1
	emcc sortbead.c -DLARGE_DATASET -o Large_dataset/WASM/sortbead_runWASM_LARGE.js -O2 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1
	emcc sortbead.c -DLARGE_DATASET -o Large_dataset/JS/sortbead_runJS_LARGE.js -O2 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1
