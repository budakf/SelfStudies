#!/bin/sh
DYLD_IMAGE_SUFFIX=_debug
export DYLD_IMAGE_SUFFIX
exec /Users/budakf/Qt/5.12.3/clang_64/bin/moc "$@"
