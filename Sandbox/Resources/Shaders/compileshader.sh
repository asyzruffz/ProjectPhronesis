#!/bin/bash
#
# Usage: sh compileshader.sh <output directory>
#
scriptdir=$(dirname $0) # Save directory of this script
outdir="."
if [ ! -z "$1" ] # Check first param exists
then
	outdir="$1"
fi
for files in $scriptdir/*.vert $scriptdir/*.tesc $scriptdir/*.tese $scriptdir/*.geom $scriptdir/*.frag $scriptdir/*.comp 
do
	[ -e "$files" ] || continue # This line takes care if there's no matching file
	mkdir -p "$outdir/Shaders"
	shaderfile=$(basename -- $files)
	glslangValidator -V "$files" -o "$outdir/Shaders/$shaderfile.spv" >/dev/null
	echo "Compiled $shaderfile to $outdir/Shaders/$shaderfile.spv"
done