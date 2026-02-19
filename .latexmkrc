# latexmk configuration for pLaTeX -> DVI -> PDF (dvipdfmx)

$latex = 'platex -synctex=1 -interaction=nonstopmode -file-line-error %O %S';
$dvipdf = 'dvipdfmx %O -o %D %S';

# 3 = build via DVI and convert to PDF (uses $latex and $dvipdf)
$pdf_mode = 3;

# Be a bit more persistent resolving refs
$max_repeat = 5;
