echo "============ testing no page1 ==========="
valgrind ./cyoa-step2 ./tests/step2/no_1
echo "============ testing no win ==========="
valgrind ./cyoa-step2 ./tests/step2/no_win
echo "============ testing no lose ==========="
valgrind ./cyoa-step2 ./tests/step2/no_lose
echo "============ testing no ref_not_in_story ==========="
valgrind ./cyoa-step2 ./tests/step2/ref_not_in_story
echo "============ testing miss ref (some pages have no reference) ==========="
valgrind ./cyoa-step2 ./tests/step2/miss_ref
echo "============ testing story1 longest path  ==========="
valgrind ./cyoa-step2 ./story1 < ./tests/step2/input_test/in_1_2_5_14.txt
echo "============ testing story1 shortest path  ==========="
valgrind ./cyoa-step2 ./story1 < ./tests/step2/input_test/in_1_2_6.txt
echo "============ testing story2 longest path  ==========="
valgrind ./cyoa-step2 ./story1 < ./tests/step2/input_test/i2n_1_2_6_7_12_9
echo "============ testing story2 shortest path  ==========="
valgrind ./cyoa-step2 ./story1 < ./tests/step2/input_test/i2n_1_3.txt
