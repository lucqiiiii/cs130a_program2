#! /bin/bash

PASSED=$(printf "[\e[32mPASSED\e[0m]")
FAILED=$(printf "[\e[31mFAILED\e[0m]")

for test in $(find "tests" -name "*.avl" | sort); do
  out="${test%avl}out"
  tgt="${test%avl}tgt"
  ./avl "$test" > "$out"
  if cmp -s "$tgt" "$out"; then
    echo "$PASSED: $test"
    rm "$out"
  else
    echo "$FAILED: $test"
    diff "$tgt" "$out"
  fi
done
