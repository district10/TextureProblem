all: 
	@mkdir -p tmp
	cp TextureProblem.mk tmp/Makefile
	make -C tmp

qiniu:
	qrsync conf.json

clean:
	rm -rf tmp/*
	rm TextureProblem.pdf

rmpdf:
	rm TextureProblem.pdf tmp/TextureProblem.pdf
