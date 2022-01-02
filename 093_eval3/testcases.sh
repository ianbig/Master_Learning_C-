#!/bin/bash
echo "which testcases to load?"
ls ./testcases/
read var
ls ./testcases/$var
cp ./testcases/$var ./testcases.txt
echo "finish making testcases"
