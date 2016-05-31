all: 
	@mkdir -p tmp
	cp TextureProblem.mk tmp/Makefile
	make -C tmp

clean:
	rm -rf tmp/*
	rm TextureProblem.pdf

rmpdf:
	rm TextureProblem.pdf tmp/TextureProblem.pdf
