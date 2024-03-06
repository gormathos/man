#!/bin/bash

name=$(cat problem_ua_pdf.tex | sed -n '1p' | sed -e 's/\\begin{problem}{//g' | sed -e 's/}{}{}{.*//g')
sed -e "s/$name//;1a\% $name" problem_ua_pdf.tex > problem_ua.tex

name=$(cat problem_en_pdf.tex | sed -n '1p' | sed -e 's/\\begin{problem}{//g' | sed -e 's/}{}{}{.*//g')
sed -e "s/$name//;1a\% $name" problem_en_pdf.tex > problem_en.tex

cp problem_ua.tex problem.tex

