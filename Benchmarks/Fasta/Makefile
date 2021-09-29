smallcompile:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge  fasta.gcc-2.c -o Small_dataset/C/fasta.gcc-2.gcc_runSMALL -DSMALL_DATASET

mediumcompile:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge  fasta.gcc-2.c -o Medium_dataset/C/fasta.gcc-2.gcc_runMEDIUM -DMEDIUM_DATASET

largecompile:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge  fasta.gcc-2.c -o Large_dataset/C/fasta.gcc-2.gcc_runLARGE -DLARGE_DATASET

wasmsmall:
	emcc fasta.gcc-2.c -DSMALL_DATASET -o Small_dataset/WASM/fasta.gcc-2.gcc_runSMALL.js -O2 -s WASM=1

jssmall:
	emcc fasta.gcc-2.c -DSMALL_DATASET -o Small_dataset/JS/fasta.gcc-2.gcc_runSMALL.js -O2 -s WASM=0

wasmmedium:
	emcc fasta.gcc-2.c -DMEDIUM_DATASET -o Medium_dataset/WASM/fasta.gcc-2.gcc_runMEDIUM.js -O2 -s WASM=1

jsmedium:
	emcc fasta.gcc-2.c -DMEDIUM_DATASET -o Medium_dataset/JS/fasta.gcc-2.gcc_runMEDIUM.js -O2 -s WASM=0

wasmlarge:
	emcc fasta.gcc-2.c -DLARGE_DATASET -o Large_dataset/WASM/fasta.gcc-2.gcc_runLARGE.js -O2 -s WASM=1

jslarge:
	emcc fasta.gcc-2.c -DLARGE_DATASET -o Large_dataset/JS/fasta.gcc-2.gcc_runLARGE.js -O2 -s WASM=0

compileall:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge  fasta.gcc-2.c -o Small_dataset/C/fasta.gcc-2.gcc_runSMALL -DSMALL_DATASET
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge  fasta.gcc-2.c -o Medium_dataset/C/fasta.gcc-2.gcc_runMEDIUM -DMEDIUM_DATASET
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge  fasta.gcc-2.c -o Large_dataset/C/fasta.gcc-2.gcc_runLARGE -DLARGE_DATASET
	emcc fasta.gcc-2.c -DSMALL_DATASET -o Small_dataset/WASM/fasta.gcc-2.gcc_runWASM_SMALL.js -O2 -s WASM=1
	emcc fasta.gcc-2.c -DSMALL_DATASET -o Small_dataset/JS/fasta.gcc-2.gcc_runJS_SMALL.js -O2 -s WASM=0
	emcc fasta.gcc-2.c -DMEDIUM_DATASET -o Medium_dataset/WASM/fasta.gcc-2.gcc_runWASM_MEDIUM.js -O2 -s WASM=1
	emcc fasta.gcc-2.c -DMEDIUM_DATASET -o Medium_dataset/JS/fasta.gcc-2.gcc_runJS_MEDIUM.js -O2 -s WASM=0
	emcc fasta.gcc-2.c -DLARGE_DATASET -o Large_dataset/WASM/fasta.gcc-2.gcc_runWASM_LARGE.js -O2 -s WASM=1
	emcc fasta.gcc-2.c -DLARGE_DATASET -o Large_dataset/JS/fasta.gcc-2.gcc_runJS_LARGE.js -O2 -s WASM=0
