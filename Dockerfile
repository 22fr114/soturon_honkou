# syntax=docker/dockerfile:1
FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# TeX Live (pLaTeX/dvipdfmx) + latexmk
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
    ca-certificates \
    git \
    make \
    perl \
    latexmk \
    ghostscript \
    texlive \
    texlive-latex-extra \
    texlive-extra-utils \
    texlive-lang-japanese \
    texlive-fonts-recommended \
    fonts-noto-cjk \
    && rm -rf /var/lib/apt/lists/*

# Create a non-root user for Dev Containers (matches VS Code defaults)
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=1000
RUN groupadd --gid ${USER_GID} ${USERNAME} \
    && useradd --uid ${USER_UID} --gid ${USER_GID} -m ${USERNAME}

WORKDIR /workspaces
USER ${USERNAME}

# Default to a shell; Dev Container / docker run can override
CMD ["bash"]
