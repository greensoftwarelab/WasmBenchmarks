wasmhtml:
	emcc example.c -o example_runMEDIUM.html -O2 -s WASM=1

localhost:
	python3 -m http.server

chrome:
	google-chrome http://localhost:8000/example_runMEDIUM.html

firefox:
	firefox http://localhost:8000/example_runMEDIUM.html

gcc:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge -fopenmp example.c -o example_runSMALL -DLARGE_DATASET

smallcompile:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge -fopenmp example.c -o Small_dataset/C/example_runSMALL -DSMALL_DATASET

mediumcompile:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge -fopenmp example.c -o Medium_dataset/C/example_runMEDIUM -DMEDIUM_DATASET

largecompile:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge -fopenmp example.c -o Large_dataset/C/example_runLARGE -DLARGE_DATASET

wasmsmall:
	emcc example.c -DSMALL_DATASET -o Small_dataset/WASM/example_runSMALL.js -O2 -s WASM=1

jssmall:
	emcc example.c -DSMALL_DATASET -o Small_dataset/JS/example_runSMALL.js -O2 -s WASM=0

wasmmedium:
	emcc example.c -DMEDIUM_DATASET -o Medium_dataset/WASM/example_runMEDIUM.js -O2 -s WASM=1

jsmedium:
	emcc example.c -DMEDIUM_DATASET -o Medium_dataset/JS/example_runMEDIUM.js -O2 -s WASM=0

wasmlarge:
	emcc example.c -DLARGE_DATASET -o Large_dataset/WASM/example_runLARGE.js -O2 -s WASM=1

jslarge:
	emcc example.c -DLARGE_DATASET -o Large_dataset/JS/example_runLARGE.js -O2 -s WASM=0

compileall:
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge -fopenmp example.c -o Small_dataset/C/example_runSMALL -DSMALL_DATASET
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge -fopenmp example.c -o Medium_dataset/C/example_runMEDIUM -DMEDIUM_DATASET
	/usr/bin/gcc -pipe -Wall -O3 -fomit-frame-pointer -march=ivybridge -fopenmp example.c -o Large_dataset/C/example_runLARGE -DLARGE_DATASET
	emcc example.c -DSMALL_DATASET -o Small_dataset/WASM/example_runWASM_SMALL.js -O2 -s WASM=1
	emcc example.c -DSMALL_DATASET -o Small_dataset/JS/example_runJS_SMALL.js -O2 -s WASM=0
	emcc example.c -DMEDIUM_DATASET -o Medium_dataset/WASM/example_runWASM_MEDIUM.js -O2 -s WASM=1
	emcc example.c -DMEDIUM_DATASET -o Medium_dataset/JS/example_runJS_MEDIUM.js -O2 -s WASM=0
	emcc example.c -DLARGE_DATASET -o Large_dataset/WASM/example_runWASM_LARGE.js -O2 -s WASM=1
	emcc example.c -DLARGE_DATASET -o Large_dataset/JS/example_runJS_LARGE.js -O2 -s WASM=0
