LATEXCMD = pdflatex -shell-escape -output-directory build/
export TEXINPUTS=.:content/tex/:
export max_print_line = 1048576

help:
	@echo "This makefile builds UzhNU_3yagoda team notebook (using makefile and templates of KTH Algorithm Competition Template Library)"
	@echo ""
	@echo "Available commands are:"
	@echo "	make fast		- to build notebook, quickly (only runs LaTeX once)"
	@echo "	make notebook		- to build notebook"
	@echo "	make clean		- to clean up the build process"
	@echo "	make veryclean		- to clean up and remove notebook.pdf"
	@echo "	make test-compiles	- to test compiling all headers"
	@echo "	make help		- to show this information"
	@echo "	make showexcluded	- to show files that are not included in the doc"

fast: | build
	$(LATEXCMD) content/notebook.tex </dev/null
	cp build/notebook.pdf notebook.pdf

notebook: test-session.pdf | build
	$(LATEXCMD) content/notebook.tex && $(LATEXCMD) content/notebook.tex
	cp build/notebook.pdf notebook.pdf

clean:
	cd build && rm -f notebook.aux notebook.log notebook.tmp notebook.toc notebook.pdf notebook.ptc

veryclean: clean
	rm -f notebook.pdf test-session.pdf

.PHONY: help fast notebook clean veryclean

build:
	mkdir -p build/

test-session.pdf: content/test-session/test-session.tex content/test-session/chapter.tex | build
	$(LATEXCMD) content/test-session/test-session.tex
	cp build/test-session.pdf test-session.pdf

showexcluded: build
	grep -RoPh '^\s*\\kactlimport{\K.*' content/ | sed 's/.$$//' > build/headers_included
	find ./content -name "*.h" -o -name "*.py" -o -name "*.java" | grep -vFf build/headers_included
