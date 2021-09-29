smallcompile:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=native -fopenmp -D_FILE_OFFSET_BITS=64 -I/usr/include/apr-1.0 caesar-cipher.c -o Small_dataset/C/caesar-cipher_runSMALL -lapr-1 -lgomp -lm -DSMALL_DATASET


mediumcompile:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=native -fopenmp -D_FILE_OFFSET_BITS=64 -I/usr/include/apr-1.0 caesar-cipher.c -o Medium_dataset/C/caesar-cipher_runMEDIUM -lapr-1 -lgomp -lm -DMEDIUM_DATASET

largecompile:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=native -fopenmp -D_FILE_OFFSET_BITS=64 -I/usr/include/apr-1.0 caesar-cipher.c -o Large_dataset/C/caesar-cipher_runLARGE -lapr-1 -lgomp -lm -DLARGE_DATASET

wasmsmall:
	emcc caesar-cipher.c -DSMALL_DATASET -o Small_dataset/WASM/caesar-cipher_runSMALL.js -O2 -s WASM=1

jssmall:
	emcc caesar-cipher.c -DSMALL_DATASET -o Small_dataset/JS/caesar-cipher_runSMALL.js -O2 -s WASM=0

wasmmedium:
	emcc caesar-cipher.c -DMEDIUM_DATASET -o Medium_dataset/WASM/caesar-cipher_runMEDIUM.js -O2 -s WASM=1

jsmedium:
	emcc caesar-cipher.c -DMEDIUM_DATASET -o Medium_dataset/JS/caesar-cipher_runMEDIUM.js -O2 -s WASM=0

wasmlarge:
	emcc caesar-cipher.c -DLARGE_DATASET -o Large_dataset/WASM/caesar-cipher_runLARGE.js -O2 -s WASM=1

jslarge:
	emcc caesar-cipher.c -DLARGE_DATASET -o Large_dataset/JS/caesar-cipher_runLARGE.js -O2 -s WASM=0

compileall:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=native -fopenmp -D_FILE_OFFSET_BITS=64 -I/usr/include/apr-1.0 caesar-cipher.c -o Small_dataset/C/caesar-cipher_runSMALL -lapr-1 -lgomp -lm -DSMALL_DATASET
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=native -fopenmp -D_FILE_OFFSET_BITS=64 -I/usr/include/apr-1.0 caesar-cipher.c -o Medium_dataset/C/caesar-cipher_runMEDIUM -lapr-1 -lgomp -lm -DMEDIUM_DATASET
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=native -fopenmp -D_FILE_OFFSET_BITS=64 -I/usr/include/apr-1.0 caesar-cipher.c -o Large_dataset/C/caesar-cipher_runLARGE -lapr-1 -lgomp -lm -DLARGE_DATASET
	emcc caesar-cipher.c -DSMALL_DATASET -o Small_dataset/WASM/caesar-cipher_runWASM_SMALL.js -O2 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1
	emcc caesar-cipher.c -DSMALL_DATASET -o Small_dataset/JS/caesar-cipher_runJS_SMALL.js -O2 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1
	emcc caesar-cipher.c -DMEDIUM_DATASET -o Medium_dataset/WASM/caesar-cipher_runWASM_MEDIUM.js -O2 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1
	emcc caesar-cipher.c -DMEDIUM_DATASET -o Medium_dataset/JS/caesar-cipher_runJS_MEDIUM.js -O2 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1
	emcc caesar-cipher.c -DLARGE_DATASET -o Large_dataset/WASM/caesar-cipher_runWASM_LARGE.js -O2 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1
	emcc caesar-cipher.c -DLARGE_DATASET -o Large_dataset/JS/caesar-cipher_runJS_LARGE.js -O2 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1
