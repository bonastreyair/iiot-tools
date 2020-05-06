#!/bin/bash

echo "= What is your name?"
read NAME

echo "= Hello "$NAME"! This is a script!"
echo "= I can read input variables, like your name"

NUMBER=1

while [ $NUMBER -gt 0 ]
do
  echo "= Tell me a number between 1 and 10. 0 will quit the script"
  read NUMBER
  if [ $NUMBER -eq 0 ]
  then
    echo "= Exiting the script"
  elif [ $NUMBER -gt 5 ]
  then
    echo "= Your number is greater than 5 - " $NUMBER "> 5"
  else
    echo "= Your number is not greater than 5 - " $NUMBER" <=  5"
  fi
done

