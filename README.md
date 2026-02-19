![LaTeX](https://img.shields.io/badge/LaTeX-pLaTeX-008080?logo=latex&logoColor=white)
![TeX Live](https://img.shields.io/badge/TeX_Live-2020+-3D6117)
![Docker](https://img.shields.io/badge/Docker-Dev%20Containers-2496ED?logo=docker&logoColor=white)
# 卒業研究報告書 LaTeX テンプレート

卒業研究中間報告書／卒業研究予稿用テンプレート(非公式)です。必要があればforkして使用してください。 

本リポジトリは、非Docker版テンプレート（ https://github.com/yokolab2025/FR_Thesis_Tex_Template_unofficial.git ）の Docker / VS Code Dev Containers 対応版です。

## 必要な環境 Docker（VS Code Dev Containers を使う場合）

- Docker Desktop https://www.docker.com/ja-jp/products/docker-desktop/
- VS Code 拡張機能「Dev Containers」（ms-vscode-remote.remote-containers）

> メモ: コンテナ環境内には LaTeX Workshop が自動でインストールされます（[.devcontainer/devcontainer.json](.devcontainer/devcontainer.json) 参照）。

## Dev Container（VS Code）によるコンパイル方法

VS Code の「Dev Containers」拡張機能を使うと、`.devcontainer/devcontainer.json` から同じ環境を自動で起動できます。

1. VS Code でこのフォルダを開く
2. コマンドパレット → 「Dev Containers: Reopen in Container」
3. コンテナ内で `main.tex`を開き，右上の再生ボタンでビルド


## ファイル構成

```
├── .devcontainer/
│   └── devcontainer.json     # VS Code Dev Containers 設定
├── chapters/
│   ├── 01_introduction.tex   # 第1章：緒論
│   ├── 02_theory.tex         # 第2章：理論
│   ├── 03_method.tex         # 第3章：提案手法
│   ├── 04_experiment.tex     # 第4章：実験・評価
│   ├── 05_conclusion.tex     # 第5章：結論
│   └── 99_references.tex     # 参考文献
├── .dockerignore             # Docker ビルド除外設定
├── .gitignore                # Git 管理除外設定
├── .latexmkrc                # latexmk 設定
├── Dockerfile                # LaTeX 環境（コンテナ）定義
├── FR_style.sty              # スタイルファイル
├── main.tex                  # メインファイル（コンパイル対象）
├── build.bat                 # コンパイルスクリプト (cmd)
├── build.ps1                 # コンパイルスクリプト (PowerShell)
└── clean.bat                 # 中間ファイル削除スクリプト
```



※ 相互参照を正しく解決するため、`platex` は2回実行します。

### 中間ファイルの削除

```cmd
clean.bat
```

### 推奨エディタ

- VS Code + LaTeX Workshop 拡張機能
- TeXstudio
- TeXworks

## 執筆ルール

### フォント・レイアウト

| 項目 | 設定 |
|------|------|
| 本文フォント | 明朝体 10pt |
| 本文インデント | 一字下げ |
| 図表キャプション | ゴシック体 |
| 表中の文字 | 9pt |
| 参考文献 | 9pt |

### ヘッダー情報

`main.tex` で以下を設定してください：

- 和文タイトル
- 英文タイトル (Title in English)
- 指導教員名（例：教授 ○○ ○○）
- 学籍番号・氏名（例：10FR*** ○○ ○○）

※ 概要（Abstract）を日本語・英語どちらで書くかは指導教員の指示に従ってください。

### 推奨される章構成

1. **緒論（はじめに）** - 研究背景と研究目的
2. **理論** - システムの説明、モデリング
3. **提案手法** - 設計・実装
4. **実験・評価** - シミュレーション、実験結果
5. **結論（おわりに）** - まとめと今後の課題

### 図・表・参考文献の記述方法

#### 番号付けルール

予稿全体で通し番号をつけます：

| 要素 | 参照形式 | 例 |
|------|----------|-----|
| 図 | `Fig. 番号` | Fig. 1, Fig. 2 |
| 表 | `Table 番号` | Table 1, Table 2 |
| 数式 | `(番号)` | (1), (2) |

LaTeXでは `\label{}` と `\ref{}` を使用して相互参照してください。

#### 図の記述例

```latex
\begin{figure}[h]
  \centering
  \includegraphics[width=0.9\hsize]{src/example.png}
  \caption{図のキャプション}
  \label{fig:example}
\end{figure}

Fig.~\ref{fig:example}に示すように...
```

#### 表の記述例

```latex
\begin{table}[h]
  \centering
  \caption{表のキャプション}
  \label{tab:example}
  \small
  \begin{tabular}{c|c} \hline \hline
    項目 & 値 \\ \hline
    データ1 & 100 \\ \hline
    データ2 & 200 \\ \hline
  \end{tabular}
\end{table}

Table~\ref{tab:example}に示すように...
```

#### 参考文献の記述例

- **日本語文献**: 著者名：タイトル，掲載誌名，巻(号)，pp.ページ範囲 (発行年)
- **英語文献**: IEEE形式に準拠

```latex
\bibitem{ref01}
    石川：ハードディスク装置のRun-out Orientedな制御系の一設計，
    平成20年電気学会産業応用部門大会予稿集，pp. 63--68 (2008).

\bibitem{ref02}
    A. Mamun, et al., ``Iterative Feedback Tuning of HDD,''
    Proc. of IECON, pp. 769--774, Nov. 2007.
```

本文での参照：
```latex
文献\cite{ref01}によると...
```
