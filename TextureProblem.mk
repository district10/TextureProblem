DATASRC:=$(wildcard ../images/*)
DATADST:= $(DATASRC:../%=%)
CODESRC:=$(wildcard ../*.cpp)
CODEDST:= $(CODESRC:../%=code/%)

all: $(DATADST) $(CODEDST) TextureProblem.pdf ../TextureProblem.pdf

images/%: ../images/%
	@mkdir -p $(@D)
	cp $< $@
code/%.cpp: ../%.cpp
	@mkdir -p $(@D)
	cp $< $@

TextureProblem.pdf: TextureProblem.tex cumcmthesis.cls
	xelatex $<
TextureProblem.tex: ../TextureProblem.tex
	cp $< $@
cumcmthesis.cls: ../cumcmthesis.cls
	cp $< $@

../TextureProblem.pdf: TextureProblem.pdf
	cp $< $@
