#!/bin/bash

RESULT=0

function assertNoLeak()
{
    valgrind --tool=memcheck --leak-check=full --xml=yes --xml-file=$1.xml $1
    LEAKCOUNT=`xmllint --xpath "//leakedblocks" $1.xml 2>/dev/null | wc -l`

    if [ $LEAKCOUNT -ne 0 ]
    then
        echo ""
        echo ""
        echo "Test $1 leaks:"
        cat $1.xml
        echo ""


        RESULT=1
    else
        echo "$1 does not leak"
    fi
}



pushd . >/dev/null 2>&1
cd $1

for TEST_EXECUTABLE in `find . -type f -executable`
do
    assertNoLeak $TEST_EXECUTABLE
done

popd >/dev/null 2>&1
exit $RESULT
