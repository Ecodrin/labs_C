#!/bin/bash


function recurse1(){
    for dir1 in "$1"/*; do
        if [ -d "$dir1" ];then
            echo "$dir1"
            recurse1 "$dir1"
        fi
    done
}

#Основная программа
read -p "Введите путь до каталога: " str1

#Проверка на пустоту
if ["$str1" -eq ""]; then
    str1="/home/matvey/Unik/"
fi

recurse1  $str1
