#!/usr/bin/bash

if [ -z "$1" ];
then
  echo -e "Doing nothing since no arg given.\nUsage: $0 <question number>"
  exit -1
fi

qstr="p$1"
qcc="$qstr.cc"

if [ -f "$qcc" ]
then
  echo "doing nothing since $qcc already exists"
else
  echo "creating $qcc and updating BUILD"
  cp template $qcc

  echo -e "\ncc_binary(\n  name = \"$qstr\",\n  srcs = [\"$qcc\"],\n  deps = [\n    \"//projecteuler/solutions:library\",\n  ],\n)" >> BUILD
fi
