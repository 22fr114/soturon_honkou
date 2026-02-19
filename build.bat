@echo off
REM ====================================================
REM  LaTeX コンパイルスクリプト
REM  使用方法: build.bat
REM ====================================================

setlocal

set MAIN=main
set LATEX=platex
set DVIPDF=dvipdfmx

echo ====================================
echo  LaTeX Build Script
echo ====================================

REM 1回目のコンパイル
echo [1/3] Running %LATEX%...
%LATEX% -interaction=nonstopmode %MAIN%.tex
if errorlevel 1 (
    echo Error: LaTeX compilation failed.
    pause
    exit /b 1
)

REM 2回目のコンパイル（相互参照解決のため）
echo [2/3] Running %LATEX% again for cross-references...
%LATEX% -interaction=nonstopmode %MAIN%.tex
if errorlevel 1 (
    echo Error: LaTeX compilation failed.
    pause
    exit /b 1
)

REM DVIからPDF変換
echo [3/3] Converting DVI to PDF...
%DVIPDF% %MAIN%.dvi
if errorlevel 1 (
    echo Error: DVI to PDF conversion failed.
    pause
    exit /b 1
)

echo ====================================
echo  Build completed successfully!
echo  Output: %MAIN%.pdf
echo ====================================

endlocal
