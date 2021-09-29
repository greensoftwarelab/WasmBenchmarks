raplserver:
	sudo modprobe msr
	sudo ../../../../../RAPL/raplServer

raplclient:
	sudo modprobe msr
	for number in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 ; do \
        sleep 5;sudo ../../../../../RAPL/raplClient 10000 fastaLARGE$$number "node ../fasta.gcc-2.gcc_runJS_LARGE.js" ; \
    done

clean:
	sudo rm *.rapl *.time