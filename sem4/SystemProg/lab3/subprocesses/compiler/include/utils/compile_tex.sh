#!/bin/bash


if [ ! $# -eq 2 ];then
    exit 1
fi

filename="$1"

if [ -f "$filename" ]; then
    pdflatex -halt-on-error -interaction=nonstopmode -jobname="$2" "$filename"
    rm -rd "$2.log"
    rm -rd "$2.toc"
    rm -rd "$2.aux"
    exit 0
else
  echo "This file doesn't exist"
  exit 1
fi
