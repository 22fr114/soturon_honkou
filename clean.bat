@echo off
REM ====================================================
REM  中間ファイル削除スクリプト
REM  使用方法: clean.bat
REM ====================================================

echo Cleaning intermediate files...

del /q *.aux 2>nul
del /q *.log 2>nul
del /q *.dvi 2>nul
del /q *.toc 2>nul
del /q *.lof 2>nul
del /q *.lot 2>nul
del /q *.out 2>nul
del /q *.bbl 2>nul
del /q *.blg 2>nul
del /q chapters\*.aux 2>nul

echo Clean completed!
