#!/bin/bash

# To save build results put "NotDelBuildResults" as commandline parameter of this script !!!

#MultiLineBashCommenter() {

[ -z $BASH ] || shopt -s expand_aliases
alias BEGINCOMMENT="if [ ]; then"
alias ENDCOMMENT="fi"

#BEGINCOMMENT
#ENDCOMMENT

#}

DeleteTmpBildFolders() {

if [ -d build ]; then
      rm -rf build
fi
if [ -d builds ]; then
      rm -rf builds
fi

}

DeleteHtml2pdfFiles() {

if [ -f html2pdf ]; then
      rm -f html2pdf
fi

if [ -f learncpp.html ]; then
      rm -f learncpp.html
fi

if [ -d html2pdf ]; then
      rm -rf html2pdf
fi

}

PreviousCommandExitCodeCheck() {

if [ $? -ne 0 ]; then
  echo -e "PreviousCommandExitCodeCheck: Failure execute previous command\n" >&2
  exit 1
fi

}

CheckNotDelBuildCommandLineArgument() {

if [[ "$1" == "NotDelBuildResults" ]]; then
  echo -e "$1: Save all build results\n";
  exit 0
fi

}

DeleteTmpBildFolders
DeleteHtml2pdfFiles


mkdir build
cmake -S . -B build
cd build
make

PreviousCommandExitCodeCheck


cd ..

if [ -f build/html2pdf ]; then
      mkdir html2pdf
      cp build/html2pdf html2pdf/
      cp src/pdf/templates/learncpp.template html2pdf/
fi

CheckNotDelBuildCommandLineArgument $1

DeleteTmpBildFolders
