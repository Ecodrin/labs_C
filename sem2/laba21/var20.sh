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

while [ "$str1" == "?" ] || [ -z "$str1" ] || [ ! -d "$str1" ]
do
    echo "Необходимо указать полный пусть, например, </home/matwey> . Если путь не будет указан, будет взят шаблонный путь путь."
    read -p "Введите путь до каталога: " str1
done;

#Проверка на пустоту
if  [ ! "$str1" ]; then
    str1="/home/matvey/Unik"
fi

recurse1  $str1

