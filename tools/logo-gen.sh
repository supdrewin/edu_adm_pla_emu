#!/bin/bash

[[ $1 ]] || exit 1

dist=${1%%.*}.hh
src=$(cat "$1")

tmp=${src//
/\\x0a}
tmp=${tmp// /\\x20}
tmp=${tmp//#/\\x1b\\x5b\\x34\\x33\\x6d\\x20\\x1b\\x5b\\x30\\x6d}
tmp=${tmp//\\x1b\\x5b\\x30\\x6d\\x1b\\x5b\\x34\\x33\\x6d/}

echo "#pragma once

#if defined(__has_logo)

static const char *logo = \"$tmp\\x0a\";

#endif // defined(__has_logo)" >"$dist"
clang-format -i "$dist"
