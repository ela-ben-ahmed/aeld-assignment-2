#!/bin/sh
filesdir=$1
searchstr=$2

if [ -z "$filesdir" ] || [ -z "$searchstr" ]; then
    echo "Error: Parameters missing"
    exit 1
fi

if [ ! -d "$filesdir" ]; then
    echo "Error: $filesdir does not represent a directory on the filesystem"
    exit 1
fi

numf=$(find "$filesdir" -type f | wc -l)
numl=$(grep -r "$searchstr" "$filesdir" 2>/dev/null | wc -l)

echo "The number of files are $numf and the number of matching lines are $numl"
