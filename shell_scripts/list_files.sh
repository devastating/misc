#!/bin/bash

# List Python files in current directory that only has .pyc, but no .py

# 1. in ls, use --time-style to fix the output format
# 2. egrep - extension grep for regular expression
# 3. last egrep makes sure files left are with extension
# 4. sort the files
PY_FILES=`ls -lR --time-style="long-iso" | egrep '^-' | awk '{print $8}' | egrep '(*\.py|*\.pyc|*\.pyo)' | sort`
PY_SOUCE=""
for PY_FILE in ${PY_FILES}
do
    if [[ "$PY_FILE" == *\.py ]]; then
        PY_SOURCE="${PY_FILE%.*}"
    else
        py_file="${PY_FILE%.*}"
        if [ "$py_file" != "$PY_SOURCE" ]; then
            echo "Found no-source Python file $PY_FILE"
        fi
    fi
done
