#!/bin/bash

    cd statements

    cat begin.document_ru problem_ru.tex end.document > prob_ru.tex
    texi2pdf prob_ru.tex
    pdftoppm -tiff prob_ru.pdf > prob_ru.tif 
    convert  -transparent white -trim prob_ru.tif problem_ru.png

    cat begin.document_en problem_en.tex end.document > prob_en.tex
    texi2pdf prob_en.tex
    pdftoppm -tiff prob_en.pdf > prob_en.tif 
    convert  -transparent white -trim prob_en.tif problem_en.png

    cat begin.document_ua problem_ua.tex end.document > prob_ua.tex
    texi2pdf prob_ua.tex
    pdftoppm -tiff prob_ua.pdf > prob_ua.tif 
    convert  -transparent white -trim prob_ua.tif problem_ua.png

    rm -f *.tif *.pdf *.log *.dvi *.aux prob_*
    cd ..
