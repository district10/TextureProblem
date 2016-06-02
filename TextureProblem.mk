ifeq (,$(MMTZX))
	MMTZX:=TANG ZhiXiong
endif
ifeq (,$(MMTJG))
	MMTJG:=TU JinGe
endif
ifeq (,$(MMZY))
	MMZY:=ZHANG Ying
endif

IMGSRC:=$(wildcard ../images/*)
IMGDST:= $(IMGSRC:../%=%)
CODESRC:=$(wildcard ../*.cpp)
CODEDST:= $(CODESRC:../%=code/%)
DIAGRAMSRC:=$(wildcard ../diagrams/*.tex ../diagrams/examples/*.tex)
DIAGRAMDST:=$(DIAGRAMSRC:../diagrams/examples/%.tex=%.pdf)
DIAGRAMDST:=$(DIAGRAMDST:../diagrams/%.tex=%.pdf)

all: $(IMGDST) $(CODEDST) $(DIAGRAMDST) TextureProblem.pdf ../TextureProblem.pdf

images/%: ../images/%
	@mkdir -p $(@D)
	cp $< $@
code/%.cpp: ../%.cpp
	@mkdir -p $(@D)
	cp $< $@
%.pdf: ../diagrams/%.tex
	xelatex $<
%.pdf: ../diagrams/examples/%.tex
	xelatex $<

TextureProblem.pdf: TextureProblem.tex cumcmthesis.cls
	xelatex $<
TextureProblem.tex: ../TextureProblem.tex
	cat $< \
		| sed -e "s/MMTZX/$(MMTZX)/" \
		| sed -e "s/MMTJG/$(MMTJG)/" \
		| sed -e "s/MMZY/$(MMZY)/" \
		| sed -e "s/BUILDDATE/$(BUILDDATE)/" \
		> $@
cumcmthesis.cls: ../cumcmthesis.cls
	cp $< $@

../TextureProblem.pdf: TextureProblem.pdf
	cp $< $@
