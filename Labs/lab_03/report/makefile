all: report

.PHONY: clean, report

report: report.pdf

report.pdf: report.tex preambula.tex *.tex
	pdflatex $<
	pdflatex $<
	pdflatex $<
	gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dNOPAUSE -dOptimize=true \
	-dBATCH -dRemoveUnusedFonts=true -dRemoveUnusedImages=true \
	-dOptimizeResources=true -dDetectDuplicateImages -dCompressFonts=true \
	-dEmbedAllFonts=true -dSubsetFonts=true -dPreserveAnnots=true \
	-dPreserveMarkedContent=true -dPreserveOverprintSettings=true \
	-dPreserveHalftoneInfo=true -dPreserveOPIComments=true \
	-dPreserveDeviceN=true -dMaxInlineImageSize=0 -sOUTPUTFILE=result.pdf \
	report.pdf
	mv ./result.pdf ./report.pdf
	make clean

clean:
	@rm -f *.aux *.log *.out *.toc *.bbl *.blg *.nav *.snm