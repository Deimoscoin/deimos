#!/usr/bin/env bash

export LC_ALL=C
TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
BUILDDIR=${BUILDDIR:-$TOPDIR}

BINDIR=${BINDIR:-$BUILDDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

DEIMOSD=${DEIMOSD:-$BINDIR/deimosd}
DEIMOSCLI=${DEIMOSCLI:-$BINDIR/deimos-cli}
DEIMOSTX=${DEIMOSTX:-$BINDIR/deimos-tx}
DEIMOSQT=${DEIMOSQT:-$BINDIR/qt/deimos-qt}

[ ! -x $DEIMOSD ] && echo "$DEIMOSD not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
DEIVER=($($DEIMOSCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for deimosd if --version-string is not set,
# but has different outcomes for deimos-qt and deimos-cli.
echo "[COPYRIGHT]" > footer.h2m
$DEIMOSD --version | sed -n '1!p' >> footer.h2m

for cmd in $DEIMOSD $DEIMOSCLI $DEIMOSTX $DEIMOSQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${DEIVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${DEIVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
