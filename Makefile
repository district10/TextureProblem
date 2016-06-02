all: 
	@mkdir -p tmp
	cp TextureProblem.mk tmp/Makefile
	make -C tmp

qiniu:
	qrsync conf.json

clean:
	rm -rf tmp/*
	rm TextureProblem.pdf 2>/dev/null

rmpdf:
	rm TextureProblem.pdf tmp/TextureProblem.pdf
