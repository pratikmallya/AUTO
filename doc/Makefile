#
#   Makefile		11/1996
#
RM     = rm -f
#
all:  manual
#
manual: auto.tex
	latex auto.tex
	bibtex auto
	latex auto.tex
	latex auto.tex
	dvips -o auto.ps auto 

short:
	latex auto.tex

html:
	latex2html auto.tex
#
clean:
	@echo "Cleaning auto.doc ..."
	@$(RM) *~ *.dvi *.ps *.aux *.bbl *.blg *.log *.toc
	@echo "Cleaning ... done"
