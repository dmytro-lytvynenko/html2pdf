#!/bin/bash

if [[ $1 == "http"* ]]; then
  google-chrome --headless --disable-gpu --print-to-pdf $1
else
  echo -e "It's not an URL address!\n"
fi
