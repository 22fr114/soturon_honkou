# ====================================================
#  LaTeX コンパイルスクリプト (PowerShell)
#  使用方法: .\build.ps1
# ====================================================

$ErrorActionPreference = "Stop"

$MAIN = "main"
$LATEX = "platex"
$DVIPDF = "dvipdfmx"

Write-Host "====================================" -ForegroundColor Cyan
Write-Host " LaTeX Build Script" -ForegroundColor Cyan
Write-Host "====================================" -ForegroundColor Cyan

try {
    # 1回目のコンパイル
    Write-Host "[1/3] Running $LATEX..." -ForegroundColor Yellow
    & $LATEX -interaction=nonstopmode "$MAIN.tex"
    if ($LASTEXITCODE -ne 0) {
        throw "LaTeX compilation failed."
    }

    # 2回目のコンパイル（相互参照解決のため）
    Write-Host "[2/3] Running $LATEX again for cross-references..." -ForegroundColor Yellow
    & $LATEX -interaction=nonstopmode "$MAIN.tex"
    if ($LASTEXITCODE -ne 0) {
        throw "LaTeX compilation failed."
    }

    # DVIからPDF変換
    Write-Host "[3/3] Converting DVI to PDF..." -ForegroundColor Yellow
    & $DVIPDF "$MAIN.dvi"
    if ($LASTEXITCODE -ne 0) {
        throw "DVI to PDF conversion failed."
    }

    Write-Host "====================================" -ForegroundColor Green
    Write-Host " Build completed successfully!" -ForegroundColor Green
    Write-Host " Output: $MAIN.pdf" -ForegroundColor Green
    Write-Host "====================================" -ForegroundColor Green
}
catch {
    Write-Host "Error: $_" -ForegroundColor Red
    exit 1
}
