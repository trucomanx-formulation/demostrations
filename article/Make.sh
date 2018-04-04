#!/bin/bash
latex -interaction=nonstopmode demos.tex
latex -interaction=nonstopmode demos.tex
latex -interaction=nonstopmode demos.tex

./clean.sh
